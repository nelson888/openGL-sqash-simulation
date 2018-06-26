#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include "forms.h"


using namespace std;


void Form::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
}


void Form::render()
{
    // Point of view for rendering
    // Common for all Forms
    Point org = anim.getPos();
    glTranslated(org.x, org.y, org.z);
    if (col.a == 1.0f) {
        glColor3f(col.r, col.g, col.b);
    } else {
        glColor4f(col.r, col.g, col.b, col.a);
     }

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

void EllipseDisk::update(double delta_t)
{
    // Complete this part
}

void EllipseDisk::render()
{
    Form::render();

    glBegin(GL_TRIANGLE_FAN);
    for(int t = 0; t <= 360; t +=1)
	{
	    Vector position = sinFactor*sin(t)*dir1 + cosFactor* cos(t)* dir2;
	    glVertex3f(position.x,position.y,position.z);
    }
    glEnd();
}



Face::Face(Vector v1, Vector v2, Point org, double l, double w,
           ColorGradient colorGradient)
{
    vdir1 = 1.0 / v1.norm() * v1;
    vdir2 = 1.0 / v2.norm() * v2;
    anim.setPos(org);
    length = l;
    width = w;
    col = colorGradient.getStartColor();
    middle1Color = colorGradient.getMiddle1Color();
    middle2Color = colorGradient.getMiddle2Color();
    endColor = colorGradient.getEndColor();
}


void Face::update(double delta_t)
{
    // Do nothing, no physics associated to a Face
}

void changeColor(Color color) {
    glColor4f(color.r, color.g, color.b, color.a);
}

void Face::render()
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
        changeColor(col);
        glVertex3d(p1.x, p1.y, p1.z);
        changeColor(middle1Color);
        glVertex3d(p2.x, p2.y, p2.z);
        changeColor(middle2Color);
        glVertex3d(p3.x, p3.y, p3.z);
        changeColor(endColor);
        glVertex3d(p4.x, p4.y, p4.z);
    }
    glEnd();
}
