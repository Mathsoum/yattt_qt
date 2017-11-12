#ifndef DATETIMEDELEGATE_H
#define DATETIMEDELEGATE_H

#include <QStyledItemDelegate>

#include <memory>

class CustomCalendarWidget;

class DateTimeDelegate : public QStyledItemDelegate
{
public:
    DateTimeDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const override;
    void setEditorData(QWidget* editor, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem &option, const QModelIndex &) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void destroyEditor(QWidget *editor, const QModelIndex& index) const override;

private slots:
    void commitAndCloseEditor();
    void editionFinished();
};

#endif // DATETIMEDELEGATE_H
