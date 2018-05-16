#ifndef PENTAGON_HPP
#define PENTAGON_HPP

#include "point.h"
#include <vector>

using std::vector;

class Pentagon : public Shape{
public:
    Pentagon(vector<Point> points) : pts(points) {
        adjustPoints();
    }
    Pentagon(Point p1, Point p2, Point p3, Point p4, Point p5) : pts{p1, p2, p3, p4, p5}{
        adjustPoints();
    }
    vector<Point> points(){
        vector<Point> res;
        for (auto it : pts){
            Point p = it;
            p.SetR(it.GetR() * mult);
            p.SetPhi(it.GetPhi() + angle);
            res.push_back(p);
        }
        return res;
    }
    Point getPoint(int n){
        if ((n >= 0) && (n < 5))
            Point p = res[n];
            p.SetR(it.GetR() * mult);
            p.SetPhi(it.GetPhi() + angle);
    }
    double square(){
        double a=0; double b=0; double xp=pts[0].GetX()*mult; double yp=pts[0].GetY()*mult;
        for (vector<Point>::iterator it = ++pts.begin(); it < pts.end(); it++){
            a = a + xp * it->GetY()*mult;
            b = b + yp * it->GetX()*mult;
            xp = it->GetX()*mult;
            yp = it->GetY()*mult;
        }
        a = a + xp * pts[0].GetY()*mult;
        b = b + yp * pts[0].GetX()*mult;
        return abs((a-b)/2);
    }
    friend ostream& operator<<(ostream& os, const Pentagon& dt){
        os << "C: " << dt.center;
        for (auto it : dt.pts){
            os << " P " << it;
        }
        return os;
    }

private:
    Point calculateCenter(){
        Point cnt;
        for (auto it : pts){
            cnt = cnt + it;
        }
        cnt = cnt / 5;
        return cnt;
    }
    void adjustPoints(){
        center = calculateCenter();
        for (vector<Point>::iterator it = pts.begin(); it < pts.end(); it++){
            *it = *it - center;
        }
    }
    vector<Point> pts;
};

#endif