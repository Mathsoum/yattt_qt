#ifndef MAINSQLTABLEMODEL_H
#define MAINSQLTABLEMODEL_H

#include <QSqlRelationalTableModel>
#include <QSqlDatabase>

#include <memory>

class DBModel;

class MainSqlTableModel : public QSqlRelationalTableModel
{
public:
    MainSqlTableModel(QObject *parent = nullptr, const QSqlDatabase &db = QSqlDatabase());

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // MAINSQLTABLEMODEL_H
