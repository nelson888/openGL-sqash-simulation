#ifndef BALLE_H
#define BALLE_H

#define WEIGHT 24
#define RADIUS 0.02

class Balle
{
    public:
        Balle();
        virtual ~Balle();

        void render();
        Coordinates nextPosition();

    protected:

    private:
        double radius = RADIUS;
        double weight = WEIGHT;

        Sphere glForm = Sphere(radius, BLACK);

        Coordinates position;
        Vector accel;
};

#endif // BALLE_H
