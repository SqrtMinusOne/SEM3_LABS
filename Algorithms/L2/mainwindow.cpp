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
    char ch[80] = "hren";
    gr1.AddElem("lol");
    gr1.AddElem("kek");
    gr1.AddElem(ch);
    QString q;
    QTextStream str(&q);
    gr1.AddEdge(gr1.FindElem("lol"), gr1.FindElem("kek"));
    gr1.AddEdge(gr1[1], gr1[2]);
    gr1.AddEdge(gr1[1], gr1[0]);
    gr1.RemoveEdge(gr1[1], gr1[2]);
    gr1.Inc_Matr(str);
    ui->incEdit->setPlainText(q);
}
