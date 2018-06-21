#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include "terrain.h"


using namespace std;


Terrain::Terrain(Point center, double length, double width, double height) {
    this->center = center;
    this->length = length;
    this->width = width;
    this->height = heigth;
    faces[SOL] = Face(Vector(1,0,0), Vector(0,0,1), center, length, width, RED);
    faces[SOL] = Face(Vector(1,0,0), Vector(0,0,1), center, LENGTH, WIDTH, RED);
    faces[SOL] = Face(Vector(1,0,0), Vector(0,0,1), center, LENGTH, WIDTH, RED);
    faces[SOL] = Face(Vector(1,0,0), Vector(0,0,1), center, LENGTH, WIDTH, RED);
    faces[SOL] = Face(Vector(1,0,0), Vector(0,0,1), center, LENGTH, WIDTH, RED);
    faces[SOL] = Face(Vector(1,0,0), Vector(0,0,1), center, LENGTH, WIDTH, RED);
}
void Form::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
}


void Form::render()
{

   for
}


Sphere::Sphere(double r, Color cl)
{
    radius = r;
    col = cl;
}


void Sphere::update(double delta_t)
{
    // Complete this part
}


void Sphere::render()
{
    GLUquadric *quad;

    quad = gluNewQuadric();

    Form::render();
    glBegin(GL_QUADS);
    {
        gluSphere(quad, radius, SPHERE_PRECISION, SPHERE_PRECISION);
    }
    glEnd();

    gluDeleteQuadric(quad);
}


Cube_face::Cube_face(Vector v1, Vector v2, Point org, double l, double w, Color cl)
{
    vdir1 = 1.0 / v1.norm() * v1;
    vdir2 = 1.0 / v2.norm() * v2;
    anim.setPos(org);
    length = l;
    width = w;
    col = cl;
}


void Cube_face::update(double delta_t)
{
    // Do nothing, no physics associated to a Cube_face
}


void Cube_face::render()
{
    Point p1 = Point();
    Point p2 = p1, p3, p4 = p1;
    p2.translate(length*vdir1);
    p3 = p2;
    p3.translate(width*vdir2);
    p4.translate(width*vdir2);

    Form::render();
    glBegin(GL_QUADS);
    {
        glColor3f(col.r,col.g,col.b);
        glVertex3d(p1.x, p1.y, p1.z);

        glVertex3d(p2.x, p2.y, p2.z);

        glVertex3d(p3.x, p3.y, p3.z);

        glVertex3d(p4.x, p4.y, p4.z);
    }
    glEnd();
}
