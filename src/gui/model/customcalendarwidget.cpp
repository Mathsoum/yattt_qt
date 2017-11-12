#include "include/gui/model/customcalendarwidget.h"
#include "ui_customcalendarwidget.h"

#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

CustomCalendarWidget::CustomCalendarWidget(const QDateTime &dateTime, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomCalendarWidget)
{
    ui->setupUi(this);

    ui->calendarWidget->setVerticalHeaderFormat(QCalendarWidget::ISOWeekNumbers);

    ui->calendarWidget->setSelectedDate(dateTime.date());
    ui->timeEdit->setTime(dateTime.time());
}

CustomCalendarWidget::~CustomCalendarWidget()
{
    delete ui;
}

void CustomCalendarWidget::setSelectedDate(const QDateTime &dateTime)
{
    ui->calendarWidget->setSelectedDate(dateTime.date());
    ui->timeEdit->setTime(dateTime.time());
}

QDateTime CustomCalendarWidget::getDateTime() const
{
    return QDateTime(ui->calendarWidget->selectedDate(), ui->timeEdit->time());
}

void CustomCalendarWidget::mouseDoubleClickEvent(QMouseEvent */*event*/)
{
    qDebug() << "[CustomCalendarWidget] Mouse double clicked !";
    validate();
}

void CustomCalendarWidget::keyReleaseEvent(QKeyEvent *event)
{
    qDebug() << "[CustomCalendarWidget] Key released event !";
    if (event->key() == Qt::Key_Enter) {
        event->accept();
        validate();
    } else {
        QWidget::keyReleaseEvent(event);
    }
}

void CustomCalendarWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawRect(0, 0, width() - 1, height() - 1);
    QWidget::paintEvent(event);
}

void CustomCalendarWidget::validate()
{
    qDebug() << "Selection is " << ui->calendarWidget->selectedDate() << " --- " << ui->timeEdit->time();
    emit editingFinished();
}
