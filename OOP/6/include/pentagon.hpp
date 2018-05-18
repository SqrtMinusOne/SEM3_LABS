#ifndef PENTAGON_HPP
#define PENTAGON_HPP

#include "point.h"
#include <vector>

using std::vector;

class Pentagon : public Shape{
public:
    Pentagon() : Shape(){
        for (int i = 0; i < 5; i++)
            pts.push_back(Point(0,0));
    }
    Pentagon(vector<Point> points) : Shape(), pts(points) {
        adjustPoints();
    }
    Pentagon(Point p1, Point p2, Point p3, Point p4, Point p5) : Shape(), pts{p1, p2, p3, p4, p5}{
        adjustPoints();
    }
    vector<Point> points(){
        vector<Point> res;
        for (auto it : pts){
            Point p = it;
            p.SetR(it.GetR() * mult);
            p.SetPhi(it.GetPhi() + angle);
            p = p + center;
            res.push_back(p);
        }
        return res;
    }
    Point getPoint(int n){
        if ((n >= 0) && (n < 5)){
            Point p = pts[n];
            p.SetR(pts[n].GetR() * mult);
            p.SetPhi(pts[n].GetPhi() + angle);
            p = p + center;
            return p;
        }
        else{
            throw std::out_of_range("Out of range");
        }
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

protected:
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