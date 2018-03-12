#include "stdafx.h"
#include "Line.h"

Line::Line() : Shape(2)
{
}

Line::Line(Point a, Point b) : Shape(2)
{
	this->pts[0] = a;
	this->pts[1] = b;
}

Line::Line(int x1, int y1, int x2, int y2) : Line(Point(x1, y1), Point(x2,y2)) {}

void Line::Enter()
{
	cout << "Enter start: ";
	cin >> pts[0];
	cout << "Enter end: ";
	cin >> pts[1];
}

Point Line::Start()
{
	return pts[0];
}

Point Line::End()
{
	return pts[1];
}

Point Line::Delta(){
	return End() - Start();
}

void Line::RotateAroundStart(int deg)
{
	Rotate(deg, Start());
}

void Line::RotateAroundEnd(int deg)
{
	Rotate(deg, End());
}

void Line::MoveAtCoords(Point newp)
{
	Shape::MoveAtCoords(newp, Start());
}

Line::~Line()
{
}

double Line::Length(){
	Point d = End() - Start();
	return sqrt((d.GetX()*d.GetX()) + (d.GetY()*d.GetY()));
}

int Line::ScalarMult(Line l2){
	int res = 0;
	res = res + Delta().GetX()*l2.Delta().GetX();
	res = res + Delta().GetY()*l2.Delta().GetY();
}