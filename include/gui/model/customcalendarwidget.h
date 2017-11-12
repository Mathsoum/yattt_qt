#ifndef CUSTOMCALENDARWIDGET_H
#define CUSTOMCALENDARWIDGET_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class CustomCalendarWidget;
}

class CustomCalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomCalendarWidget(const QDateTime &dateTime = QDateTime(), QWidget *parent = 0);
    ~CustomCalendarWidget();

    void setSelectedDate(const QDateTime &dateTime);
    QDateTime getDateTime() const;

private slots:
    void mouseDoubleClickEvent(QMouseEvent *);
    void keyReleaseEvent(QKeyEvent *event);

    void paintEvent(QPaintEvent *event);

private: // Methods
    void validate();

signals:
    void editingFinished();

private: // Attributes
    Ui::CustomCalendarWidget *ui;
};

#endif // CUSTOMCALENDARWIDGET_H
