#include <iostream>
#include <cstdlib>
#include <cmath>

#include "point.h"
#include "shape.hpp"
#include "circle.hpp"
#include "pentagon.hpp"
#include "regular_pentagon.hpp"

#include "shared_ptr.hpp"
#include "vector.hpp"

#define N 3

using namespace std;

Pentagon* psRandRect(int min, int max){
    Point cnt = Point().Rand(min, max);
    int rd = (max - min) / 10;
    double PhiDeg = 0;
    vector<Point> pts;
    for (int i = 0; i < 5; i++){
        PhiDeg = 72*i + rand() % 72;
        double PhiRad = PhiDeg/180*M_PI;
        Point p;
        p.SetR(rand()%rd + rd/2);
        p.SetPhi(PhiRad);
        pts.push_back(p);
    }
    Pentagon* res = new Pentagon(pts);
    return res;
}

int main(){
    stepik::vector<stepik::shared_ptr<Shape>> vect(N);
    srand(time(0));
    short int choice = 0;
    for (int i = 0; i < N; i++){
        choice = rand() % 3;
        Shape* shp;
        switch (choice){
            case 0: shp = new Circle(Point().Rand(0, 1000), rand()%100); break;
            case 1: shp = new RegularPentagon(Point().Rand(0, 1000), rand()%100); break;
            case 2: shp = psRandRect(0, 1000); break;
        }
        stepik::shared_ptr<Shape> ptr(shp);
        vect.push_back(ptr);
    }
    double sq = 0;
    stepik::shared_ptr<Shape> * max;
    Shape* toReplace = new Circle(Point(500, 500), 500);
    for (int i = 0; i < N; i++){
        if (vect[i]->square() > sq){
            sq = vect[i]->square();
            cout << sq << endl;
            max = &vect[i];
        }
    }
    max->reset(toReplace);

}