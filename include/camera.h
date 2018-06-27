#ifndef CAMERA_H
#define CAMERA_H

#include "geometry.h"
#include "terrain.h"
#include "math.h"


class Camera
{
    public:
        Camera(double LENGTH, double WIDTH,Point position, Point center) {
            this->position = position;
            this->look_at = center;
            this->WIDTH = WIDTH;
            this->LENGTH = LENGTH;
            degree = 180 + 90;
            radius = - position.z;
            degreeOffset = 0;
            radiusOffset = 0;
            this->update();
        }

        Point getPosition() {return position;}
        Point getLookAt() {return look_at;}

        void rotateBy(double offset);
        void moveBy(double z);

        void stopMoving();
        void stopRotating();

        //pour cacher les faces du terrain en fonction de la position de la camera
        void update(Terrain *terrain);

    protected:

    private:
        Point position;
        Point look_at;
        double radius;
        double degree;
        double LENGTH;
        double WIDTH;

        double degreeOffset;
        double radiusOffset;

    void update();
};

#endif // CAMERA_H
