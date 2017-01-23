#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Rectangle.h"
using namespace std;


// Constructor. First set up base class (Shape), then store the 
// vertices, which are 3 (x,y) points giving offsets from the Shape center 
// to each triangle vertex.
Rectangle::Rectangle (string _name, string _colour, float _xcen, float _ycen,
            float _width, float _height) 
              : Shape (_name, _colour, _xcen, _ycen) {
   
    width = _width;
    height = _height;
    //0--1
    //|  |
   // 3--2
    //
    relVertex[0].x = relVertex[3].x = _xcen - _width/2;
    relVertex[1].x = relVertex[2].x = _xcen + _width/2;
    relVertex[0].y = relVertex[1].y = _ycen + _height/2;
    relVertex[2].y = relVertex[3].y = _ycen - _height/2;
}


Rectangle::~Rectangle () {
   // No dynamic memory to delete
}


void Rectangle::print () const {
   Shape::print();
   cout << "rectangle width: " <<width<<" height: "<<height<< endl;
}


void Rectangle::scale (float scaleFac) {
   for (int i = 0; i < 4; i++) {
      relVertex[i].x *= scaleFac;
      relVertex[i].y *= scaleFac;
   }
}
   

float Rectangle::computeArea () const {
   return width*height;
}


float Rectangle::computePerimeter () const {
  
   return 2*(width+height);
}


void Rectangle::draw (easygl* window) const {
   t_point coords[4];  // This data type is in easygl_constants.h
   for (int i = 0; i < 4; i++) {
      coords[i].x = relVertex[i].x;
      coords[i].y = relVertex[i].y;
   }
   window->gl_setcolor(getColour());
   window->gl_fillpoly(coords, 4);
}


bool Rectangle::pointInside (float x, float y) const {
   // Make a point that corresponds to where you clicked. Since all my
   // vertices are relative to the triangle center, it is more convenient
   // to also shift the click point so it is an offset from the triangle 
   // center.
   t_point click;
   click.x = x;
   click.y = y;
   
   if(click.x > relVertex[0].x && click.x < relVertex[1].x && click.y > relVertex[2].y && click.y < relVertex[1].y)
        return true;
   else
       return false;
}


// Private helper functions below.  Working out triangle area etc. 
// requires some vector math, so these helper functions are useful.

// Return the (x,y) vector between start and end points.
t_point Rectangle::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}

