#include "include/gui/mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlRelationalTableModel>
#include <QDateTime>

#include "include/model/dbmodel.h"
#include "include/gui/dialogs/newtaskdialog.h"
#include "include/gui/model/mainsqltablemodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("YATTT  \u2014  Yet Another Time Tracking Tool");

    dbModel = std::make_shared<DBModel>();
    ui->tableView->setModel(dbModel->getTableModel().get());
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
