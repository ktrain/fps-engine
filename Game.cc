#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "Game.h"



void handleInput( void )
{
  // the player tells give us the movement vector based on the input vector
  Vector movement;
  player.getRelativeMotion( &movement, Keyboard::getMovement() );

  // move the world, not the player
  // i don't like it, but that's the way OpenGL is
  if ( movement.isNonZero() )
  {
    // reverse the direction since the movement vector is the player's;
    // the world's relative motion is in the opposite direction.
    movement = -movement;
    world.moveRelative( &movement );
  }


  const Matrix* rotation = Mouse::getRotation();
  player.setRotation( rotation );
  //world.loadMatrix( rotation );
}


void reshape( int w, int h )
{
  window_width = w;
  window_height = h;
  glViewport( 0, 0, w, h );
  camera.setPerspective( fieldOfView, w, h, nearZ, farZ );
  Mouse::init( w, h );
}


void display( void )
{
  // clear color and depth buffers
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  drawGUI( window_height, window_width );

  handleInput();

  world.draw();

  glutSwapBuffers();
}


void idle( void )
{
  display();
}


void initScene( void )
{
  Matrix m;

  m.makeTranslate( 0.0, 0.0, -30.0 );
  world.loadMatrix( &m );

  m.makeTranslate( 0.0, 0.0, 0.0 );
  Group *g1 = new Group();
  g1->loadMatrix( &m );

  world.add( g1 );
  g1->add( new TestShape() );
}


int main( int argc, char* argv[] )
{
  // leave this here, it separates compiler stuff from output
  (void) printf( "\n" );

  // initialize glut
  glutInit( &argc, argv );
  // use double buffering, rgb colors, and depth buffering
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
  glutInitWindowSize( window_width, window_height );
  glutInitWindowPosition( 100, 100 );
  glutCreateWindow( "Game" );

  // enable depth buffering
  glEnable( GL_DEPTH_TEST );
  glClear( GL_DEPTH_BUFFER_BIT );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );   	  // set clear color to black
  glShadeModel( GL_SMOOTH );
  glEnable( GL_NORMALIZE );

  // generate light (for now)
  glEnable( GL_LIGHTING );
  glLightfv( GL_LIGHT0, GL_POSITION, light0_pos );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, light0_dif );
  glLightfv( GL_LIGHT0, GL_AMBIENT, light0_amb );
  glEnable( GL_LIGHT0 );

  // install display callback functions
  glutDisplayFunc( display );
  glutIdleFunc( idle );
  glutReshapeFunc( reshape );

  // install input callback functions
  glutIgnoreKeyRepeat( true );
  glutSetCursor( GLUT_CURSOR_NONE );
  glutKeyboardFunc( Keyboard::keyPress );
  glutKeyboardUpFunc( Keyboard::keyRelease );
  glutPassiveMotionFunc( Mouse::motion );
  glutMotionFunc( Mouse::motion );
  //glutMouseFunc(  );

  // initialize mouse
  Mouse::init( window_width, window_height );

  // make the scene
  initScene();

  // go
  glutMainLoop();

  return 0;
}

