#include "item.h"

QColor Item::getcol()
{
    QColor col;
    col.setRgb(redcol, greencol, bluecol);
    return col;
}

void Item::set(int w, int v) {
    weight = w;
    value = v;
    setItem();
}

void Item::set(QString w, QString v, bool rnd)
{
    bool okw, okv;
    int wt = w.toInt(&okw);
    int vt = v.toInt(&okv);
    if (okw && okv){
        if (!rnd){
            weight = wt;
            value = vt;
        }
        else{
            weight = rand() % wt + 1;
            value = rand() % vt + 1;
        }
    }
    setItem();
}

void Item::set(Item it)
{
    weight = it.weight;
    value = it.value;
    redcol = it.redcol;
    greencol = it.greencol;
    bluecol = it.bluecol;
    setItem(0);
}

QString Item::print()
{
    QString str;
    QTextStream strm(&str);
    strm << "VALUE: " << get_value() << "; WEIGHT " << get_weight() << " ";
    return str;
}

void Item::setItem(bool randcol)
{
    if (value && weight){
        wItem = new QListWidgetItem(print());
        if (randcol){
            redcol = std::rand()%255;
            greencol = std::rand()%255;
            bluecol = std::rand()%255;
        }
        wItem->setBackgroundColor(getcol());
    }
}
