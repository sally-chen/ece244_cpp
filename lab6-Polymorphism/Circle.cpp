#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Circle.h"

#ifndef PI
#define PI 3.1415926535897
using namespace std;


// Constructor. First set up base class (Shape), then store the 
// vertices, which are 3 (x,y) points giving offsets from the Shape center 
// to each triangle vertex.
Circle::Circle (string _name, string _colour, float _xcen, float _ycen,
            float _radius) 
              : Shape (_name, _colour, _xcen, _ycen) {
    radius = _radius;
}


Circle::~Circle () {
   // No dynamic memory to delete
}


void Circle::print () const {
   Shape::print();
   cout << "circle radius: "<<radius<<endl;
}


void Circle::scale (float scaleFac) {
    radius *= scaleFac;
}
   

float Circle::computeArea () const {   
   float area = 0;
    area = radius * radius * PI;
   return area;
}


float Circle::computePerimeter () const {
    float perimeter = 0;
    perimeter = 2*PI*radius;
   return perimeter;
}


void Circle::draw (easygl* window) const {
   window->gl_setcolor(getColour());
   window->gl_fillarc(getXcen(),getYcen(),0,360);
}


bool Circle::pointInside (float x, float y) const {
    //if distance to center > r=x^2 + y^ 2 squrt
    int r;
    r = sqrt(pow (x - getXcen(), 2.0) + pow (y - getYcen(), 2.0));
    if(r > radius)
        return false;
    else 
        return true;
}
#endif
