#ifndef DBMODEL_H
#define DBMODEL_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <string>

class DBModel
{
public:
    DBModel();
    virtual ~DBModel();

    void addEntry(const std::string &name, const std::string &description);

private: // Methods
    void createTableIfNotExists();

private: // Attributes
    QSqlDatabase db;
};

#endif // DBMODEL_H
