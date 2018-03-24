#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <QFileDialog>
#include <qDebug>
#include <ctime>
#include <item.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(nullptr));
}

void MainWindow::out_sol(QStack<Item> s)
{
    ui->solWidget->clear();
    for (auto it : s){
        Item item;
        item.set(it);
        ui->solWidget->addItem(item.wItem);
    }
    ui->weightNum->display(op.g_totw(s));
    ui->valueNum->display(op.g_totv(s));
}

void MainWindow::out_parm(QStack<try_parm> series)
{
    ui->qList->clear();
    for (auto it: series){
        QString str;
        QTextStream strm(&str);
        strm << "Element " << it.i << ". There is " << it.s.count() << " elements in list";
        ui->qList->addItem(str);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Item it;
    it.set(ui->weightEdit->text(), ui->valueEdit->text());
    if (it.ok()){
        ui->listWidget->addItem(it.wItem);
    }
    op.all.push_back(it);
    ui->weightEdit->clear();
    ui->valueEdit->clear();
    ui->listNum->display(ui->listWidget->count());
}

void MainWindow::on_randButton_clicked()
{
    Item it;
    it.set(ui->weightEdit->text(), ui->valueEdit->text(), 1);
    if (it.ok()){
        ui->listWidget->addItem(it.wItem);
    }
    op.all.push_back(it);
    ui->listNum->display(ui->listWidget->count());
}

void MainWindow::on_delButton_clicked()
{
    if (ui->listWidget->count()){
        ui->listWidget->takeItem(ui->listWidget->count()-1);
        Item it;
        op.clrzeros();
        op.all.pop_back();
    }
    ui->listNum->display(ui->listWidget->count());
}

void MainWindow::on_clearButton_clicked()
{
    ui->listWidget->clear();
    op.all.clear();
    ui->listNum->display(ui->listWidget->count());
}

void MainWindow::on_solveButton_clicked()
{
    op.steps = 0;
    op.setlimw(ui->limwEdit->text());
    op.clrzeros();
    op.try_item();  
    out_sol(op.opts);
    ui->stepNum->display(op.g_nums());
}


void MainWindow::on_clearButton_2_clicked()
{
    op.go = 1;
    op.series.clear();
    ui->solWidget->clear();
    ui->weightNum->display(0);
    ui->valueNum->display(0);
    ui->stepNum->display(0);
    ui->qList->clear();
}


void MainWindow::on_stepButton_clicked()
{
    op.steps = 1;
    op.setlimw(ui->limwEdit->text());
    if (op.series.isEmpty()){
        if (op.go){
            op.go = 0;
            op.clrzeros();
            op.try_item();
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("Конец");
            msgBox.exec();
        }
    }
    else{
        try_parm parm = op.series.pop();
        out_sol(parm.s);
        op.out(parm.s);
        QStack<Item> temp;
        op.try_item(parm);
        op.s = temp;
        ui->stepNum->display(ui->stepNum->value()+ 1);
    }
    out_parm(op.series);
}

void MainWindow::on_pushButton_2_clicked()
{
    out_sol(op.opts);
}

void MainWindow::on_pushButton_3_clicked()
{
    on_clearButton_clicked();
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл");
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream file1s(&file);
    QString str;
    int w; int v;
    str = file1s.readLine();
    ui->limwEdit->setText(str);
    while (!file1s.atEnd()){
        str = file1s.readLine();
        QStringList strl = str.split(' ');
        v = strl.at(0).toInt();
        w = strl.at(1).toInt();
        Item it;
        it.set(w, v);
        if (it.ok()){
            ui->listWidget->addItem(it.wItem);
        }
        op.all.push_back(it);
        ui->listNum->display(ui->listWidget->count());
    }
}
