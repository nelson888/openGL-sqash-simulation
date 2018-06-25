#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include "terrain.h"


using namespace std;

Terrain::Terrain(Point center, double length, double width, double height) {
    anim.setPos(center);
    this->length = length;
    this->width = width;
    this->height = height;

    ColorGradient WALL_COLOR = ColorGradient(Color(0.88f, 0.84f, 0.77f), Color(0.98f, 0.92f, 0.75f), Color(0.98f, 0.92f, 0.75f), Color(1.0f, 0.98f, 0.8f));
    ColorGradient GROUND_COLOR = ColorGradient(Color(227.0 / 255.0, 190.0 / 255.0, 145.0 / 255.0), Color(222.0 / 255.0, 180.0 / 255.0, 142.0 / 255.0), Color(222.0 / 255.0, 180.0 / 255.0f, 142.0f / 255.0f), Color(189.0 / 255.0f, 150.0f / 255.0f, 107.0f / 255.0f));
    ColorGradient LINE_COLOR = ColorGradient(Color(206.0 / 255.0, 11.0 / 255.0, 15.0 / 255.0), Color(226.0 / 255.0, 11.0 / 255.0, 15.0 / 255.0), Color(226.0 / 255.0, 11.0 / 255.0, 15.0 / 255.0), Color(226.0 / 255.0, 0.0 / 255.0, 0.0 / 255.0));

    faces[GROUND] = Face(Vector(1,0,0), Vector(0,0,1), Point(-length/2, 0, -width/2), length, width, GROUND_COLOR);
    faces[RIGHT] = Face(Vector(0,0,-1), Vector(0,1,0), Point(-length/2, 0, width/2), width, height, WALL_COLOR);
    faces[FRONT] = Face(Vector(1,0,0), Vector(0,1,0), Point(-length/2, 0, width/2), length, height, WALL_COLOR);
    faces[BACK] = Face(Vector(1,0,0), Vector(0,1,0), Point(-length/2, 0, -width/2), length, height, ColorGradient(WALL_COLOR, 0.6f));
    faces[LEFT] = Face(Vector(0,0,-1), Vector(0,1,0), Point(length/2, 0, width/2), width, height, WALL_COLOR);
    faces[ROOF] = Face(Vector(1,0,0), Vector(0,0,1), Point(-length/2, height, -width/2), length, width, GROUND_COLOR);

    lines[0] = Face(Vector(1,0,0), Vector(0,1,0), Point(-length/2 , 1.780 - LINE_WIDTH/2, width/2 -0.004), length, LINE_WIDTH, LINE_COLOR);
    lines[1] = Face(Vector(1,0,0), Vector(0,1,0), Point(-length/2 , 4.570 - LINE_WIDTH/2, width/2 -0.004), length, LINE_WIDTH, LINE_COLOR);
    lines[2] = Face(Vector(1,0,0), Vector(0,1,0), Point(-length/2 , 0.430 - LINE_WIDTH/2, width/2 -0.004), length, LINE_WIDTH * 3, LINE_COLOR);
    lines[3] = Face(Vector(1,0,0), Vector(0,0,1), Point(-length/2, 0.005, -width/2 + 4.26), length, LINE_WIDTH*3, LINE_COLOR);
    lines[4] = Face(Vector(1,0,0), Vector(0,0,1), Point(0, 0.005, -width/2), LINE_WIDTH, 4.260, LINE_COLOR);
    lines[5] = Face(Vector(1,0,0), Vector(0,0,1), Point(-length/2 + 1.6, 0.005, -width/2 + 2.610), LINE_WIDTH, 4.260 - 2.610, LINE_COLOR);
    lines[6] = Face(Vector(1,0,0), Vector(0,0,1), Point(length/2 - 1.6, 0.005, -width/2 + 2.610), LINE_WIDTH, 4.260 - 2.610, LINE_COLOR);
    lines[7] = Face(Vector(1,0,0), Vector(0,0,1), Point(-length/2, 0.005, -width/2 + 2.610), 1.6, LINE_WIDTH, LINE_COLOR);
    lines[8] = Face(Vector(1,0,0), Vector(0,0,1), Point(length/2 - 1.6, 0.005, -width/2 + 2.610), 1.6, LINE_WIDTH, LINE_COLOR);
    lines[9] = Face(Vector(0,-0.25,-1), Vector(0,1,0), Point(length/2 - 0.004, 4.57, width/2), width, LINE_WIDTH, LINE_COLOR);
    lines[10] = Face(Vector(0,-0.25,-1), Vector(0,1,0), Point(-length/2 + 0.004, 4.57, width/2), width, LINE_WIDTH, LINE_COLOR);

}



void Terrain::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
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

