#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QKeyEvent>
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
    void update_matr();
    int get_speed();

public slots:
    void One_Step();

protected:
    void keyPressEvent(QKeyEvent *event) override;

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

    void on_colorButton_clicked();

    void on_shuffleButton_clicked();

    void on_pushButton_clicked();

    void on_clrMarksButton_clicked();

    void on_desButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
};

#endif // MAINWINDOW_H
