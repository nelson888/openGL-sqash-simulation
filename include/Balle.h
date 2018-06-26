#ifndef BALLE_H
#define BALLE_H

#define WEIGHT 0.024
#define RADIUS 0.2
#define DRAG 0.05

#include "forms.h"
#include "geometry.h"
#include "math.h"

class Balle : public Sphere
{
    public:
        Balle(Point center, Vector accel);
        virtual ~Balle();

        double getWeight();

        void update(double delta);
        void checkCollision(Face face);
    protected:

    private:
        double weight;
        double drag;
        double surface;

        Point position;
        Vector accel;
};

#endif // BALLE_H
