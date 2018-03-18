#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphwidget.h"

#include <QTextStream>
#include <QByteArray>
#include <QInputDialog>
#include <QFileDialog>
#include <cstdlib>
#include <ctime>

#include <QGraphicsScene>

Graph* gr1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gr1 = new Graph;
    gr1->widget = new GraphWidget(0, gr1);
    ui->graphicsView->setViewport(gr1->widget);
    srand(time(nullptr));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    gr1->widget->keyPressEvent(event);
}


void MainWindow::on_exit_action_triggered()
{
    exit(0);
}

void MainWindow::on_matrButton_clicked()
{
    QString matr;
    QTextStream ms(&matr);
    gr1->Inc_Matr(ms);
    ui->incEdit->setPlainText(matr);
}

void MainWindow::on_addNodeButton_clicked()
{
    QString name = ui->NodeNameEdit->text();
    if (name.length() > Numb){
        QMessageBox msg;
        msg.setText("Слишком длинное имя");
        msg.exec();
        ui->NodeNameEdit->clear();
        return;
    }
    QByteArray arr = name.toLocal8Bit();
    char* cname = arr.data();
    if (!gr1->FindElem(cname))
        gr1->AddElem(cname);
    else{
        QMessageBox msg;
        msg.setText("Элемент уже существует");
        msg.exec();
    }
    ui->NodeNameEdit->clear();
    on_matrButton_clicked();
}

void MainWindow::on_deleteNodeButton_clicked()
{
     QString name = ui->NodeNameEdit->text();
     QByteArray arr = name.toLocal8Bit();
     char* cname = arr.data();
     if (gr1->FindElem(cname))
         gr1->RemoveElem(cname);
     else{
         QMessageBox msg;
         msg.setText("Элемент не существует");
         msg.exec();
     }
     ui->NodeNameEdit->clear();
     on_matrButton_clicked();
}

void MainWindow::on_AddEdge_clicked()
{
    QString name = ui->NodeNameEdit->text();
    QByteArray arr = name.toLocal8Bit();
    char* cname = arr.data();
    Elem* el1 = gr1->FindElem(cname);
    if (!el1){
        QMessageBox msg;
        msg.setText("Элемент 1 не существует");
        msg.exec();
        ui->NodeNameEdit->clear();
        return;
    }
    bool ok;
    QString name2 = QInputDialog::getText(this, "Добавить связь", "Введите имя", QLineEdit::Normal, "", &ok);
    QByteArray arr2 = name2.toLocal8Bit();
    char* cname2 = arr2.data();
    Elem* el2 = gr1->FindElem(cname2);
    if (!el2){
        QMessageBox msg;
        msg.setText("Элемент 2 не существует");
        msg.exec();
        ui->NodeNameEdit->clear();
        return;
    }
    if (!gr1->Is_Egde(el1, el2)){
        gr1->AddEdge(el1, el2);
    }
    else{
        QMessageBox msg;
        msg.setText("Связь уже есть");
        msg.exec();
    }
    on_matrButton_clicked();
    ui->NodeNameEdit->clear();
}

void MainWindow::on_DeleteEdgeButton_clicked()
{
    QString name = ui->NodeNameEdit->text();
    QByteArray arr = name.toLocal8Bit();
    char* cname = arr.data();
    Elem* el1 = gr1->FindElem(cname);
    if (!el1){
        QMessageBox msg;
        msg.setText("Элемент не существует");
        msg.exec();
        ui->NodeNameEdit->clear();
        return;
    }
    bool ok;
    QString name2 = QInputDialog::getText(this, "Удалить связь", "Введите имя", QLineEdit::Normal, "", &ok);
    QByteArray arr2 = name2.toLocal8Bit();
    char* cname2 = arr2.data();
    Elem* el2 = gr1->FindElem(cname2);
    if (!el2){
        QMessageBox msg;
        msg.setText("Элемент 2 не существует");
        msg.exec();
        ui->NodeNameEdit->clear();
        return;
    }
    if (gr1->Is_Egde(el1, el2)){
        gr1->RemoveEdge(el1, el2);
    }
    else{
        QMessageBox msg;
        msg.setText("Связи нет");
        msg.exec();
    }
    on_matrButton_clicked();
    ui->NodeNameEdit->clear();
}

void MainWindow::on_ClearButton_clicked()
{
    gr1->Clear();
    on_matrButton_clicked();
    ui->NodeNameEdit->clear();
}

void MainWindow::on_open_action_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл");
    gr1->Clear();
    gr1->ReadFile(fileName);
    on_matrButton_clicked();
}

void MainWindow::on_save_action_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Открыть файл");
    gr1->SaveFile(fileName);
}

void MainWindow::on_gravityBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        gr1->widget->SetGravity(0);
    }
    else
        gr1->widget->SetGravity(1);
}

void MainWindow::on_colorButton_clicked()
{
    gr1->widget->RandomColors();
}

void MainWindow::on_shuffleButton_clicked()
{
    gr1->widget->shuffle();
}
