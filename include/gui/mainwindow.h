#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

class DBModel;
class QSqlTableModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAddTask_triggered();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<DBModel> dbModel;
};

#endif // MAINWINDOW_H
