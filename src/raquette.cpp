#include "raquette.h"

Raquette::Raquette(int SCREEN_WIDTH, int SCREEN_HEIGHT,
                 double TERRAIN_WIDTH, double TERRAIN_HEIGHT,
                 double z, double radius):EllipseDisk(radius, X_AXIS, 0.7 * Y_AXIS, Color(0.7f,0.7f,0.7f)) {
            getAnim().setPos(Point(0.0, 0.0, z));
            col.a = 0.7f;
            double maxFactor = 0.75;
            this->z = z;
            this->SCREEN_HEIGHT = maxFactor * ((double)SCREEN_HEIGHT);
            this->SCREEN_WIDTH = maxFactor * ((double)SCREEN_WIDTH);
            this->TERRAIN_HEIGHT = TERRAIN_HEIGHT;
            this->TERRAIN_WIDTH = TERRAIN_WIDTH;
            LIMIT_X = TERRAIN_WIDTH * 0.45f;
            LIMIT_Y = TERRAIN_HEIGHT * 0.8f;
}

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

void Raquette::update(double delta_t) {
    Form::update(delta_t);

    int x, y;
    SDL_GetMouseState(&x, &y);
    getAnim().setPos(screenPosToWorldPos(x,y));
}


