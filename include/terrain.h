#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include "forms.h"
#include "geometry.h"

static const int NB_FACES = 5;

class Terrain : public Form
{
private:
    //index des faces du tableau
    static const int GROUND = 0;
    static const int RIGHT = 1;
    static const int LEFT = 2;
    static const int FRONT = 3;
    static const int BACK = 5;
    static const int ROOF = 4;
    static const int NB_LINES = 11;
    static const double LINE_WIDTH = 0.05;

    double length, width, height;
    Point center;
    Face faces[NB_FACES];
    Face lines[NB_LINES];

public:
    Terrain(Point center = Point(0.0, 0.0, 0.0), double length = 0.0, double width = 0.0, double height = 0.0);

    const double getLength() {return length;}
    const double getWidth() {return width;}
    const double getHeight() {return height;}
    const Point getCenter() {return center;}

    void update(double delta_t);
    void render();
    Face* getFaces() {
        return &this->faces[0];
    }
};


#endif
