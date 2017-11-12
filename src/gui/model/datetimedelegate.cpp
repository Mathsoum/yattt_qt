#include "include/gui/model/datetimedelegate.h"

#include <QDebug>
#include <QDateTime>

#include <iostream>
#include <ctime>

#include "include/gui/model/customcalendarwidget.h"

DateTimeDelegate::DateTimeDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *DateTimeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const
{
    qDebug() << "[Delegate] editor created";
    auto calendar = new CustomCalendarWidget(index.data().toDateTime(), parent);
    calendar->setParent(parent);
    connect(calendar, &CustomCalendarWidget::editingFinished, this, &DateTimeDelegate::commitAndCloseEditor);
    return calendar;
}

void DateTimeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug() << "[Delegate] set editor data";
    CustomCalendarWidget *calendar = qobject_cast<CustomCalendarWidget *>(editor);
    if (!index.data().isValid() || index.data().toString().isEmpty()) {
        auto time = std::time(nullptr);
        calendar->setSelectedDate(QDateTime::fromTime_t(time));
    } else {
        calendar->setSelectedDate(index.data().toDateTime());
    }
}

void DateTimeDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    qDebug() << "[Delegate] update editor geometry";
    editor->move(option.rect.x(), option.rect.y() + option.rect.height());
    editor->repaint();
}

void DateTimeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    qDebug() << "[Delegate] set model data";
    CustomCalendarWidget *calendar = qobject_cast<CustomCalendarWidget *>(editor);
    qDebug() << "[Delegate] editor data is" << calendar->getDateTime();
    model->setData(index, QVariant::fromValue(calendar->getDateTime().toTime_t()));
}

void DateTimeDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const
{
    qDebug() << "[Delegate] destroying editor";
    QStyledItemDelegate::destroyEditor(editor, index);
}

void DateTimeDelegate::commitAndCloseEditor()
{
    qDebug() << "[Delegate] commit and close";
    CustomCalendarWidget *calendar = qobject_cast<CustomCalendarWidget *>(sender());
    emit commitData(calendar);
    emit closeEditor(calendar);
}
