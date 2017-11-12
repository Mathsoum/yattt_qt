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
    virtual ~MainSqlTableModel();

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    bool setData(const QModelIndex &item, const QVariant &value, int role) override;
};

#endif // MAINSQLTABLEMODEL_H
