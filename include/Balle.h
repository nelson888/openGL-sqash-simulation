#ifndef BALLE_H
#define BALLE_H

#define WEIGHT 0.024
#define RADIUS 0.2
#define DRAG 0.01

#include "forms.h"
#include "geometry.h"
#include "math.h"

const double REBOND_SCALAR = 0.8;


class Balle : public Sphere
{
    public:
        Balle(Point center, Vector vitesse);
        virtual ~Balle();

        double getWeight();
        Point getNextPosition(){return nextPosition;};
        Vector getNextAccel(){return nextAccel;};
        Vector getNextVitesse(){return nextVitesse;};
        void setPosition(Point p){anim.setPos(p);};
        void setAccel(Vector v){anim.setAccel(v);};
        void setVitesse(Vector v){anim.setSpeed(v);};

        void update(double delta);
        void checkCollision(Face *faces);
    protected:

    private:
        double weight;
        double drag;
        double surface;

        Point nextPosition;
        Vector nextAccel;
        Vector nextVitesse;
};

#endif // BALLE_H
