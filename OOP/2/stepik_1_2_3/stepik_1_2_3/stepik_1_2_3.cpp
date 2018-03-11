#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include "Point.h"
#include "Shape.h"

using namespace std;
using namespace stdext;



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

