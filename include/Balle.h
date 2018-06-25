#ifndef BALLE_H
#define BALLE_H

#define WEIGHT 24
#define RADIUS 0.02

#include "forms.h"
#include "geometry.h"

class Balle : public Sphere
{
    public:
        Balle();
        virtual ~Balle();

        Point nextPosition();

        double getWeight();
        Vector getAccel();

    protected:

    private:
        double radius = RADIUS;
        double weight = WEIGHT;

        Point position;
        Vector accel;
};

#endif // BALLE_H
