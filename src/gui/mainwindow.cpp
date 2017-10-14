#include "include/gui/mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlRelationalTableModel>
#include <QDateTime>

#include "include/model/dbmodel.h"
#include "include/gui/dialogs/newtaskdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dbModel = std::make_shared<DBModel>();

    ui->tableView->setModel(dbModel->getTableModel());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAddTask_triggered()
{
    NewTaskDialog *dialog = new NewTaskDialog(this);
    int result = dialog->exec();

    if (result == QDialog::Accepted) {
        dbModel->addEntry(dialog->name().toStdString(), dialog->description().toStdString(), dialog->startTime().toTime_t());
    }


}
