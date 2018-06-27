#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include "forms.h"
#include "geometry.h"
#include "stdlib.h"

static const int NB_FACES = 6;
static const int GROUND = 0;
static const int RIGHT = 1;
static const int LEFT = 2;
static const int FRONT = 3;
static const int BACK = 5;
static const int ROOF = 4;

class Terrain : public Form
{
private:
    class TerrainFace : public Face
    {
    public:
        int nbLines;
        int *lines;
        TerrainFace(Vector v1 = Vector(1,0,0), Vector v2 = Vector(0,0,1),
          Point org = Point(), double l = 1.0, double w = 1.0,
          ColorGradient colorGradient = ColorGradient(Color(), Color(), Color(), Color()), int nbLines = 0):Face(v1,v2,org,l,w,colorGradient)
            {
                this->nbLines = nbLines;
                lines = (int *) malloc(nbLines * sizeof(int));
            }
        };
    //index des faces du tableau

    static const int NB_LINES = 11;
    static const double LINE_WIDTH = 0.05;

    double width, length, height;
    Point center;
    TerrainFace faces[NB_FACES];
    Face lines[NB_LINES];

public:
    Terrain(Point center = Point(0.0, 0.0, 0.0), double width = 0.0, double length = 0.0, double height = 0.0);

    const double getLength() {return width;}
    const double getWidth() {return length;}
    const double getHeight() {return height;}
    const Point getCenter() {return center;}

    void update(double delta_t);
    void render();
    Face* getFaces() {
        return &this->faces[0];
    }

    void hideFace(int index);
    void showAllFaces();
};


#endif
