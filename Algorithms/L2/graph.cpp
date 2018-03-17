#include "graph.h"

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
}

void Graph::Clear(List *ls)
{
    if (ls != nullptr) {
        if (ls->next != nullptr)
            Clear(ls->next);
        delete ls;
    }
}

void Graph::Clear(Elem *gr)
{
    if (gr){
        if (gr->next != nullptr) {
            Clear(gr->next);
        }
        Clear(gr->childs);
        delete gr;
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

void Graph::AddElem(char *name)
{
    SAVEITS;
    Elem* el;
    if (!gr){
        gr = new Elem;
        strcpy_s(gr->name, Numb, name);
    }
    else{
        while ((el = it())->next!=nullptr);
        el->next = new Elem;
        el = el->next;
        strcpy_s(el->name, Numb, name);

    }
    RESTOREITS;
}

Elem *Graph::FindElem(char *name)
{
    SAVEITS;
    Elem* el;
    bool res = 0;
    while (((el = it())!=nullptr) && (res == 0)){
        res = strncmp(name, el->name, Numb);
    }
    RESTOREITS;
    return el;
}

int Graph::CountChildren(Elem *el)
{
    int i;
    while (it(el)!=nullptr)
        i++;
    return i;
}

int Graph::CountElems()
{
    int i = 0;
    while (it()!=nullptr)
        i++;
    return i;
}

bool Graph::Is_Egde(Elem *el1, Elem *el2)
{
    List* t_lpos = KeepItL();
    List* curr;
    bool res = 0;
    while ((curr = it(el2))!=nullptr){
        if (curr->node == el1){
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
    List* ls;
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

