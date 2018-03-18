#include "graph.h"
#include <cstdio>

Graph::Graph()
{
    gr = nullptr;
    ResetIts();
}

Graph::~Graph()
{
    Clear();
}

void Graph::Clear()
{
    Clear(gr);
    gr = nullptr;
}

void Graph::Clear(List *ls, Elem* el)
{
    if (ls != nullptr) {
        if (ls->next != nullptr)
            Clear(ls->next, el);
        RemoveEdge(el, ls->node);
    }
}

void Graph::Clear(Elem *gr)
{
    if (gr){
        if (gr->next != nullptr) {
            Clear(gr->next);
        }
        Clear(gr->childs, gr);
        RemoveElem(gr->name);
    }
}

Elem *Graph::it()
{
    if (pos == nullptr)
        pos = gr;
    else{
        if (gr){
            pos = pos->next;
        }
    }
    return pos;
}

List *Graph::it(Elem *el)
{
    if (el == nullptr)
        lpos = nullptr;
    else{
        if (lpos == nullptr){
            lpos = el->childs;
        }
        else{
            lpos = lpos->next;
        }
    }
    return lpos;
}

void Graph::ResetIts()
{
    lpos = nullptr;
    pos = nullptr;
}

void Graph::ReadFile(QString fileName)
{
    SAVEITS;
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream file1s(&file);
    QString str;
    QString tmp;   
    int i; int k = 0;
    while (!file1s.atEnd()){
        str = file1s.readLine();
        QStringList strl = str.split(' ');
        QByteArray arr;
        arr = strl.at(0).toLocal8Bit();
        char* name = arr.data();
        AddElem(name);
        for (i=1; i < strl.size(); i++){
            arr = strl.at(i).toLocal8Bit();
            name = arr.data();
            AddEdge(this->operator [](k), name);
        }
        k++;
    }
    Solve();
    file.close();
    RESTOREITS;
}

void Graph::SaveFile(QString fileName)
{
    SAVEITS;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream files(&file);
    Elem* el;
    List* ls;
    while ((el = it())!=nullptr){
        files << el->name << " ";
        while ((ls = it(el))!=nullptr){
            files << ls->name << " ";
        }
        files << "\r\n";
    }
    file.close();
    RESTOREITS;
}

char *Graph::GetMinStupidName()
{
    char* name = new char[80];
    sprintf(name, "%d", stupidnames);
    while (FindElem(name)){
        stupidnames++;
        sprintf(name, "%d", stupidnames);
    }
    return name;
}

char *Graph::GetLastStupidName()
{
    char* name = new char[80];
    sprintf(name, "%d", stupidnames);
    return name;
}

void Graph::AddElem(char *name)
{
    SAVEITS;
    Elem* el;
    if (!gr){ //Если добавляется первый элемент
        gr = new Elem;
        strcpy_s(gr->name, Numb, name);
        gr->node = new Node(widget);
        gr->node->name = (gr->name);
        widget->centerNode = gr->node;
        widget->scene()->addItem(widget->centerNode);
        widget->centerNode->setPos(rand()%Wid - Wid/2 ,rand()%Hei - Hei/2);

    }
    else{
        while ((el = it())->next!=nullptr);
        el->next = new Elem;
        el = el->next;
        strcpy_s(el->name, Numb, name);
        el->node = new Node(widget);
        el->node->name = el->name;
        el->node->setPos(rand()%Wid - Wid/2 ,rand()%Hei - Hei/2);
        widget->scene()->addItem(el->node);

    }
    RESTOREITS;
}

Elem *Graph::FindElem(char *name)
{
    SAVEITS;
    Elem* el;
    bool res = 0;
    while ((el = it())!=nullptr){
        res = (strncmp(name, el->name, Numb))==0;
        if (res)
            break;
    }
    RESTOREITS;
    return el;
}

void Graph::AddEdge(Elem *el1, Elem *el2)
{
    SAVEITS;
    List* ls;
    if (el1 && el2){
        if (!el1->childs){
            el1->childs = new List;
            strcpy_s(el1->childs->name, el2->name);
            el1->childs->node = el2;
            el1->childs->edge = new Edge(el1->node, el2->node);
            widget->scene()->addItem(el1->childs->edge);
        }
        else{
            while ((ls = it(el1))->next!=nullptr);
            ls->next = new List;
            ls = ls->next;
            strcpy_s(ls->name, el2->name);
            ls->node = el2;
            ls->edge = new Edge(el1->node, el2->node);
            widget->scene()->addItem(ls->edge);
        }
    }
    RESTOREITS;
}

void Graph::AddEdge(Elem *el1, char *name)
{
    SAVEITS;
    List* ls;
    if (el1){
        if (!el1->childs){
            el1->childs = new List;
            strcpy_s(el1->childs->name, name);
        }
        else{
            while ((ls = it(el1))->next!=nullptr);
            ls->next = new List;
            ls = ls->next;
            strcpy_s(ls->name, name);
        }
    }
    RESTOREITS;
}

bool Graph::Solve()
{
    SAVEITS;
    bool res = 1;
    Elem* el;
    List* ls;
    Elem* el2;
    while ((el = it())!=nullptr){
        while ((ls = it(el))!=nullptr){
            if (ls->node == nullptr){
                el2 = FindElem(ls->name);
                if (el2){
                    ls->node = el2;
                    ls->edge = new Edge(el->node, el2->node);
                    widget->scene()->addItem(ls->edge);
                }
                else
                    res = 0;
            }
        }
    }
    RESTOREITS;
    return res;
}

void Graph::RemoveElem(char *name)
{
    SAVEITS;
    if (gr){
        Elem* el = gr;
        bool res = strncmp(name, el->name, Numb) == 0;
        if (!res){
            while (((el = it())->next)!=nullptr){
                res = strncmp(el->next->name, name, Numb) == 0;
                if (res)
                    break;
            }
            if (res){
                RemoveEdges(el->next);
                widget->scene()->removeItem(el->next->node);
                delete el->next->node;
                Elem* el2 = el->next->next;
                delete el->next;
                el->next = el2;
            }
        }
        else{
            RemoveEdges(gr);
            widget->scene()->removeItem(gr->node);
            delete gr->node;
            Elem* el2 = gr->next;
            delete gr;
            gr = el2;
        }
    }
    RESTOREITS;
}

void Graph::RemoveEdge(Elem *el1, Elem *el2)
{
    SAVEITS;
    if (el1 && el2){
        bool res = (el1->childs->node == el2);
        if (!res){
            List* ls;
            while ((ls = it(el1))->next != nullptr){
                res = (ls->next->node == el2);
                if (res)
                    break;
            }
            List* ls2 = ls->next->next;
            ls->next->edge->clear();
            widget->scene()->removeItem(ls->next->edge);
            delete ls->next->edge;
            delete ls->next;
            ls->next = ls2;
        }
        else{
            List* ls2 = el1->childs->next;
            el1->childs->edge->clear();
            widget->scene()->removeItem(el1->childs->edge);
            delete el1->childs->edge;
            delete el1->childs;
            el1->childs = ls2;
        }
    }
    RESTOREITS;
}

void Graph::RenameElem(char *oldname, char *newname)
{
    Elem* el = FindElem(oldname);
    if ((!FindElem(newname)) && strlen(newname)!=0){
        strcpy_s(el->name, newname);
    }
}

int Graph::CountChildren(Elem *el)
{
    SAVEITS;
    int i;
    while (it(el)!=nullptr)
        i++;
    return i;
    RESTOREITS;
}

int Graph::CountElems()
{
    SAVEITS;
    int i = 0;
    while (it()!=nullptr)
        i++;
    return i;
    RESTOREITS;
}

bool Graph::Is_Egde(Elem *el1, Elem *el2)
{
    List* t_lpos = KeepItL();
    List* curr;
    bool res = 0;
    while ((curr = it(el1))!=nullptr){
        if (curr->node == el2){
            res = 1;
            break;
        }

    }
    RestoreItL(t_lpos);
    return res;
}

int Graph::Max_Width()
{
    SAVEITS;
    int i = 0;
    int l;
    Elem* el;
    while ((el = it())!=nullptr){
        if ((l=strlen(el->name)) > i)
            i = l;
    }
    RESTOREITS;
    return i;
}

void Graph::Inc_Matr(QTextStream &os)
{
    SAVEITS;
    int len = Max_Width();
    Elem* el;
    int z = CountElems();
    int i; int k;
    os.setFieldWidth(len + 1);
    os << " ";
    while ((el = it())!=nullptr){
        os << el->name;
    }
    os << endl;
    for (i=0; i<z; i++){
        os << this->operator [](i)->name;
        for (k=0; k<z; k++)
            os << Is_Egde(this->operator [](i), this->operator [](k));
        os << endl;
    }
    RESTOREITS;
}

Elem *Graph::operator[](int i)
{
    SAVEITS;
    int k=0;
    Elem* el;
    while (k<=i){
        el = it();
        if (el!=nullptr)
            k++;
        else
            break;
    }
    RESTOREITS;
    return el;
}


Elem *Graph::KeepItE()
{
    Elem* t_pos = pos;
    pos = nullptr;
    return t_pos;
}

List *Graph::KeepItL()
{
    List* t_lpos = lpos;
    lpos = nullptr;
    return t_lpos;
}

void Graph::RestoreItE(Elem *t_pos)
{
    pos = t_pos;
}

void Graph::RestoreItL(List *t_lpos)
{
    lpos = t_lpos;
}

void Graph::RemoveEdges(Elem *el)
{
    SAVEITS;
    Elem* el1;
    while ((el1 = it())!=nullptr){
        if (Is_Egde(el1, el))
            RemoveEdge(el1, el);
        if (Is_Egde(el, el1))
            RemoveEdge(el, el1);
    }
    RESTOREITS;
}

