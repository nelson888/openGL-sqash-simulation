#include "Balle.h"

Balle::Balle(Point center, Vector accel):Sphere(RADIUS,BLACK)
{
    anim.setPos(center);
    anim.setAccel(accel);
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
    //force de trainee
    //Cx = constante = 0.5
    Vector speed = anim.getSpeed();

    Vector Ft = (1/2) * drag * speed.norm() * surface * speed;

    Vector P = weight * Vector(0,-9.81,0); //g = vecteur constant gravite (0, -9.81)
    Vector F = Vector(0.0, 0.0, 0.0);

    F = P + weight * anim.getAccel() + Ft;

    anim.setAccel((1.0/weight)*F);

    anim.setSpeed(anim.getSpeed()+(delta*anim.getAccel()));

    Point newPos = anim.getPos();
    newPos.translate(delta*anim.getSpeed());
    newPos.translate((((delta*delta)/2)*anim.getAccel()));
    anim.setPos(newPos);
}

