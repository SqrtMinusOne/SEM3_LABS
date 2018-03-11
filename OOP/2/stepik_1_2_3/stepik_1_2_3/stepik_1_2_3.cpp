#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#define M_PI 3.14159265358979323846
using namespace std;
using namespace stdext;

class Point {
public:
	Point(int xs = 0, int ys = 0): x(xs), y(ys) {}
	Point(const Point& p) : x(p.x), y(p.y) {}
	~Point() = default;
	//Copy-and-swap
	friend void swap(Point& first, Point& second) {
		swap(first.x, second.x);
		swap(first.y, second.y);
	}
	Point& operator=(Point p) {
		swap(*this, p);
		return *this;
	}
	Point(Point&& p) {
		swap(*this, p);
	}
/*	Point& operator=(Point&& p) {
		swap(*this, p);
		return *this;
	} */
	
	//Arithmetics
	/*
	Point& operator+(Point p) {
		x = x + p.GetX();
		y = y + p.GetY();
		return *this;
	}
	Point& operator-(Point p) {
		x = x - p.GetX();
		y = y - p.GetY();
		return *this;
	}
	*/
	Point& operator/(double i) {
		x = x / i;
		y = y / i;
		return *this;
	}
	Point& operator*(double i) {
		x = x * i;
		y = y * i;
		return *this;
	}

	//In-out
	friend ostream& operator<<(ostream& os, const Point& p) {
		os << "(" << p.x << "," << p.y << ")";
		return os;
	}
	friend istream& operator >> (istream& is, Point& p) {
		is >> p.x >> p.y;
		return is;
	}

	int GetX() { return x; }
	int GetY() { return y; }
	void SetX(int xs) { x = xs; }
	void SetY(int ys) { y = ys; }
private:
	int x;
	int y;
};

Point operator+(Point& p1, Point& p2) {
	return Point(p1.GetX() + p2.GetX(), p1.GetY() + p2.GetY());
}

Point operator-(Point& p1, Point& p2) {
	return Point(p1.GetX() - p2.GetX(), p1.GetY() - p2.GetY());
}

class Shape {
public:
	Shape(int dots = 0) : dts(dots), pts(dots ? new Point[dots] : nullptr) {}
	Point* it() //Passes throught every point
	{
		if (pos < dts) {
			return &pts[pos++];
		}
		else {
			pos = 0;
			return nullptr;
		}
	}
	/*
	//Copy-and-swap
	friend void swap(Shape& first, Shape& second)
	{
		swap(first.dts, second.dts);
		swap(first.pts, second.pts);
	}
	Shape(const Shape& s): dts(s.dts), pts(s.dts ? new Point[s.dts] : nullptr)
	{
		copy(s.pts, s.pts + s.dts*sizeof(Point), checked_array_iterator<Point*>(pts, dts));
	}
	*/
	//In-out
	virtual void Enter() {
		for (int i = 0; i < dts; i++) {
			cout << "Enter point #" << i << ": ";
			cin >> pts[i];
		}
	}
	virtual void Out() {
		Point* ptr;
		while (ptr = it()) {
			cout << *ptr << ", ";
		}
		cout << endl;
	}
	friend ostream& operator<<(ostream& os, Shape& s) {
		while (Point* ptr = s.it()) {
			os << *ptr << ", ";
		}
		return os;
	}
	void Rand(int min, int max) {
		while (Point* ptr = it()) {
			ptr->SetX(min + rand() % (max - min));
			ptr->SetY(min + rand() % (max - min));
		}
	}

	//Geometry
	virtual Point GetCenterPoint() { 
		Point res;
		Point* ptr;
		while (ptr = it()) {
			res = res + *ptr;
		}
		res = res / dts;
		return res;
	}
	virtual void Rotate(int deg) {
		Rotate(deg, GetCenterPoint());
	}
	virtual void Rotate(int deg, Point cnt)  //Default rotate
	{
		Point* ptr;
		double rad = deg*M_PI / 180;
		Point d;
		Point nd;
		while (ptr = it()) {
			d = *ptr - cnt;
			nd.SetX(d.GetX()*cos(rad) + d.GetY()*sin(rad));
			nd.SetY(d.GetY()*cos(rad) + d.GetX()*sin(rad));
			*ptr = nd + cnt;
		}
	}
	virtual void Move(Point delta) {
		while (Point* ptr = it()) {
			*ptr = *ptr + delta;
		}
	}
	virtual void MoveAtCoords(Point newp) {
		MoveAtCoords(newp, GetCenterPoint());
	}
	virtual void MoveAtCoords(Point newp, Point cnt) {
		Point* ptr;
		Point d;
		while (ptr = it()) {
			d = *ptr - cnt;
			*ptr = d + newp;			
		}
	}
	virtual void Scale(int c) {
		Scale(c, GetCenterPoint());
	}
	virtual void Scale(double c, Point cnt) {
		Point d;
		while (Point* ptr = it()) {
			d = *ptr - cnt;
			d = d * c;
			*ptr = cnt + d;
		}
	}
protected:
	int dts;
	Point* pts;
private:
	int pos = 0;
};

int main()
{
	srand(time(0));
	//----------------------------
	cout << "===|Base constructor test|===" << endl;
	Shape s(5);
	s.Rand(0, 100); 
	cout << s << endl;
	//----------------------------
	cout << "===|Base center test|===" << endl;
	cout << s.GetCenterPoint() << endl;
	//----------------------------
	cout << "===|Base rotate test|===" << endl;
	for (int i = 0; i <= 360; i = i + 90) {
		s.Rotate(90);
		cout << i << ": ";
		cout << s << endl;
	}
	//----------------------------
	cout << "===|Base move test|===" << endl;
	s.Move(Point(20, 20));
	cout << s << endl;
	//----------------------------
	cout << "===|Base move at coordinates test|===" << endl;
	s.MoveAtCoords(Point(1000, 1000));
	cout << s.GetCenterPoint() << endl;
	cout << s << endl;
	s.MoveAtCoords(Point(0, 0));
	cout << s.GetCenterPoint() << endl;
	s.Out();
	//----------------------------
	cout << "===|Base scale test|===" << endl;
	s.Scale(10);
	s.Out();
	return 0;
}

