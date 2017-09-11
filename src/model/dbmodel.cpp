#include "include/model/dbmodel.h"

#include <QDebug>

DBModel::DBModel()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("yattt.db");
    db.open();

    createTableIfNotExists();
}

DBModel::~DBModel() {
    db.close();
}

void DBModel::addEntry(const std::__cxx11::string &name, const std::__cxx11::string &description)
{
    QSqlQuery query;
    QString sql;
    bool success;

    sql = QString("INSERT INTO yattt_tasks VALUES ('%1', '%2', datetime('now'), datetime('now'), (SELECT rowid FROM yattt_task_status WHERE status_text = 'RUNNING'));").arg(name.c_str()).arg(description.c_str());
    success = query.exec(sql);
    if (!success) {
        throw std::runtime_error("'INSERT INTO' SQL command failed.\n\t" + sql.toStdString());
    }
}

void DBModel::createTableIfNotExists()
{
    QSqlQuery query;
    QString sql = QString("SELECT * FROM yattt_task_status;");
    bool success = query.exec(sql);
    if (!success) {
        sql = QString("CREATE TABLE yattt_task_status (status_text VARCHAR(100));");
        success = query.exec(sql);
        if (!success) {
            throw std::runtime_error("'CREATE TABLE' SQL command failed.\n\t" + sql.toStdString());
        }
        sql = QString("INSERT INTO yattt_task_status VALUES('RUNNING');");
        success = query.exec(sql);
        if (!success) {
            throw std::runtime_error("'INSERT INTO' SQL command failed.\n\t" + sql.toStdString());
        }
        sql = QString("INSERT INTO yattt_task_status VALUES('FINISHED');");
        success = query.exec(sql);
        if (!success) {
            throw std::runtime_error("'INSERT INTO' SQL command failed.\n\t" + sql.toStdString());
        }
    }
    sql = QString("SELECT * FROM yattt_tasks;");
    success = query.exec(sql);
    if (!success) {
        sql = QString("CREATE TABLE yattt_tasks (name VARCHAR(100), description VARCHAR(200), starting_time DATETIME, ending_time DATETIME, status_id INTEGER, FOREIGN KEY(status_id) REFERENCES yattt_task_status(rowid));");
        success = query.exec(sql);
        if (!success) {
            throw std::runtime_error("'CREATE TABLE' SQL command failed.\n\t" + sql.toStdString());
        }
    }
}
