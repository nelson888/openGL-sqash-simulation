#ifndef RAQUETTE_H
#define RAQUETTE_H

#include "forms.h"
#include "geometry.h"
#include "animation.h"
#include <SDL2/SDL.h>


class Raquette : public EllipseDisk
{
    public:
        Raquette(int SCREEN_WIDTH, int SCREEN_HEIGHT,
                 double TERRAIN_WIDTH, double TERRAIN_HEIGHT,
                 double z, double radius = 1.0);

        void update(double delta);
    private:
        double z;
        double SCREEN_WIDTH;
        double SCREEN_HEIGHT;

        double TERRAIN_WIDTH;
        double TERRAIN_HEIGHT;
        double LIMIT_X;
        double LIMIT_Y;


        Point screenPosToWorldPos(int x, int y);
};

#endif // RAQUETTE_H
