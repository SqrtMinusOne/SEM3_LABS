#ifndef ITEM_H
#define ITEM_H

#include <QColor>
#include <QString>
#include <QTextStream>
#include <QListWidget>
#include <QApplication>
#include <qDebug>

class Item{
public:
    QColor getcol();
    void set(int w, int v);
    void set(QString w, QString v, bool rnd = 0);
    void set(Item it);
    int get_weight(){ return weight; }
    int get_value() { return value; }
    bool ok() {return ((weight!=0) && (value!=0)); }
    QString print();
    QListWidgetItem* wItem;
private:
    int redcol = 0; int greencol = 0; int bluecol = 0;
    void setItem(bool randcol=1);
    int weight = 0;
    int value = 0;
};

#endif // ITEM_H
