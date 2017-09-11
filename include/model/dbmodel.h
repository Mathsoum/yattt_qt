#ifndef DBMODEL_H
#define DBMODEL_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <string>
#include <vector>

#include "include/model/task.h"

class DBModel
{
public:
    DBModel();
    virtual ~DBModel();

    void addEntry(const std::string &name, const std::string &description);
    std::vector<Task> listTasks() const;

private: // Methods
    void createTableIfDoesNotExist();

private: // Attributes
    QSqlDatabase db;
};

#endif // DBMODEL_H
