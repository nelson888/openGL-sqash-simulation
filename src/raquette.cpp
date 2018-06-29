#include "raquette.h"
#include <stdio.h>
Raquette::Raquette(int SCREEN_WIDTH, int SCREEN_HEIGHT,
                 double TERRAIN_WIDTH, double TERRAIN_HEIGHT,
                 double z, double radius):EllipseDisk(radius, X_AXIS, Y_AXIS, Color(0.7f,0.7f,0.7f)) {
            getAnim().setPos(Point(0.0, 0.0, z));
            col.a = 0.7f;
            double maxFactor = 0.6;
            this->z = z;
            this->SCREEN_HEIGHT = maxFactor * ((double)SCREEN_HEIGHT);
            this->SCREEN_WIDTH = maxFactor * ((double)SCREEN_WIDTH);
            this->TERRAIN_HEIGHT = TERRAIN_HEIGHT;
            this->TERRAIN_WIDTH = TERRAIN_WIDTH;
            LIMIT_X = TERRAIN_WIDTH * 0.45f;
            LIMIT_Y = TERRAIN_HEIGHT * 0.8f;
            chargeGauge = -1;
            startColor = getColor();
            chargedColor = Color(RED);
            chargedColor.a = startColor.a;
            charging = false;
            started = false;
}

/**
fonction qui convertit les coordonnées de la souris en coordonnées dans le terrain
*/
Point Raquette::screenPosToWorldPos(int x, int y) {
    Point point = Point(SCREEN_WIDTH - x,SCREEN_HEIGHT - y,z); //origine en haut a gauche

    point.x = point.x * TERRAIN_WIDTH/SCREEN_WIDTH - TERRAIN_WIDTH *0.5f + getRadius() * 2;
    point.y = point.y * TERRAIN_HEIGHT/SCREEN_HEIGHT + getRadius();

    if (point.x > LIMIT_X) {
        point.x = LIMIT_X;
    }
    else if (point.x < -LIMIT_X) {
        point.x = -LIMIT_X;
    }
    if (point.y > LIMIT_Y) {
        point.y = LIMIT_Y;
    }
    else if (point.y < getRadius()) {
        point.y = getRadius();
    }
    return point;
}

void Raquette::startCharging(){
    chargeGauge = 0.0;
    charging = true;
}

void Raquette::stopCharging(){
    charging = false;
}

void Raquette::start(Balle &balle) {
    started = true;
    Point position = balle.getAnim().getPos();
    position.z = z - 0.01; //to provoke collision
    balle.setPosition(position);
}

void Raquette::checkCollision(Balle &balle) {
    if (!started) {
        Point p = getAnim().getPos();
        Vector v = Vector(p.x, p.y - TERRAIN_HEIGHT*0.2, 0);
        v.x = (1.0 / TERRAIN_WIDTH) * v.x;
        v.y =  (1.0/ TERRAIN_HEIGHT) * v.y;
        p.translate(v);
        p.z = z + balle.getRadius();
        balle.setPosition(p);

        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
            start(balle);
        }
        return;
    }
    Point ballPos = balle.getAnim().getPos();
    Point position = getAnim().getPos();

    if (ballPos.z - balle.getRadius() > position.z) {
        return;
    }

    Vector v = Vector(position, ballPos);
    if (v.norm() < getRadius()) {

        if (v.isZero()) {
            v = Vector(0.0, 0.0, 1.0);
        }

        v = (1.0/v.norm()) * v;

        v.z = 1.6;

        v.setLength(20 + chargeGauge*2);

        Vector bVitesse = balle.getAnim().getSpeed();

        balle.setVitesse(v);
        ballPos.z = z + balle.getRadius();
        balle.setPosition(ballPos);

        charging = false;
        chargeGauge = 0.0;
        setColor(startColor);
    }

}

void Raquette::update(double delta_t) {
    Form::update(delta_t);

    if (charging) {
        if (chargeGauge < MAX_CHARGE) {
            Color color = getColor();
            //change la couleur en fonction du chargement
            color = startColor + (chargeGauge/MAX_CHARGE) * (RED - startColor);
            chargeGauge += delta_t * MAX_CHARGE/0.5;
            setColor(color);
        }
    }
    int x, y;
    int mouseFlags = SDL_GetMouseState(&x, &y);
    getAnim().setPos(screenPosToWorldPos(x,y));

    bool isCharging = mouseFlags & SDL_BUTTON(SDL_BUTTON_LEFT);

    if (!charging && isCharging) {
        charging = true;
    }

    if (charging && (mouseFlags & SDL_BUTTON(SDL_BUTTON_RIGHT))) {
        charging = false;
        chargeGauge = 0.0;
        setColor(startColor);
    }


}
