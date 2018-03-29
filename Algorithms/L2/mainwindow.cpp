#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphwidget.h"

#include <QTextStream>
#include <QByteArray>
#include <QInputDialog>
#include <QFileDialog>
#include <cstdlib>
#include <ctime>
#include <QTimer>

#include <QGraphicsScene>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gr1 = new Graph;
    gr1->widget = new GraphWidget(0, gr1, this);
    ui->graphicsView->setViewport(gr1->widget);
    srand(time(nullptr));
    timer = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_matr()
{
    on_matrButton_clicked();
}

int MainWindow::get_speed()
{
    return ui->speedSlider->value();
}

void MainWindow::One_Step() //Один шаг алгоритма
{
    if ((!ui->cycleEdit->text().isEmpty()) && (gr1->Stack.isEmpty())){ //Последний шаг
        QMessageBox msg;
        msg.setText("Цикл найден");
        msg.exec();
        if (timer){
            timer->stop();
            delete timer;
            timer = nullptr;
            return;
        }
    }
    bool res = gr1->Euler(); //Один шаг делает метод в Graph
    QString str;
    QTextStream strm(&str);
    for (auto it : gr1->SE){
           strm << it->name << " "; //Вывод данных стека для цикла Эйлера
    }
    std::reverse(str.begin(), str.end());
    ui->cycleEdit->setText(str);
    str.clear();
    strm.reset();
    for (auto it : gr1->Stack){
           strm << it->name << " "; //Вывод данных временного цикла
    }
    std::reverse(str.begin(), str.end());
    ui->stackEdit->setText(str);
    if (res){ //Остановка таймера, если что-то не так
        timer->stop();
        delete timer;
        timer = nullptr;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    gr1->widget->keyPressEvent(event); //Передача управления виджету
}


void MainWindow::on_exit_action_triggered()
{
    exit(0); //Выход из программы
}

void MainWindow::on_matrButton_clicked() //Построение матрицы
{
    QString matr;
    QTextStream ms(&matr);
    gr1->Inc_Matr(ms);
    ui->incEdit->setPlainText(matr);
}

void MainWindow::on_addNodeButton_clicked() //Добавление вершины
{
    QString name = ui->NodeNameEdit->text();
    if (name.length() > Numb){
        QMessageBox msg;
        msg.setText("Слишком длинное имя");
        msg.exec();
        ui->NodeNameEdit->clear();
        return;
    }
    QByteArray arr = name.toLocal8Bit(); //Конвертация QString в char*
    char* cname = arr.data();
    if (!gr1->FindElem(cname))
        gr1->AddElem(cname);
    else{
        QMessageBox msg;
        msg.setText("Элемент уже существует");
        msg.exec();
    }
    ui->NodeNameEdit->clear();
    on_matrButton_clicked(); //После каждой процедуры матрица обновляется
}

void MainWindow::on_deleteNodeButton_clicked() //Удаление вершины
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

void MainWindow::on_DeleteEdgeButton_clicked() //Удаление ребра
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

void MainWindow::on_ClearButton_clicked() //Сброс графа
{
    gr1->Clear();
    on_matrButton_clicked();
    ui->NodeNameEdit->clear();
    gr1->widget->update();
}

void MainWindow::on_open_action_triggered() //Открытие из файла
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл");
    gr1->Clear();
    gr1->ReadFile(fileName);
    on_matrButton_clicked();
}

void MainWindow::on_save_action_triggered() //Сохранение в файл
{
    QString fileName = QFileDialog::getSaveFileName(this, "Открыть файл");
    gr1->SaveFile(fileName);
}

void MainWindow::on_gravityBox_stateChanged(int arg1) //Изменение гравитации
{
    if (arg1 == 0){
        gr1->widget->SetGravity(0);
    }
    else
        gr1->widget->SetGravity(1);
}

void MainWindow::on_colorButton_clicked() //Рандомизация цветов
{
    gr1->widget->RandomColors();
}

void MainWindow::on_shuffleButton_clicked() //Перетасовка вершин
{
    gr1->widget->shuffle();
}

void MainWindow::on_pushButton_clicked() //Запуск алгоритма
{
    if (ui->stepBox->isChecked()) //Если пошаговое выполнение, просто выполнить один шаг
        One_Step();
    else if (!timer){
        timer = new QTimer(this); //Иначе выполнение по таймеру
        connect(timer, SIGNAL(timeout()), this, SLOT(One_Step()));
        timer->start(ui->speedSlider->value());
    }
}

void MainWindow::on_clrMarksButton_clicked() //Сброс алгоритма
{
    gr1->ResetEuler();
    gr1->ClearMarks();
    ui->stackEdit->clear();
    ui->cycleEdit->clear();
    if (timer){
        timer->stop();
        delete timer;
        timer = nullptr;
    }

}

void MainWindow::on_desButton_clicked() //Убрать ориентацию графа
{
    gr1->Desorientate();
    gr1->widget->update();
    on_matrButton_clicked();
}

void MainWindow::on_speedSlider_sliderMoved(int position) //Изменение скорости
{
    if (timer){
        timer->setInterval(position);
    }
}

void MainWindow::on_guessButoon_clicked() //Угадать цикл
{
    ui->speedSlider->setValue(0);
    if (!timer)
        on_pushButton_clicked();
    QPalette p1 = ui->cycleEdit->palette(); //Изменение цвета шрифта
    QPalette* p2 = new QPalette(p1);
    p2->setColor(QPalette::Text, Qt::white);
    ui->cycleEdit->setPalette(*p2);
    while (timer){
        app->processEvents(); //Пока идет таймер, обрабатывать ивенты приложения
    }
    if (!(ui->stackEdit->text().isEmpty()) || (ui->cycleEdit->text().isEmpty())){ //Если некорректно завершилось
        ui->cycleEdit->setPalette(p1);
        delete p2;
        return;
    }
    QString txt; int g = gr1->SE.count()-1; bool alright = 0;
    do{ //Цикл с угадыванием
        alright = 1;
        QInputDialog* dia = new QInputDialog;
        dia->setInputMode(QInputDialog::TextInput);
        dia->setWindowTitle("Угадать цикл");
        dia->setLabelText("Введите следующую вершину цикла");
        dia->setCancelButtonText("Всё");
        dia->exec();
        txt = dia->textValue();
        if (txt.isSimpleText()){
            bool res = !(QString::compare(txt, gr1->SE[g]->name));
            if ((!res) && (!txt.isEmpty())){
                QMessageBox box;
                box.setText("Неверно!");
                box.exec();
                break;
            }
        }
        g--;
        delete dia;
    } while (!txt.isEmpty() && (g>=0));
    ui->cycleEdit->setPalette(p1); //Восстановление цвета
    delete p2;
    if (alright){ //Подсчёт угаданного
        QString final;
        QTextStream finals(&final);
        finals << "Correct: " << gr1->SE.count() - g - 1 << " of " << gr1->SE.count() << endl;;
        QMessageBox box;
        box.setText(final);
        box.exec();
    }
}
