// Using SDL, SDL OpenGL and standard IO
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
//#include <GL/glu.h> //pour linux

// Module for space geometry
#include "geometry.h"
// Module for generating and rendering forms
#include "forms.h"
#include "terrain.h"
#include "Balle.h"
#include "raquette.h"
#include "camera.h"


using namespace std;


/***************************************************************************/
/* Constants and functions declarations                                    */
/***************************************************************************/
// Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Max number of forms : static allocation
const int MAX_FORMS_NUMBER = 10;

// Animation actualization delay (in ms) => 100 updates per second
const Uint32 ANIM_DELAY = 1;

//Terrain dimensions
const double WIDTH = 6.4;
const double LENGTH = 9.75;
const double HEIGHT = 4.8;

const double CAMERA_Z_OFFSET  = 0.2;
const double CAMERA_ANGLE_OFFSET = 1.5;

// Starts up SDL, creates window, and initializes OpenGL
bool init(SDL_Window** window, SDL_GLContext* context);

// Initializes matrices and clear color
bool initGL();

// Updating forms for animation
void update(Form* formlist[MAX_FORMS_NUMBER], double delta_t);

// Renders scene to the screen
const void render(Form* formlist[MAX_FORMS_NUMBER], const Point &cam_pos);

// Frees media and shuts down SDL
void close(SDL_Window** window);


/***************************************************************************/
/* Functions implementations                                               */
/***************************************************************************/
bool init(SDL_Window** window, SDL_GLContext* context)
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        // Use OpenGL 2.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        // Create window
        *window = SDL_CreateWindow( "TP intro OpenGL / SDL 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
        if( *window == NULL )
        {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }
        else
        {
            // Create context
            *context = SDL_GL_CreateContext(*window);
            if( *context == NULL )
            {
                cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << endl;
                success = false;
            }
            else
            {
                // Use Vsync
                if(SDL_GL_SetSwapInterval(1) < 0)
                {
                    cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << endl;
                }

                // Initialize OpenGL
                if( !initGL() )
                {
                    cout << "Unable to initialize OpenGL!"  << endl;
                    success = false;
                }
            }
        }
    }

    //enable transparancy
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return success;
}


bool initGL()
{
    bool success = true;
    GLenum error = GL_NO_ERROR;

    // Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the viewport : use all the window to display the rendered scene
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Fix aspect ratio and depth clipping planes
    gluPerspective(40.0, (GLdouble)SCREEN_WIDTH/SCREEN_HEIGHT, 1.0, 100.0);


    // Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Initialize clear color : black with no transparency
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

//    glEnable(GL_LIGHT0);
//    glEnable(GL_LIGHTING);

    // Activate Z-Buffer


    // Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        cout << "Error initializing OpenGL!  " << gluErrorString( error ) << endl;
        success = false;
    }

    glEnable(GL_DEPTH_TEST);

    return success;
}

void update(Form* formlist[MAX_FORMS_NUMBER], double delta_t)
{
    // Update the list of forms
    unsigned short i = 0;
    while(formlist[i] != NULL)
    {
        formlist[i]->update(delta_t);
        i++;
    }
}

const void render(Form* formlist[MAX_FORMS_NUMBER], const Point &cam_pos, const Point &look_at)
{
    // Clear color buffer and Z-Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Set the camera position and parameters
    gluLookAt(cam_pos.x,cam_pos.y,cam_pos.z, look_at.x, look_at.y, look_at.z, 0.0,1.0,0.0);
    // Isometric view
    //glRotated(-45, 0, 1, 0);
    //glRotated(30, 1, 0, -1);

    // X, Y and Z axis
    glPushMatrix(); // Preserve the camera viewing point for further forms
    // Render the coordinates system
    glBegin(GL_LINES);
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(1, 0, 0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 1, 0);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 0, 1);
    }
    glEnd();
    glPopMatrix(); // Restore the camera viewing point for next object

    // Render the list of forms
    unsigned short i = 0;
    while(formlist[i] != NULL)
    {
        glPushMatrix(); // Preserve the camera viewing point for further forms
        formlist[i]->render();
        glPopMatrix(); // Restore the camera viewing point for next object
        i++;
    }
}

void close(SDL_Window** window)
{
    //Destroy window
    SDL_DestroyWindow(*window);
    *window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}


/***************************************************************************/
/* MAIN Function                                                           */
/***************************************************************************/

//TODO METTRE GRAVITY
//TODO RESISTANCE AIR
int main(int argc, char* args[])
{
    // The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    // OpenGL context
    SDL_GLContext gContext;


    // Start up SDL and create window
    if( !init(&gWindow, &gContext))
    {
        cout << "Failed to initialize!" << endl;
    }
    else
    {
        // Main loop flag
        bool quit = false;
        bool space = false;
        bool freeze = false;
        Uint32 current_time, previous_time, elapsed_time, paused_time = 0;

        // Event handler
        SDL_Event event;

        Camera *camera  = new Camera(LENGTH, WIDTH, HEIGHT, Point(0.0, 2.0, -LENGTH), Point(0.0,HEIGHT/2, 0.0), 180 + 90, -1);

        // The forms to render
        Form* forms_list[MAX_FORMS_NUMBER];
        unsigned short number_of_forms = 0, i;
        for (i=0; i<MAX_FORMS_NUMBER; i++)
        {
            forms_list[i] = NULL;
        }


        Terrain *terrain = new Terrain(Point(0, 0.0, 0.0), WIDTH, LENGTH, HEIGHT);
        forms_list[number_of_forms] = terrain;
        number_of_forms++;

        Balle *balle = new Balle(Point(0.0,HEIGHT/2,0), Vector(0,0,5000));
        forms_list[number_of_forms] = balle;
        number_of_forms++;

        Raquette *raquette = new Raquette(SCREEN_WIDTH, SCREEN_HEIGHT,
                                          WIDTH, HEIGHT, -LENGTH*0.45, 0.5);
        forms_list[number_of_forms] = raquette;
        number_of_forms++;
        raquette->getAnim().setPos(Point(0.0, HEIGHT/2, 0.0));




        // Get first "current time"
        previous_time = SDL_GetTicks();
        // While application is running
        while(!quit)
        {
            // Handle events on queue
            while(SDL_PollEvent(&event) != 0)
            {
                int x = 0, y = 0;
                SDL_Keycode key_pressed = event.key.keysym.sym;

                switch(event.type)
                {
                // User requests quit
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    // Handle key pressed with current mouse position
                    SDL_GetMouseState( &x, &y );

                    switch(key_pressed)
                    {
                    // Quit the program when 'q' or Escape keys are pressed
                    case SDLK_q:
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_SPACE:
                        space = true;
                        break;
                    case SDLK_DOWN:
                        if (space) {
                            camera->rotateYBy(CAMERA_ANGLE_OFFSET);
                        } else {
                            camera->moveBy(-CAMERA_Z_OFFSET);
                        }
                        break;
                    case SDLK_UP:
                        if (space) {
                            camera->rotateYBy(-CAMERA_ANGLE_OFFSET);
                        } else {
                            camera->moveBy(CAMERA_Z_OFFSET);
                        }
                        break;
                    case SDLK_LEFT:
                        camera->rotateBy(CAMERA_ANGLE_OFFSET);
                        //look_at.x += CAMERA_MOOVE_OFFSET;
                        break;
                    case SDLK_RIGHT:
                        camera->rotateBy(-CAMERA_ANGLE_OFFSET);
                        //look_at.x -= CAMERA_MOOVE_OFFSET;
                        break;
                    case SDLK_f:
                        if (!freeze) {
                            paused_time = SDL_GetTicks(); //debut de la pause
                        } else {

                            previous_time += SDL_GetTicks() - paused_time;
                            paused_time = 0;
                        }
                        freeze = !freeze;
                        break;
                    default:
                        break;
                    }
                    break;
                case SDL_KEYUP:
                    switch(key_pressed)
                    {
                    case SDLK_DOWN:
                    case SDLK_UP:
                        camera->stopRotatingY();
                        camera->stopMoving();
                        break;
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        camera->stopRotating();
                        //look_at.x += CAMERA_MOOVE_OFFSET;
                        break;
                    case SDLK_SPACE:
                        space = false;
                        break;
                    default:
                        break;
                    }
                    break;

                default:
                    break;


                }
            }

            if (!freeze) {
                current_time = SDL_GetTicks(); // get the elapsed time from SDL initialization (ms)
                // Update the scene
                elapsed_time = current_time - previous_time;
                if (elapsed_time > ANIM_DELAY)
                {
                    previous_time = current_time;
                    update(forms_list, 1e-3 * 0.5 *  elapsed_time); // International system units : seconds
                    terrain->checkCollision(*balle);
                    raquette->checkCollision(*balle);
                }
            }
            camera->update(terrain);
            // Render the scene
            render(forms_list, camera->getPosition(), camera->getLookAt());

            // Update window screen
            SDL_GL_SwapWindow(gWindow);
        }
    }

    // Free resources and close SDL
    close(&gWindow);

    return 0;
}
