#pragma once
#include "Shape.h"
#include "Line.h"


class Rectangle :
    public Shape
{
    public:
    Rectangle();
    Rectangle(Point lu, Point rd);
    Rectangle(Point lu, Point ld, Point ru, Point rd);
    Rectangle(int lux, int luy, int rdx, int rdy);
    Rectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
    void Enter();
	void Rand(int min, int max);
	Point LeftUp() {return this->pts[0]; }
    Point LeftDown() {return this->pts[1]; }
    Point RightUp() {return this->pts[2]; }
    Point RightDown() {return this->pts[3]; }
    bool isValid();
};