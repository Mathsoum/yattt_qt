#ifndef NEWTASKDIALOG_H
#define NEWTASKDIALOG_H

#include <QDialog>

namespace Ui {
class NewTaskDialog;
}

class NewTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTaskDialog(QWidget *parent = 0);
    ~NewTaskDialog();

    QString name() const;
    QString description() const;
    QDateTime startTime() const;

private slots:
    void on_cancelButton_released();
    void on_okButton_released();

private:
    Ui::NewTaskDialog *ui;
};

#endif // NEWTASKDIALOG_H
