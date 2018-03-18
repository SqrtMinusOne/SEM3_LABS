#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>

#include "graph.h"

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

    void on_exit_action_triggered();

    void on_matrButton_clicked();

    void on_addNodeButton_clicked();

    void on_deleteNodeButton_clicked();

    void on_AddEdge_clicked();

    void on_DeleteEdgeButton_clicked();

    void on_ClearButton_clicked();

    void on_open_action_triggered();

    void on_save_action_triggered();

    void on_gravityBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
