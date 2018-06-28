#ifndef FORMS_H_INCLUDED
#define FORMS_H_INCLUDED

#include "geometry.h"
#include "animation.h"
const double ANGLE2RAD = 0.01745329; //pi /180

class Color
{
public:
    float r, g, b, a;
    Color(float rr = 1.0f, float gg = 1.0f, float bb = 1.0f) {r=rr; g=gg; b=bb; a = 1.f; }
    Color(float rr, float gg, float bb, float aa) {r=rr; g=gg; b=bb; a = aa; }
};

class ColorGradient
{
private:
    Color startColor;
    Color middle1Color;
    Color middle2Color;
    Color endColor;
public:
    ColorGradient(Color startColorr, Color middle1Colorr, Color middle2Colorr, Color endColorr) {
        startColor = startColorr;
        middle1Color = middle1Colorr;
        middle2Color = middle2Colorr;
        endColor = endColorr;
    }
    ColorGradient(float r, float g, float b) {
        startColor = Color(r,g,b);
        middle1Color = startColor;
        middle2Color = startColor;
        endColor = startColor;
    }
    ColorGradient(Color color) {
        startColor = color;
        middle1Color = startColor;
        middle2Color = startColor;
        endColor = startColor;
    }

    ColorGradient(const ColorGradient& color) {
        startColor = color.startColor;
        middle1Color = color.middle1Color;
        middle2Color = color.middle2Color;
        endColor = color.endColor;
    }

    ColorGradient(const ColorGradient& color, float alpha) {
        startColor = color.startColor;
        middle1Color = color.middle1Color;
        middle2Color = color.middle2Color;
        endColor = color.endColor;

        startColor.a = alpha;
        middle1Color.a = alpha;
        middle2Color.a = alpha;
        endColor.a = alpha;
    }
    ColorGradient reversed() {
        return ColorGradient(endColor, middle2Color, middle1Color, startColor);
    }
    Color getStartColor() {return startColor;}
    Color getMiddle1Color() {return middle1Color;}
    Color getMiddle2Color() {return middle2Color;}
    Color getEndColor() {return endColor;}
};
// Constant Colors
const Color RED(1.0f, 0.0f, 0.0f);
const Color BLUE(0.0f, 0.0f, 1.0f);
const Color GREEN(0.0f, 1.0f, 0.0f);
const Color YELLOW(1.0f, 1.0f, 0.0f);
const Color WHITE(1.0f, 1.0f, 1.0f);
const Color BLACK(0.0f, 0.0f, 0.0f);


// Generic class to render and animate an object
class Form
{
protected:
    Color col;
    Animation anim;
public:
    Animation& getAnim() {return anim;}
    void setAnim(Animation ani) {anim = ani;}
    void setColor(Color colorr) {col = colorr;}
    Color getColor() {return col;}
    // This method should update the anim object with the corresponding physical model
    // It has to be done in each inherited class, otherwise all forms will have the same movements !
    // Virtual method for dynamic function call
    // Pure virtual to ensure all objects have their physics implemented
    virtual void update(double delta_t) = 0;
    // Virtual method : Form is a generic type, only setting color and reference position
    virtual void render();
};


const int SPHERE_PRECISION = 100;
// A particular Form
class Sphere : public Form
{
private:
    // The sphere center is aligned with the coordinate system origin
    // => no center required here, information is stored in the anim object
    double radius;
public:
    Sphere(double r = 1.0, Color cl = Color());
    const double getRadius() {return radius;}
    void setRadius(double r) {radius = r;}
    void update(double delta_t);
    void render();
};

//a flat ellipse
class EllipseDisk : public Form
{
private:
    double sinFactor;
    double cosFactor;
    double radius;
    Vector dir1; //axe avec un facteur
    Vector dir2; //axe avec un facteur
public:
    EllipseDisk(double radius, Vector dirr1 = Vector(1.0,0.0,0.0),Vector dirr2 = Vector(0.0,1.0,0.0),
            Color cl = Color()) {
        col = cl;
        this->radius = radius;
        dir1 = dirr1;
        dir2 = dirr2;
    }
    void update(double delta_t);
    void render();
    double getRadius() {return radius;}
};


// A face of a cube
class Face : public Form
{
private:
    Vector vdir1, vdir2;
    double length, width;
    Color middle1Color;
    Color middle2Color;
    Color endColor;
public:
    Face(Vector v1 = Vector(1,0,0), Vector v2 = Vector(0,0,1),
          Point org = Point(), double l = 1.0, double w = 1.0,
          ColorGradient colorGradient = ColorGradient(Color(), Color(), Color(), Color()));


    void update(double delta_t);
    void render();
    void setAlpha(float a);

    const Vector getVdir1() {return vdir1;}
    const Vector getVdir2() {return vdir2;}
    const double getWidth() {return width;}
    const double getLength() {return length;}

};

#endif // FORMS_H_INCLUDED
