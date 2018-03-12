#pragma once
#include "Shape.h"
class Circle :
	public Shape
{
public:
	Circle();
	Circle(Point x, int r);
	Circle(int x, int y, int r);
	void Enter();
	void Out();
	friend ostream& operator<<(ostream& os, Circle& s);
	void Rand(int min, int max);
	void Scale(int c);
	void Scale(int c, Point cnt);
	~Circle() = default;
private:
	int rad;
};

