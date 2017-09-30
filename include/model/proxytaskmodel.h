#ifndef PROXYTASKMODEL_H
#define PROXYTASKMODEL_H

class QSqlTableModel;

class ProxyTaskModel
{
public:
    ProxyTaskModel(QSqlTableModel *baseModel);
    virtual ~ProxyTaskModel();

private:
    QSqlTableModel* sqlTableModel;


};

#endif // PROXYTASKMODEL_H
