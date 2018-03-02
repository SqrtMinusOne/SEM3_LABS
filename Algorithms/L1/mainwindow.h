#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <opt_task.h>
#include <item.h>
#include <QListWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    Opt_task op;
    void out_sol(QStack<Item> s);
    void out_parm(QStack<try_parm> series);
    ~MainWindow();

private slots:


    void on_pushButton_clicked();

    void on_randButton_clicked();

    void on_delButton_clicked();

    void on_clearButton_clicked();

    void on_solveButton_clicked();

    void on_clearButton_2_clicked();


    void on_stepButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
