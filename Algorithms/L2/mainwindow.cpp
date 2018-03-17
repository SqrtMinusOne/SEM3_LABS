#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Graph gr1;
    gr1.AddElem("lol");
    gr1.AddElem("kek");
    QString q;
    QTextStream str(&q);
    gr1.Inc_Matr(str);
    ui->incEdit->setPlainText(q);
    int a = gr1.CountElems();
    Elem* el = gr1.FindElem("kek");
}
