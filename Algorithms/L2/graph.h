#ifndef GRAPH_H
#define GRAPH_H
#define SAVEITS List* t_lpos = KeepItL(); Elem* t_pos = KeepItE();
#define RESTOREITS RestoreItL(t_lpos); RestoreItE(t_pos);
#define Numb 80
#define Wid 800
#define Hei 600

#include <iostream>
#include <cstring>
#include <QTextStream>
#include <QString>
#include <QFile>
#include <QStack>
#include <QMessageBox>

#include "graphwidget.h"

using namespace std;

typedef struct List List;

typedef struct Elem{ //Элементы графа
    Elem() = default;
    char name[Numb];
    Elem* next=nullptr;
    List* childs=nullptr; //Дети элемента
    Node* node;
}Elem;

typedef struct List{
    List() = default;
    char name[Numb];
    bool mark = false;
    Elem* node = nullptr; //Сам элемент
    List* next = nullptr;
    Edge* edge;
}List;

class Graph
{
public:
    Graph();
    ~Graph();
    void Clear(); //Очистка

    Elem* it(); //Итератор через вершины
    List* it(Elem* el, bool marked = 1); //Итератор через сыновей
    void ResetIts();

    void ReadFile(QString fileName); //Считать из файла
    void SaveFile(QString fileName); //Сохранить в файл

    char* GetMinStupidName();
    char* GetLastStupidName();

    void AddElem(char* name); //Добавить элемент
    void AddEdge(Elem* el1, Elem* el2); //Добавить линию
    void AddEdge(Elem* el1, char* name); //Добавить "заготовку" для линии
    bool Solve(); //Разрешить зависимости "заготовок" для линий
    void RemoveElem(char* name); //Удалить элемент
    void RemoveEdge(Elem* el1, Elem* el2); //Удалить линию
    void RemoveEdges(Elem* el); //Удалить связи элемента
    void RenameElem(char* oldname, char* newname); //Переименовать элемент

    Elem* FindElem(char* name); //Найти элемент
    int CountChildren(Elem* el, bool marked = 1); //Сколько детей
    int CountElems(); //Сколько элементов

    bool Is_Egde(Elem* el1, Elem* el2); //Есть ли связь от 1 к 2

    int Max_Width();
    void Inc_Matr(QTextStream& os); //Матрица инцидентности

    void Euler();
    void ResetEuler();
    void ClearMarks();

    Elem* operator[](int i);

    GraphWidget* widget;
    QStack<Elem*> SE;
    QStack<Elem*> Stack;
    Elem* v0 = nullptr;
    bool steps = 0;
protected:
    int stupidnames = 0;

    Elem* gr;
    Elem* pos;
    List* lpos;
private:
    void Clear(List* ls, Elem *el);
    void Clear(Elem* gr);

    Elem* KeepItE();
    List* KeepItL();
    void RestoreItE(Elem* t_pos);
    void RestoreItL(List* t_lpos);


};

#endif // GRAPH_H
