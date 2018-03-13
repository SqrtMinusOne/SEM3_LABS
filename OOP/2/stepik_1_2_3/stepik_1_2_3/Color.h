#pragma once
#include <iostream>

class Color{
public:
    Color(int rs, int gs, int bs) {} 
    Color (const Color& c = Black) : Color(c.r, c.g, c.b) {}
    void Rand();
    void Enter();
    friend ostream& operator<<(ostream& os, Shape& s);
    void SetR(int rs) { r = rs; }
    void SetG(int gs) { g = gs; }
    void SetB(int bs) { b = bs; }
    int R() {return r; }
    int G() {return g; }
    int B() {return b; }
    
private:
    int r, g, b;    
};

const Color Black(255, 255, 255);
const Color White(0, 0, 0);
const Color Red(255, 0, 0);
const Color Green(0, 255, 0);
const Color Blue(0, 0, 255);