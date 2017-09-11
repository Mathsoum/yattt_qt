#include "include/model/dbmodel.h"

#include <QVariant>
#include <ctime>

DBModel::DBModel()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("yattt.db");
    db.open();

    createTableIfDoesNotExist();
}

DBModel::~DBModel() {
    db.close();
}

void DBModel::addEntry(const std::__cxx11::string &name, const std::__cxx11::string &description)
{
    QSqlQuery query;
    QString sql;
    bool success;

    auto now = std::time(nullptr);
    sql = QString("INSERT INTO yattt_tasks VALUES ('%1', '%2', %3, %3, (SELECT rowid FROM yattt_task_status WHERE status_text = 'RUNNING'));").arg(name.c_str()).arg(description.c_str()).arg(now);
    success = query.exec(sql);
    if (!success) {
        throw std::runtime_error("'INSERT INTO' SQL command failed.\n\t" + sql.toStdString());
    }
}

std::vector<Task> DBModel::listTasks() const
{
    std::vector<Task> taskList;

    QSqlQuery query;
    bool success;
    QString sql = QString("SELECT name, description, status_id, starting_time, ending_time FROM yattt_tasks;");
    success = query.exec(sql);
    if (!success) {
        throw std::runtime_error("'SELECT' SQL command failed.\n\t" + sql.toStdString());
    }
    while(query.next()) {
        QString name = query.value(0).toString();
        QString description = query.value(1).toString();
        int statusId = query.value(2).toInt();
        int startingTimestamp = query.value(3).toInt();
        int endingTimestamp = query.value(4).toInt();
        QSqlQuery embeddedQuery;
        sql = QString("SELECT status_text FROM yattt_task_status WHERE _rowid_ = %1;").arg(QString::number(statusId));
        success = embeddedQuery.exec(sql);
        if (!success) {
            throw std::runtime_error("'SELECT' SQL command failed.\n\t" + sql.toStdString());
        }
        std::string statusText = "UNKNOWN";
        while(embeddedQuery.next()) {
            statusText = embeddedQuery.value(0).toString().toStdString();
        }
        taskList.push_back(Task(name.toStdString(), description.toStdString(), statusText, startingTimestamp, endingTimestamp));
    }

    return taskList;
}

void DBModel::createTableIfDoesNotExist()
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
        sql = QString("CREATE TABLE yattt_tasks (name VARCHAR(100), description VARCHAR(200), starting_time INTEGER, ending_time INTEGER, status_id INTEGER, FOREIGN KEY(status_id) REFERENCES yattt_task_status(rowid));");
        success = query.exec(sql);
        if (!success) {
            throw std::runtime_error("'CREATE TABLE' SQL command failed.\n\t" + sql.toStdString());
        }
    }
}
