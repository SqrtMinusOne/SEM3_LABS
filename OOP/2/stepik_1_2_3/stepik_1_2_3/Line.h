#pragma once
#include "Shape.h"
class Line :
	public Shape
{
public:
	Line();
	Line(Point a, Point b);
	Line(int x1, int y1, int x2, int y2);
	//Int-out
	void Enter();
	//Different points
	Point Start();
	Point End();
	//Geometry
	void RotateAroundStart(int deg);
	void RotateAroundEnd(int deg);
	void MoveAtCoords(Point newp);
	~Line();
};

