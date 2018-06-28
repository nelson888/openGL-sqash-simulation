#ifndef CAMERA_H
#define CAMERA_H

#include "geometry.h"
#include "terrain.h"
#include "math.h"


class Camera
{
    public:
        Camera(double LENGTH, double WIDTH, double HEIGHT, Point position, Point center, double degree, double degreeY) {
            this->position = position;
            this->look_at = center;
            this->WIDTH = WIDTH;
            this->LENGTH = LENGTH;
            this->HEIGHT = HEIGHT;
            this->degree = degree;
            this->degreeY = degreeY;
            radius = abs(position.z);
            radiusY = 20;
            degreeOffset = 0;
            degreeYOffset = 0;
            radiusOffset = 0;
            this->update();
        }

        Point getPosition() {return position;}
        Point getLookAt() {return look_at;}

        void rotateBy(double offset);
        void rotateYBy(double offset);
        void moveBy(double z);

        void stopMoving();
        void stopRotating();
        void stopRotatingY();

        //pour cacher les faces du terrain en fonction de la position de la camera
        void update(Terrain *terrain);

    protected:

    private:
        Point position;
        Point look_at;
        double radius;
        double radiusY;
        double degree;
        double degreeY;
        double LENGTH;
        double WIDTH;
        double HEIGHT;

        double degreeOffset;
        double degreeYOffset;
        double radiusOffset;

    void update();
};

#endif // CAMERA_H
