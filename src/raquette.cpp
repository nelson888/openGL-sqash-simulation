#include "raquette.h"

Point Raquette::screenPosToWorldPos(int x, int y) {
    Point point = Point(SCREEN_WIDTH - x,SCREEN_HEIGHT - y,z);

    point.x = point.x * TERRAIN_WIDTH/SCREEN_WIDTH - TERRAIN_WIDTH/2;
    point.y = point.y * TERRAIN_HEIGHT/SCREEN_HEIGHT;

    return point;
}

void Raquette::update(double delta_t) {
    Form::update(delta_t);

    int x, y;
    SDL_GetMouseState(&x, &y);
    getAnim().setPos(screenPosToWorldPos(x,y));
    //origine en haut a gauche
}


