#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include "forms.h"
#include "geometry.h"

class Terrain : public Form
{
private:
    double length, width, height;
    Point center;
    Face faces[6];
    //index des faces du tableau
    static const int SOL = 0;
    static const int DROIT = 1;
    static const int GAUCHE = 2;
    static const int FOND = 3;
    static const int DERRIERE = 4;
    static const int PLAFOND = 5;
public:
    Terrain(Point center = Point(0.0, 0.0, 0.0), double length = 0.0, double width = 0.0, double height = 0.0);

    const double getLength() {return length;}
    const double getWidth() {return width;}
    const double getHeight() {return height;}
    const Point getCenter() {return center;}

    void update(double delta_t);
    void render();
};


#endif // ANIMATION_H_INCLUDED
