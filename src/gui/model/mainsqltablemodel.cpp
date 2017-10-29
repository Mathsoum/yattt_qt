#include "include/gui/model/mainsqltablemodel.h"

#include "include/model/dbmodel.h"

#include <QSqlRelationalTableModel>
#include <QDateTime>

MainSqlTableModel::MainSqlTableModel(QObject *parent, const QSqlDatabase &db)
    : QSqlRelationalTableModel(parent, db)
{
}

QVariant MainSqlTableModel::data(const QModelIndex &index, int role) const
{
    QVariant sqlData = QSqlRelationalTableModel::data(index, role);
    if (role == Qt::DisplayRole && (index.column() == 2 || index.column() == 3) && !sqlData.toString().isEmpty()) {
        QDateTime timestamp;
        timestamp.setTime_t(sqlData.toInt());
        sqlData = timestamp.toString(Qt::SystemLocaleShortDate);
    }
    return sqlData;
}

QVariant MainSqlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch(section) {
        case 0:
            return "Name";
        case 1:
            return "Descritpion";
        case 2:
            return "Starting time";
        case 3:
            return "Ending time";
        case 4:
            return "Status";
        }
    }
    return QSqlRelationalTableModel::headerData(section, orientation, role);
}
