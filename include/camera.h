#ifndef CAMERA_H
#define CAMERA_H

#include "geometry.h"
#include "terrain.h"


class Camera
{
    public:
        Camera(double LENGTH, double WIDTH, Point camera_position, Point center) {
            this->position = camera_position;
            this->look_at = center;
            this->WIDTH = WIDTH;
            this->LENGTH = LENGTH;
            degree = 0;
        }

        Point getPosition() {return position;}
        Point getLookAt() {return look_at;}

        void rotateFromCenter(double offset);
        void moveBy(Vector vec);

        //pour cacher les faces du terrain en fonction de la position de la camera
        void update(Terrain *terrain);

    protected:

    private:
        Point position;
        Point look_at;
        double degree;
        double LENGTH;
        double WIDTH;
};

#endif // CAMERA_H
