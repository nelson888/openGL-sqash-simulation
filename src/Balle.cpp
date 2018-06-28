#include "Balle.h"

Balle::Balle(Point center, Vector vitesse):Sphere(RADIUS,BLACK)
{
    anim.setPos(center);
    anim.setSpeed(vitesse);
    weight = WEIGHT;
    drag = DRAG;
    surface = M_PI * RADIUS*RADIUS;
}

Balle::~Balle()
{
    //dtor
}

double Balle::getWeight(){return weight;}

void Balle::update(double delta) {
    Vector speed = anim.getSpeed();

    Vector Ft = 0;//(1/2) * drag * speed.norm() * surface * speed;
    nextAccel = (1/weight)*Ft + Vector(0,-9.81,0);

    nextVitesse = anim.getSpeed()+(delta*anim.getAccel());

    nextPosition = anim.getPos();
    nextPosition.translate(delta*anim.getSpeed());
    nextPosition.translate((((delta*delta)/2)*anim.getAccel()));
}

