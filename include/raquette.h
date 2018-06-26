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
                 double z, double sinFactorr = 1.0, double cosFactorr = 1.0):EllipseDisk(10, X_AXIS, Y_AXIS, WHITE, sinFactorr, cosFactorr) {
            getAnim().setPos(Point(0.0, 0.0, z));
            this->z = z;
            this->SCREEN_HEIGHT = SCREEN_HEIGHT;
            this->SCREEN_WIDTH = SCREEN_WIDTH;
            this->TERRAIN_HEIGHT = TERRAIN_HEIGHT;
            this->TERRAIN_WIDTH = TERRAIN_WIDTH;
        }

        void update(double delta);
    private:
        double z;
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;

        double TERRAIN_WIDTH;
        double TERRAIN_HEIGHT;

        Point screenPosToWorldPos(int x, int y);
};

#endif // RAQUETTE_H
