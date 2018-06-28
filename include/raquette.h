#ifndef RAQUETTE_H
#define RAQUETTE_H

#include "forms.h"
#include "geometry.h"
#include "animation.h"
#include "Balle.h"
#include "math.h"
#include <SDL2/SDL.h>

class Raquette : public EllipseDisk
{
    public:
        Raquette(int SCREEN_WIDTH, int SCREEN_HEIGHT,
                 double TERRAIN_WIDTH, double TERRAIN_HEIGHT,
                 double z, double radius = 1.0);

        void update(double delta);
        void checkCollision(Balle &balle);
        void startCharging();
        void stopCharging();
    private:
        double z;
        double SCREEN_WIDTH;
        double SCREEN_HEIGHT;

        double TERRAIN_WIDTH;
        double TERRAIN_HEIGHT;
        double LIMIT_X;
        double LIMIT_Y;
        double chargeGauge;
        bool charging;
        Color startColor;
        Color chargedColor;

        const double MAX_CHARGE = 15;

        Point screenPosToWorldPos(int x, int y);
};

#endif // RAQUETTE_H
