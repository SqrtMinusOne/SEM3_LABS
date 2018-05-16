#ifndef POINT
#define POINT

#include <iostream>

using namespace std;
class Point {
public:
	Point(double xs = 0, double ys = 0) : x(xs), y(ys) {}
	Point(const Point& p) : x(p.x), y(p.y) {}
	~Point() = default;
	Point& Rand(int min, int max);
	//Copy-and-swap
	friend void swap(Point& first, Point& second);
	Point& operator=(Point p);
	Point(Point&& p);
	//Arithmetics
	Point& operator/(double i);
	Point& operator*(double i);
	//In-out
	friend ostream& operator<<(ostream& os, const Point& p);
	friend istream& operator >> (istream& is, Point& p);
	//Get, Set
	double GetX() const { return x; }
	double GetY() const { return y; }
	void SetX(double xs) { x = xs; }
	void SetY(double ys) { y = ys; }
private:
	double x;
	double y;
};

bool operator==(const Point & a, const Point & b);
Point operator+(const Point & p1, const Point & p2);
Point operator-(const Point & p1, const Point & p2);
#endif // POINT