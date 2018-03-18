#ifndef GRAPH_H
#define GRAPH_H
#define SAVEITS List* t_lpos = KeepItL(); Elem* t_pos = KeepItE();
#define RESTOREITS RestoreItL(t_lpos); RestoreItE(t_pos);
#define Numb 80

#include <iostream>
#include <cstring>
#include <QTextStream>
#include <QString>
#include <QFile>

#include "graphwidget.h"

using namespace std;

typedef struct List List;

typedef struct Elem{ //Элементы графа
    Elem() = default;
    char name[Numb];
    Elem* next=nullptr;
    List* childs=nullptr; //Дети элемента
}Elem;

typedef struct List{
    List() = default;
    char name[Numb];
    Elem* node = nullptr; //Сам элемент
    List* next = nullptr;
}List;

class Graph
{
public:
    Graph();
    ~Graph();
    void Clear(); //Очистка

    Elem* it(); //Итератор через вершины
    List* it(Elem* el); //Итератор через сыновей
    void ResetIts();

    void ReadFile(QString fileName); //Считать из файла
    void SaveFile(QString fileName); //Сохранить в файл

    void AddElem(char* name); //Добавить элемент
    void AddEdge(Elem* el1, Elem* el2); //Добавить линию
    void AddEdge(Elem* el1, char* name); //Добавить "заготовку" для линии
    bool Solve(); //Разрешить зависимости "заготовок" для линий
    void RemoveElem(char* name); //Удалить элемент
    void RemoveEdge(Elem* el1, Elem* el2); //Удалить линию

    Elem* FindElem(char* name); //Найти элемент
    int CountChildren(Elem* el); //Сколько детей
    int CountElems(); //Сколько элементов

    bool Is_Egde(Elem* el1, Elem* el2); //Есть ли связь от 1 к 2

    int Max_Width();
    void Inc_Matr(QTextStream& os); //Матрица инцидентности

    Elem* operator[](int i);

    GraphWidget* widget;

protected:
    Elem* gr;
    Elem* pos;
    List* lpos;
private:
    void Clear(List* ls);
    void Clear(Elem* gr);

    Elem* KeepItE();
    List* KeepItL();
    void RestoreItE(Elem* t_pos);
    void RestoreItL(List* t_lpos);

    void RemoveEdges(Elem* el);
};

#endif // GRAPH_H
