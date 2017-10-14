#include "include/gui/dialogs/newtaskdialog.h"
#include "ui_newtaskdialog.h"

#include <QMessageBox>

NewTaskDialog::NewTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTaskDialog)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}

NewTaskDialog::~NewTaskDialog()
{
    delete ui;
}

QString NewTaskDialog::name() const
{
    return ui->nameLineEdit->text();
}

QString NewTaskDialog::description() const
{
    return ui->descriptionLineEdit->text();
}

QDateTime NewTaskDialog::startTime() const
{
    return ui->dateTimeEdit->dateTime();
}

void NewTaskDialog::on_cancelButton_released()
{
    reject();
}

void NewTaskDialog::on_okButton_released()
{
    if (ui->nameLineEdit->text().isEmpty()) {
        QMessageBox::critical(this, tr("Missing name."), tr("You muse specify a task name."));
    } else {
        accept();
    }
}
