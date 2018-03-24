#ifndef OPT_TASK_H
#define OPT_TASK_H

#include <iostream>
#include <QStack>
#include <QQueue>
#include <QList>
#include <QtDebug>
#include <QFile>
#include <QByteArray>
#include <item.h>

class try_parm{
public:
    try_parm(int it, int twt, int avt){i=it; tw=twt; av=avt; }
    try_parm() = default;
    int i;
    int tw;
    int av;
    QStack<Item> s;//Вариант для запуска
};

class Opt_task{
public:
    Opt_task(int nt); //Конструктор
    Opt_task() = default;
    QList<Item> all; //Стек из всех предметов
    QStack<Item> s;//Текущий вариант
    QStack<Item> opts;//Оптимальный вариант
    QStack<try_parm> series;//Стек запусков функции
    int totv_all(); //Суммарная ценность массива
    void try_item(); //Инициализация  
    void try_item(int i, int tw, int av); //Рекурсивное решение
    void try_item(int i, int tw, int av, bool steps); //Вариант для пошаговой обработки
    void try_item(try_parm parm);
    void setlimw(int i);
    void setlimw(QString i);
    void clrzeros(); //Очистка от мусора
    int g_totw(QStack<Item> s); //Суммарный вес сета
    int g_totv(QStack<Item> s); //Суммарная ценность сета
    int g_nums() {return nums; } //Вывод количества решений
    void out(QStack<Item> s); //Вывод сета
    void make_arr();
    bool steps = 0;
    bool go = 1;
private:  
    void try_incl(int i, int tw, int av);
    void try_unincl(int i, int tw, int av);
    int n;
    int limw = 0; //Максимальный вес
    int totw = 0; //Вес текущей выборки
    int maxv = 0; //Максимальная ценость оптимальной выборки
    int nums = 0; //Количество решений

};


#endif // OPT_TASK_H
