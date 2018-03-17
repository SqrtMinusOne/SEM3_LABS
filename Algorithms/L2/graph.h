#ifndef GRAPH_H
#define GRAPH_H
#define SAVEITS List* t_lpos = KeepItL(); Elem* t_pos = KeepItE();
#define RESTOREITS RestoreItL(t_lpos); RestoreItE(t_pos);
#define Numb 80

#include <iostream>
#include <cstring>
#include <QTextStream>

using namespace std;

typedef struct List List;

typedef struct Elem{ //Элементы графа
    char name[Numb];
    Elem* next = nullptr;
    List* childs = nullptr; //Дети элемента
}Elem;

typedef struct List{
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

    void AddElem(char* name); //Добавить элемент
    Elem* FindElem(char* name); //Найти элемент
    //void AddEdge(Elem* el1, Elem* el2);

    int CountChildren(Elem* el); //Сколько детей
    int CountElems(); //Сколько элементов

    bool Is_Egde(Elem* el1, Elem* el2); //Есть ли связь от 1 к 2

    int Max_Width();
    void Inc_Matr(QTextStream& os); //Матрица инцидентности

    Elem* operator[](int i);
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
};

#endif // GRAPH_H
