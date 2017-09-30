#include "include/model/proxytaskmodel.h"

#include <QSqlTableModel>

ProxyTaskModel::ProxyTaskModel(QSqlTableModel* baseModel)
    : sqlTableModel(baseModel)
{

}

ProxyTaskModel::~ProxyTaskModel()
{
    delete sqlTableModel;
}
