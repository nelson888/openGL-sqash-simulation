#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include "terrain.h"


using namespace std;

Point newCenter(Point origin, Point localCenter, Point center) {
    return Point(-localCenter.x + origin.x + center.x, -localCenter.y + origin.y + center.y,- localCenter.z + origin.z + center.z);
}

Terrain::Terrain(Point center, double length, double width, double height) {
    this->center = center;
    this->length = length;
    this->width = width;
    this->height = height;
    Point localCenter = newCenter(center, Point(0.0,0.0,0.0),Point(-length/2, 0, -width/2));
    Vector offset = Vector(center, localCenter);
    faces[SOL] = Face(Vector(1,0,0), Vector(0,0,1), localCenter, length, width, RED);

    Point p = Point(center);
    p.translate(offset);
    faces[DERRIERE] = Face(Vector(0,0,1), Vector(0,1,0), p, width, height);
    //faces[GAUCHE] = Face(Vector(1,0,0), Vector(0,1,0), newCenter(center, Point(0, 0, 0)), length, height);
    //faces[DROIT] = Face(Vector(1,0,0), Vector(0,1,0), newCenter(center, Point(0, 0, -width)), length, height);
    //faces[FOND] = Face(Vector(0,0,-1), Vector(0,1,0), newCenter(center, Point(length, 0, width)), width, height);
    //faces[PLAFOND] = Face(Vector(1,0,0), Vector(0,0,1), newCenter(center, Point(0, height, 0)), length, width, RED);
}



void Terrain::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
}


void Terrain::render()
{

    faces[SOL].render();
    faces[DERRIERE].render();
    //faces[GAUCHE].render();
    //faces[DROIT].render();
    //faces[FOND].render();

    //TODO loop
    for (int i = 0; i < 6; i++) {


    }
}

