#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include "geometry.h"

class Terrain
{
    private double length, width, height;
    private Point center;
    Terrain(Point center = Point(0.0, 0.0, 0.0), double length, double width, double height);

};


#endif // ANIMATION_H_INCLUDED
