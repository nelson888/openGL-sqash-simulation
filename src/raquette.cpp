#include "raquette.h"

Point Raquette::screenPosToWorldPos(int x, int y) {
    Point point = Point(SCREEN_WIDTH - x,SCREEN_HEIGHT - y,z); //origine en haut a gauche

    point.x = point.x * TERRAIN_WIDTH/SCREEN_WIDTH - TERRAIN_WIDTH *0.5f;
    point.y = point.y * TERRAIN_HEIGHT/SCREEN_HEIGHT;
/*
    if (point.x > LIMIT_X) {
        point.x = LIMIT_X;
    }
    else if (point.x < -LIMIT_X) {
        point.x = -LIMIT_X;
    }
    if (point.y > LIMIT_Y) {
        point.y = LIMIT_Y;
    }
    else if (point.y < getCosFactor()) {
        point.y = getCosFactor();
    }*/
    return point;
}

void Raquette::update(double delta_t) {
    Form::update(delta_t);

    int x, y;
    SDL_GetMouseState(&x, &y);
    getAnim().setPos(screenPosToWorldPos(x,y));
}


