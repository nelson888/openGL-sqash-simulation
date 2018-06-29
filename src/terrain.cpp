#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include "terrain.h"


using namespace std;

Terrain::Terrain(Point center, double width, double length, double height) {
    anim.setPos(center);
    this->width = width;
    this->length = length;
    this->height = height;

    ColorGradient WALL_COLOR = ColorGradient(Color(0.88f, 0.84f, 0.77f), Color(0.98f, 0.92f, 0.75f), Color(0.98f, 0.92f, 0.75f), Color(1.0f, 0.98f, 0.8f));
    ColorGradient GROUND_COLOR = ColorGradient(Color(227.0 / 255.0, 190.0 / 255.0, 145.0 / 255.0), Color(222.0 / 255.0, 180.0 / 255.0, 142.0 / 255.0), Color(222.0 / 255.0, 180.0 / 255.0f, 142.0f / 255.0f), Color(189.0 / 255.0f, 150.0f / 255.0f, 107.0f / 255.0f));
    ColorGradient LINE_COLOR = ColorGradient(Color(206.0 / 255.0, 11.0 / 255.0, 15.0 / 255.0), Color(226.0 / 255.0, 11.0 / 255.0, 15.0 / 255.0), Color(226.0 / 255.0, 11.0 / 255.0, 15.0 / 255.0), Color(226.0 / 255.0, 0.0 / 255.0, 0.0 / 255.0));

    faces[GROUND] = TerrainFace(Vector(1,0,0), Vector(0,0,1), Point(-width/2, 0, -length/2), width, length, GROUND_COLOR, 6);
    faces[RIGHT] = TerrainFace(Vector(0,0,-1), Vector(0,1,0), Point(-width/2, 0, length/2), length, height, WALL_COLOR, 1);
    faces[FRONT] = TerrainFace(Vector(1,0,0), Vector(0,1,0), Point(-width/2, 0, length/2), width, height, WALL_COLOR, 3);
    faces[BACK] = TerrainFace(Vector(1,0,0), Vector(0,1,0), Point(-width/2, 0, -length/2), width, height, WALL_COLOR);
    faces[LEFT] = TerrainFace(Vector(0,0,-1), Vector(0,1,0), Point(width/2, 0, length/2), length, height, WALL_COLOR, 1);
    faces[ROOF] = TerrainFace(Vector(1,0,0), Vector(0,0,1), Point(-width/2, height, -length/2), width, length, GROUND_COLOR);

    lines[0] = Face(Vector(1,0,0), Vector(0,1,0), Point(-width/2 , 1.780 - LINE_WIDTH/2, length/2 -0.004), width, LINE_WIDTH, LINE_COLOR);
    lines[1] = Face(Vector(1,0,0), Vector(0,1,0), Point(-width/2 , 4.570 - LINE_WIDTH/2, length/2 -0.004), width, LINE_WIDTH, LINE_COLOR);
    lines[2] = Face(Vector(1,0,0), Vector(0,1,0), Point(-width/2 , 0.430 - LINE_WIDTH/2, length/2 -0.004), width, LINE_WIDTH * 3, LINE_COLOR);
    lines[3] = Face(Vector(1,0,0), Vector(0,0,1), Point(-width/2, 0.005, -length/2 + 4.26), width, LINE_WIDTH*3, LINE_COLOR);
    lines[4] = Face(Vector(1,0,0), Vector(0,0,1), Point(0, 0.005, -length/2), LINE_WIDTH, 4.260, LINE_COLOR);
    lines[5] = Face(Vector(1,0,0), Vector(0,0,1), Point(-width/2 + 1.6, 0.005, -length/2 + 2.610), LINE_WIDTH, 4.260 - 2.610, LINE_COLOR);
    lines[6] = Face(Vector(1,0,0), Vector(0,0,1), Point(width/2 - 1.6, 0.005, -length/2 + 2.610), LINE_WIDTH, 4.260 - 2.610, LINE_COLOR);
    lines[7] = Face(Vector(1,0,0), Vector(0,0,1), Point(-width/2, 0.005, -length/2 + 2.610), 1.6, LINE_WIDTH, LINE_COLOR);
    lines[8] = Face(Vector(1,0,0), Vector(0,0,1), Point(width/2 - 1.6, 0.005, -length/2 + 2.610), 1.6, LINE_WIDTH, LINE_COLOR);
    lines[9] = Face(Vector(0,-0.25,-1), Vector(0,1,0), Point(width/2 - 0.004, 4.57, length/2), length*1.03, LINE_WIDTH, LINE_COLOR);
    lines[10] = Face(Vector(0,-0.25,-1), Vector(0,1,0), Point(-width/2 + 0.004, 4.57, length/2), length*1.03, LINE_WIDTH, LINE_COLOR);

    //set lines attached to faces
    faces[FRONT].lines[0] = 0;
    faces[FRONT].lines[1] = 1;
    faces[FRONT].lines[2] = 2;
    faces[LEFT].lines[0] = 9;
    faces[RIGHT].lines[0] = 10;

    faces[GROUND].lines[0] = 3;
    faces[GROUND].lines[1] = 4;
    faces[GROUND].lines[2] = 5;
    faces[GROUND].lines[3] = 6;
    faces[GROUND].lines[4] = 7;
    faces[GROUND].lines[5] = 8;

}


void Terrain::hideFace(int i) {
    faces[i].setAlpha(0.0f);
    for(int j=0;j<faces[i].nbLines; j++) {
        lines[faces[i].lines[j]].setAlpha(0.0f);
    }
}

void Terrain::showAllFaces() {
    for (int i=0; i< NB_FACES; i++) {
        faces[i].setAlpha(1.0f);
        for(int j=0;j<faces[i].nbLines; j++) {
            lines[faces[i].lines[j]].setAlpha(1.0f);
        }
    }
}

void Terrain::update(double delta_t)
{
}

void Terrain::checkCollision(Balle &balle) {
    Vector nextAccel = balle.getNextAccel();
    Point nextPosition = balle.getNextPosition();
    Vector nextVitesse = balle.getNextVitesse();

    //on gere les cas de dépassement a cause de vitesse trop elevée
    if (nextPosition.x + balle.getRadius() > faces[LEFT].getAnim().getPos().x) { // a gauche
        nextPosition.x = faces[LEFT].getAnim().getPos().x - balle.getRadius() + 0.01;
    } else if (nextPosition.x - balle.getRadius() < faces[RIGHT].getAnim().getPos().x) {// a droite
        nextPosition.x = faces[RIGHT].getAnim().getPos().x + balle.getRadius() - 0.01;
    }

    if (nextPosition.z + balle.getRadius() > faces[FRONT].getAnim().getPos().z) { // en haut
        nextPosition.z = faces[FRONT].getAnim().getPos().z - balle.getRadius() + 0.01;
    } else if (nextPosition.z - balle.getRadius() < faces[BACK].getAnim().getPos().z) {// a droite
        nextPosition.z = faces[BACK].getAnim().getPos().z + balle.getRadius() - 0.01;
    }

    if (nextPosition.z + balle.getRadius() > faces[FRONT].getAnim().getPos().z) { // devant
        nextPosition.z = faces[FRONT].getAnim().getPos().z - balle.getRadius() + 0.01;
    } else if (nextPosition.z - balle.getRadius() < faces[BACK].getAnim().getPos().z) {// derriere
        nextPosition.z = faces[BACK].getAnim().getPos().z + balle.getRadius() - 0.01;
    }

    if (nextPosition.y + balle.getRadius() > faces[ROOF].getAnim().getPos().y) { // en haut
        nextPosition.y = faces[ROOF].getAnim().getPos().y - balle.getRadius() + 0.01;
    } else if (nextPosition.y - balle.getRadius() < faces[GROUND].getAnim().getPos().y) {// en bas
        nextPosition.y = faces[GROUND].getAnim().getPos().y + balle.getRadius() - 0.01;
    }

    for(int i=0; i<6;i++) {
        Face face = faces[i];

        Vector NormalePlan = face.getVdir1()^face.getVdir2();
        Vector DistanceMurC2 = ((Vector(nextPosition,face.getAnim().getPos())) * NormalePlan );

        if(DistanceMurC2.norm()<=balle.getRadius()){
            if(i == LEFT) {
                nextVitesse.x = -REBOND_SCALAR * nextVitesse.x;
            }
            if(i == RIGHT) {
                nextVitesse.x = -REBOND_SCALAR * nextVitesse.x;

            }
            if(i == FRONT) {
                nextVitesse.z = -REBOND_SCALAR * nextVitesse.z;
            }
            if(i == BACK) {
                nextVitesse.z = -REBOND_SCALAR * nextVitesse.z;
            }
            if(i == GROUND) {
                nextVitesse.y = - REBOND_SCALAR * nextVitesse.y ;
                nextVitesse = 0.99*nextVitesse;

            }
            if(i == ROOF) {
                nextVitesse.y = - REBOND_SCALAR * nextVitesse.y;
                nextPosition.y = faces[ROOF].getAnim().getPos().y - balle.getRadius() - 0.01;
            }
        }
    }

    balle.setAccel(nextAccel);
    balle.setVitesse(nextVitesse);
    balle.setPosition(nextPosition);
}

void Terrain::render()
{
    //translate for all forms of Terrain
    Form::render();
    for (int i=0; i < NB_FACES; i++){
        glPushMatrix(); // Preserve the camera viewing point for Terrain's forms
        faces[i].render();
        glPopMatrix(); // Restore the camera viewing point for next object
    }

    for (int i=0; i < NB_LINES; i++){
        glPushMatrix(); // Preserve the camera viewing point for Terrain's forms
        lines[i].render();
        glPopMatrix(); // Restore the camera viewing point for next object
    }
}

