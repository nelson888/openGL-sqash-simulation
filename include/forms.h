#ifndef FORMS_H_INCLUDED
#define FORMS_H_INCLUDED

#include "geometry.h"
#include "animation.h"


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
    double radius;
    double sinFactor;
    double cosFactor;
    Vector dir1;
    Vector dir2;
public:
    EllipseDisk(double radiuss = 0.0,Vector dirr1 = Vector(1.0,0.0,0.0),Vector dirr2 = Vector(0.0,1.0,0.0),
            Color cl = Color(), double sinFactorr = 1.0, double cosFactorr = 1.0) {
        radius = radiuss;
        col = cl;
        sinFactor = sinFactorr;
        cosFactor = cosFactorr;
        dir1 = dirr1;
        dir2 = dirr2;
    }
    const double getRadius() {return radius;}
    void setRadius(double r) {radius = r;}
    void update(double delta_t);
    void render();
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
};

#endif // FORMS_H_INCLUDED
