#include "opt_task.h"

Opt_task::Opt_task(int nt){
    n = nt;
    totw = 0;
    maxv = 0;
}

int Opt_task::totv_all(){
    int res = 0;
    for (int i=0; i<n; i++){
        res = all[i].get_value() + res;
    }
    return res;
}

void Opt_task::try_item()
{
 //   make_arr();
    opts.clear();
    s.clear();
    nums = 0;
    clrzeros();
    n = all.count();
    Item zero;
    zero.set(0, 0);
    all.push_back(zero);
    totw = 0; maxv = 0;
    try_item(0, 0, totv_all());
}

void Opt_task::out(QStack<Item> s){
    for (auto it : s){
        qDebug() << "VALUE: " << it.get_value() << "; WEIGHT: " << it.get_weight() << endl;
    }
    qDebug() << "-----" << endl;
}



int Opt_task::g_totw(QStack<Item> s){
    int res = 0;
    for (auto it : s){
        res = res + it.get_weight();
    }
    return res;
}

int Opt_task::g_totv(QStack<Item> s){
    int res = 0;
    for (auto it : s){
        res = res + it.get_value();
    }
    return res;
}

void Opt_task::try_item(int i, int tw, int av){
    if (!steps)
        out(opts);
    nums++;
    Item it;
    it.set(all[i]);
    if (!steps){
        app->processEvents();
        try_incl(i, tw, av);
        try_unincl(i, tw, av);
    }
    else{
        try_unincl(i, tw, av);
        try_incl(i, tw, av);
    }
}

void Opt_task::try_incl(int i, int tw, int av)
{
    Item it;
    it.set(all[i]);
    if ((tw + it.get_weight() <= limw)){ //Включение возможно?
        if (it.get_value()) s.push(it); //Включение элемента
        if (i < n) //Если не конец, то ...
            try_item(i+1, tw+it.get_weight(), av, steps); //... пробуем дальше,
        else if (av > maxv){ //иначе - проверка оптимума
            maxv = av;
            opts = s;
        }
        if (it.get_value()) s.pop(); //Выключение элемента
    }
}

void Opt_task::try_unincl(int i, int tw, int av)
{
    Item it;
    it.set(all[i]);
    int av1 = av - it.get_value(); //Сколько сможем получить, если не включим
    if (av1 > maxv) { //Возможно невключение?
        if (i < n)
            try_item(i+1, tw, av1, steps);
        else{ //Если мы здесь, то проверка уже не нужна
            maxv = av1;
            opts = s;
        }
    }
}

void Opt_task::try_item(int i, int tw, int av, bool steps)
{
    if (!steps){
        try_item(i, tw, av);
    }
    else{
        try_parm parm(i,tw,av);
        parm.s = s;
        series.push(parm);
    }
}

void Opt_task::try_item(try_parm parm)
{
    QStack<Item> temp = s;
    s = parm.s;
    try_item(parm.i, parm.tw, parm.av);
    s = temp;
}

void Opt_task::setlimw(int i)
{
    if (limw > 0 )
        limw = i;
}

void Opt_task::setlimw(QString i)
{
    bool ok;
    int t = i.toInt(&ok);
    if (ok)
        limw = t;
}

void Opt_task::clrzeros()
{
    if (!all.isEmpty()){
        if (!all.back().ok()){
            all.pop_back();
            clrzeros();
        }
    }
}

