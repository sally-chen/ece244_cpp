/* 
 * File:   Triangle.h
 * Author: vaughn
 *
 * Created on November 21, 2012, 7:36 PM
 */

#ifndef POLYGON_H
#define	POLYGON_H

#include "Shape.h"
#include "easygl.h"

class Polygon : public Shape {
private:
   t_point relVertex[100]; 
   int npoints;
   
   // Private helper functions.
   t_point getVecBetweenPoints (t_point start, t_point end) const;
   
public:
   Polygon (string _name, string _colour, float _xcen, float _ycen,
            t_point _coords[100],int _npoints);

   virtual ~Polygon();
   
   
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
};

#endif	/* TRIANGLE_H */
