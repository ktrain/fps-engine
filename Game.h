#ifndef GAME_H
#define GAME_H

#if __APPLE__ && __MACH__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "lib/Timing.h"
#include "lib/SceneGraph.h"
#include "lib/Camera.h"
#include "lib/Player.h"
#include "GUI.h"
#include "Input.h"


// this file should not be included anywhere except Game.cc


//
// statics
//

// view parameters
double fieldOfView = 75.0;
int window_width = 1360;
int window_height = 768;
double nearZ = 1.0;
double farZ = 1000.0;

// scene, camera, and player
Group world;
Camera camera;
Player player;

// light
float light0_pos[] = { 10.0, 0.0, 0.0 };
float light0_dif[] = {  1.0, 1.0, 1.0 };
float light0_amb[] = {  0.2, 0.2, 0.2 };

class TestShape : public Shape3D
{
  public:
    TestShape( void )
    {
      
    }
    void draw( void ) const
    {
      glutSolidCube( 5.0 );
    }
};


#endif  /* GAME_H */

