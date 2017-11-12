#ifndef DBMODEL_H
#define DBMODEL_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <memory>
#include <string>
#include <vector>
#include <ctime>

#include "include/model/task.h"

class QSqlRelationalTableModel;

class DBModel
{
public:
    DBModel();
    virtual ~DBModel();

    int addEntry(const std::string &name, const std::string &description, const time_t startTime = std::time(nullptr));
    std::vector<Task> listTasks() const;
    void stopTask(int id);

    std::shared_ptr<QSqlRelationalTableModel> getTableModel() const;

    void populateWithTestValues();

private: // Methods
    void createTableIfDoesNotExist();

private: // Attributes
    QSqlDatabase db;

    std::shared_ptr<QSqlRelationalTableModel> tableModel;
};

#endif // DBMODEL_H
