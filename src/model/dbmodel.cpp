#include "include/model/dbmodel.h"

#include <QVariant>
#include <QDebug>

#include "include/gui/model/mainsqltablemodel.h"

DBModel::DBModel()
{
    qDebug() << "DBModel creation";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("yattt.db");
    db.open();

    tableModel = std::make_shared<MainSqlTableModel>(nullptr, db);
    tableModel->setTable("yattt_tasks");
    tableModel->setRelation(5, QSqlRelation("yattt_task_status", "rowid", "status_text"));

    createTableIfDoesNotExist();
    tableModel->select();
}

DBModel::~DBModel() {
    qDebug() << "DBModel destruction";
    db.close();
}

int DBModel::addEntry(const std::string &name, const std::string &description, const std::time_t startTime)
{
    qDebug() << "DBModel addEntry(" << name.c_str() << ", " << description.c_str() << ")";
    QSqlQuery query;
    QString sql;
    bool success;

    sql = QString("INSERT INTO yattt_tasks"
                  "       ('name', 'description', 'starting_time', 'status_id')"
                  "VALUES ('%1',   '%2',           %3,              %4        );")
            .arg(name.c_str())
            .arg(description.c_str())
            .arg(startTime)
            .arg("(SELECT rowid FROM yattt_task_status WHERE status_text = 'RUNNING')");
    success = query.exec(sql);
    if (!success) {
        throw std::runtime_error("'INSERT INTO' SQL command failed.\n\t" + sql.toStdString());
    }
    int id = query.lastInsertId().toInt();

    tableModel->select();
    return id;
}

std::vector<Task> DBModel::listTasks() const
{
    qDebug() << "DBModel listTasks()";
    std::vector<Task> taskList;

    QSqlQuery query;
    bool success;
    QString sql = QString("SELECT rowid, name, description, status_id, starting_time, ending_time FROM yattt_tasks;");
    success = query.exec(sql);
    if (!success) {
        throw std::runtime_error("'SELECT' SQL command failed.\n\t" + sql.toStdString());
    }
    while(query.next()) {
        int rowId = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString description = query.value(2).toString();
        int statusId = query.value(3).toInt();
        int startingTimestamp = query.value(4).toInt();
        int endingTimestamp = query.value(5).toInt();
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
        taskList.push_back(Task(rowId, name.toStdString(), description.toStdString(), statusText, startingTimestamp, endingTimestamp));
    }

    return taskList;
}

void DBModel::stopTask(int id)
{
    qDebug() << "DBModel stopTask(" << QString::number(id) << ")";
    QSqlQuery query;
    std::time_t time = std::time(nullptr);
    QString sql = QString("UPDATE yattt_tasks SET "
                          "ending_time = %2,"
                          "status_id = (SELECT rowid FROM yattt_task_status WHERE status_text = 'FINISHED')"
                          "WHERE rowid = %1;")
            .arg(id)
            .arg(time);
    bool success = query.exec(sql);
    if (!success) {
        throw std::runtime_error("'UPDATE' SQL command failed.\n\t" + sql.toStdString());
    }
}

void DBModel::populateWithTestValues()
{
    std::vector<std::map<std::string, std::string>> entries {
        {
            { "rowid", "1" },
            { "name", "Task #1" },
            { "description", "Some description" },
            { "starting_time", "0" },
            { "ending_time", "0" },
            { "status_id", "10" },
        },
        {
            { "rowid", "2" },
            { "name", "Task #2" },
            { "description", "" },
            { "starting_time", "0" },
            { "ending_time", "0" },
            { "status_id", "10" },
        },
        {
            { "rowid", "3" },
            { "name", "Task #3" },
            { "description", "Some other longer description" },
            { "starting_time", "0" },
            { "ending_time", "0" },
            { "status_id", "10" },
        },
    };

    QSqlQuery query;
    for (auto entry : entries) {
        QString sql = QString("INSERT INTO yattt_tasks VALUES(%1, '%2', '%3', %4, %5, %6)")
                .arg(entry["rowid"].c_str())
                .arg(entry["name"].c_str())
                .arg(entry["description"].c_str())
                .arg(entry["starting_time"].c_str())
                .arg(entry["ending_time"].c_str())
                .arg(entry["status_id"].c_str());
        bool success = query.exec(sql);
        if (!success) {
            throw std::runtime_error("INSERT command failed while populating the DB with test entries.");
        } else {
            qDebug() << "TEST entry added:";
            qDebug() << " - ROWID : " << entry["rowid"].c_str();
            qDebug() << " - Name : " << entry["name"].c_str();
            qDebug() << " - Description : " << entry["description"].c_str();
            qDebug() << " - Starting time : " << entry["starting_time"].c_str();
            qDebug() << " - Ending time : " << entry["ending_time"].c_str();
            qDebug() << " - Status ID : " << entry["status_id"].c_str();
        }
    }
}

void DBModel::createTableIfDoesNotExist()
{
    QSqlQuery query;
    QString sql = QString("SELECT * FROM yattt_task_status;");
    bool success = query.exec(sql);
    if (!success) {
        qDebug() << "DBModel Table yattt_task_status does not exist. Creation...";
        sql = QString("CREATE TABLE yattt_task_status ("
                      "rowid INTEGER UNIQUE, "
                      "status_text VARCHAR ( 30 ), "
                      "PRIMARY KEY( 'rowid' ))"
                      "WITHOUT ROWID;");
        success = query.exec(sql);
        if (!success) {
            throw std::runtime_error("'CREATE TABLE' SQL command failed.\n\t" + sql.toStdString());
        }
        sql = QString("INSERT INTO yattt_task_status VALUES(10, 'RUNNING');");
        success = query.exec(sql);
        if (!success) {
            throw std::runtime_error("'INSERT INTO' SQL command failed.\n\t" + sql.toStdString());
        }
        sql = QString("INSERT INTO yattt_task_status VALUES(20, 'FINISHED');");
        success = query.exec(sql);
        if (!success) {
            throw std::runtime_error("'INSERT INTO' SQL command failed.\n\t" + sql.toStdString());
        }
    } else {
        qDebug() << "DBModel Table yattt_task_status exists. Skipping creation.";
    }
    sql = QString("SELECT * FROM yattt_tasks;");
    success = query.exec(sql);
    if (!success) {
        qDebug() << "DBModel Table yattt_tasks does not exist. Creation...";
        sql = QString("CREATE TABLE yattt_tasks ("
                      "rowid INTEGER UNIQUE, "
                      "name VARCHAR(100), "
                      "description VARCHAR(200), "
                      "starting_time INTEGER, "
                      "ending_time INTEGER, "
                      "status_id INTEGER, "
                      "PRIMARY KEY('rowid'), "
                      "FOREIGN KEY(status_id) REFERENCES yattt_task_status('rowid'))"
                      "WITHOUT ROWID;");
        success = query.exec(sql);
        if (!success) {
            throw std::runtime_error("'CREATE TABLE' SQL command failed.\n\t" + sql.toStdString());
        }

        populateWithTestValues();
    } else {
        qDebug() << "DBModel Table yattt_tasks exists. Skipping creation.";
    }
}

std::shared_ptr<MainSqlTableModel> DBModel::getTableModel() const
{
    return tableModel;
}
