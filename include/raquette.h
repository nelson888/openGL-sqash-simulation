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
                 double z, double sinFactorr = 1.0, double cosFactorr = 1.0):EllipseDisk(X_AXIS, Y_AXIS, WHITE, sinFactorr, cosFactorr) {
            getAnim().setPos(Point(0.0, 0.0, z));
            col.a = 0.7f;
            double maxFactor = 0.8;
            this->z = z;
            this->SCREEN_HEIGHT = maxFactor * ((double)SCREEN_HEIGHT);
            this->SCREEN_WIDTH = maxFactor * ((double)SCREEN_WIDTH);
            this->TERRAIN_HEIGHT = TERRAIN_HEIGHT;
            this->TERRAIN_WIDTH = TERRAIN_WIDTH;
            LIMIT_X = TERRAIN_WIDTH * 0.8f;
            LIMIT_Y = TERRAIN_HEIGHT * 0.8f;
        }

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
