#ifndef REGULAR_PENTAGON_HPP
#define REGULAR_PENTAGON_HPP

#include "point.h"
#include "pentagon.hpp"

class RegularPentagon : public Pentagon
{
public:
    RegularPentagon(Point cnt = Pzero, Point p = Pzero) : Pentagon(){
        center = cnt;
        p = p - cnt;
        pts.clear();
        double ang = 0;
        for (int i = 0; i < 5; i++, ang+=(2*M_PI/5)){
            Point temp = p;
            temp.SetPhi(ang);
            pts[i] = temp;
        }
    }
    RegularPentagon(Point cnt, double rad) : Pentagon()
    {
        center = cnt;
        Point p;
        p.SetR(rad);
        double ang = 0;
        for (int i = 0; i < 5; i++, ang+=(2*M_PI/5)){
            Point temp = p;
            temp.SetPhi(ang);
            pts[i] = temp;
        }
    }
};

#endif