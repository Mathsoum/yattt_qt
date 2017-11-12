#include "include/gui/model/mainsqltablemodel.h"

#include "include/model/dbmodel.h"

#include <QSqlRelationalTableModel>
#include <QCalendarWidget>
#include <QDateTime>
#include <QDebug>

MainSqlTableModel::MainSqlTableModel(QObject *parent, const QSqlDatabase &db)
    : QSqlRelationalTableModel(parent, db)
{
    setEditStrategy(QSqlTableModel::OnFieldChange);
}

MainSqlTableModel::~MainSqlTableModel()
{
    qDebug() << "[MainSqlTableModel] destructor";
}

QVariant MainSqlTableModel::data(const QModelIndex &index, int role) const
{
    QVariant sqlData = QSqlRelationalTableModel::data(index, role);
    if ((index.column() == 3 || index.column() == 4) && !sqlData.toString().isEmpty()) {
        if (role == Qt::DisplayRole) {
            QDateTime timestamp;
            timestamp.setTime_t(sqlData.toInt());
            sqlData = timestamp;
        }
    }
    return sqlData;
}

QVariant MainSqlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch(section) {
        case 0:
            return "#";
        case 1:
            return "Name";
        case 2:
            return "Descritpion";
        case 3:
            return "Starting time";
        case 4:
            return "Ending time";
        case 5:
            return "Status";
        }
    }
    return QSqlRelationalTableModel::headerData(section, orientation, role);
}
