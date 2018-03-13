#include "Color.h"

using namespace std;

Color::Color(int rs, int gs, int bs): r(rs), g(gs), b(bs) { }
Color::Color() : Color(0, 0, 0) {}
Color::Rand(){
    r = rand() % 255;
    g = rand() % 255;
    b = rand() % 255;
}

Color::Enter(){
    cout << "Enter R,G,B: ";
    cin >> r >> g >> b;
}

ostream & operator<<(ostream & os, Color & s)
{
	os << "R: " << r << "; G: " << g << "; B:" << b;
	return os;
}

