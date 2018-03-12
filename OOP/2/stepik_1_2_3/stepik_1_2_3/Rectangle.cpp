#include "stdafx.h"
#include "Rectangle.h"
#include "Line.h"
Rectangle::Rectangle() : Shape(4){
}

Rectangle::Rectangle(Point lu, Point rd): Shape(4){
    Point ld(lu.GetX(), ru.GetY());
    Point ru(lu.GetY(), rd.GetX());
    this->pts[0] = lu;
    this->pts[1] = ld;
    this->pts[2] = ru;
    this->pts[3] = rd;
}

Rectangle::Rectangle(int lux, int luy, int rdx, int rdy) : Rectangle(Point(lux, luy), Point(rdx, rdy)){
}



Rectangle::Rectangle(Point lu, Point ld, Point ru, Point rd): Shape(4){
    this->pts[0] = lu;
    this->pts[1] = ld;
    this->pts[2] = ru;
    this->pts[3] = rd;
}

Rectangle::Rectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   : Rectangle(Point(x1, y1), Point(x2, y2), Point(x3, y3), Point(x4, y4)) {}

void Rectangle::Enter(){
    cout << "Enter left up point: ";
    cin >> this->pts[0];
    cout << "Enter left down point: ";
    cin >> this->pts[1];
    cout << "Enter right up point: ";
    cin >> this->pts[2];
    cout << "Enter right down point: ";
    cin >> this->pts[3];
}

bool Rectangle::isValid(){
    Line a(LeftUp(), LeftDown());
    Line b(LeftUp(), RightUp());
    Line c(LeftDown(), RightDown());
    Line d(RightUp(), RightDown());
    bool res = 1;
    res = ((a.Length() == c.Length()) && (b.Length() == d.Length());
    res = res && (a.ScalarMult(b) == 0);
    res = res && (b.ScalarMult(c) == 0);
    res = res && (c.ScalarMult(d) == 0);
    res = res && (d.ScalarMult(a) == 0);
    return res;
}