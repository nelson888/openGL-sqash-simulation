#ifndef BALLE_H
#define BALLE_H

#define WEIGHT 24
#define RADIUS 0.02

class Balle:public Sphere
{
    public:
        Balle();
        virtual ~Balle();

        void render();
        Coordinates nextPosition();

        double getWeight();

    protected:

    private:
        double radius = RADIUS;
        double weight = WEIGHT;

        Coordinates position;
        Vector accel;
};

#endif // BALLE_H
