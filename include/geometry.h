#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include <iostream>


class Coordinates
{
public:
    double x, y, z;
    Coordinates(double xx=0, double yy=0, double zz=0) {x=xx; y=yy; z=zz;}
};


// Declaration in order to use it within Point methods
class Vector;

class Point : public Coordinates
{
public:
    // Point constructor calls the base class constructor and do nothing more
    Point(double xx=0, double yy=0, double zz=0) : Coordinates(xx, yy, zz) {}
    Point(const Point& point) : Coordinates(point.x, point.y, point.z) {}
    void translate(const Vector &);
};


class Vector : public Coordinates
{
public:
    // Instantiates a Vector from its coordinates
    Vector(double xx=0, double yy=0, double zz=0) : Coordinates(xx, yy, zz) {}
    // Or with two points
    Vector(Point, Point);
    // Compute the vector norm
    double norm();
    bool isZero();
    void setLength(double newLength);
    Vector integral(double delta_t);
    // Overloaded standard operators
    void operator+=(const Vector &v);
};

const Vector X_AXIS = Vector(1.0, 0.0, 0.0);
const Vector Y_AXIS = Vector(0.0, 1.0, 0.0);
const Vector Z_AXIS = Vector(0.0, 0.0, 1.0);

// Compute the distance between two points
double distance(Point p1, Point p2);

// Overloaded standard operators
std::ostream& operator<<(std::ostream& os, const Coordinates& coord);
Point operator+(const Point &v1, const Point &v2);

Vector operator+(const Vector &v1, const Vector &v2);
Vector operator-(const Vector &v);
Vector operator-(const Vector &v1, const Vector &v2);
Vector operator*(const double &k, const Vector &v);
// Scalar product
double operator*(const Vector &v1, const Vector &v2);
// Vector product
Vector operator^(const Vector &v1, const Vector &v2);

#endif // GEOMETRY_H_INCLUDED
