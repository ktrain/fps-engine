#include <stdlib.h>
#include <stdio.h>

#if __APPLE__ && __MACH__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "lib/Vector.h"
#include "Input.h"



//
// Keyboard
//

// static defs
bool Keyboard::moveLeft = false;
bool Keyboard::moveRight = false;
bool Keyboard::moveForward = false;
bool Keyboard::moveBackward = false;
bool Keyboard::crouch = false;
Vector Keyboard::movement;

void Keyboard::keyPress( unsigned char key, int, int )
{
  int mod = glutGetModifiers();

  crouch = mod & GLUT_ACTIVE_CTRL;

  switch ( key )
  {
  case 'a':
    // strafe left
    moveLeft = true;
    break;
  case 'd':
    // strafe right
    moveRight = true;
    break;
  case 'w':
    // move forward
    moveForward = true;
    break;
  case 's':
    // move backward
    moveBackward = true;
    break;
  case 27:
    (void) fprintf( stderr, "zomg\n" );
    exit( 1 );
    break;
  }
}


void Keyboard::keyRelease( unsigned char key, int, int )
{
  int mod = glutGetModifiers();

  crouch = mod & GLUT_ACTIVE_CTRL;

  switch ( key )
  {
  case 'a':
    // stop strafing left
    moveLeft = false;
    break;
  case 'd':
    // stop strafing right
    moveRight = false;
    break;
  case 'w':
    // stop moving forward
    moveForward = false;
    break;
  case 's':
    // stop moving backward
    moveBackward = false;
    break;
  }
}


// Normalizes Vector dest in the direction dictated by the controls.
const Vector* Keyboard::getMovement( void )
{
  movement.zero();

  if ( moveLeft )     movement.x -= 1.0;
  if ( moveRight )    movement.x += 1.0;
  if ( moveForward )  movement.z -= 1.0;
  if ( moveBackward ) movement.z += 1.0;

  movement.normalize();

  return &movement;
}



//
// Mouse
//

// static defs
int Mouse::width = 1, Mouse::height = 1;  // avoid zero divide
Matrix Mouse::rotation;
bool Mouse::left_click = false, Mouse::right_click = false, Mouse::middle_click = false;

void Mouse::init( int w, int h )
{
  width = w;
  height = h;
  rotation.identity();
}


void Mouse::motion( int x, int y )
{
  static Vector prev;
  Vector axis, curr;
  double theta;

  /*static int prevX = width / 2.0;
  static int prevY = height / 2.0;
  double thetaX = x - prevX;
  double thetaY = y - prevY;*/

  // could we just move the mouse to the center of the window?

  if ( prev.x == 0.0 && prev.y == 0.0 && prev.z == 0.0 )
  {
    calculateMouseCoords( x, y, &prev );
  }

  // calculate current vector
  calculateMouseCoords( x, y, &curr );
  curr.normalize();

  // calculate rotation axis
  Vector::Cross( &axis, &prev, &curr );
  axis.normalize();
  theta = -acos( Vector::Dot( &prev, &curr ) );
  rotation.rotate( theta, &axis );

  // save current vector for next calculation
  prev.set( &curr );
}


void Mouse::click( int button, int state, int, int )
{
  switch ( button )
  {
  case GLUT_LEFT_BUTTON:
    left_click = ( state == GLUT_DOWN );
    break;
  case GLUT_RIGHT_BUTTON:
    right_click = ( state == GLUT_DOWN );
    break;
  case GLUT_MIDDLE_BUTTON:
    middle_click = ( state == GLUT_DOWN );
    break;
  }
}


const Matrix* Mouse::getRotation( void )
{
  return &rotation;
}

