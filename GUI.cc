#include <stdio.h>

#if __APPLE__ && __MACH__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "lib/Timing.h"
#include "GUI.h"


// http://www.lighthouse3d.com/opengl/glut/index.php?bmpfontortho
void switchOrthographicProjection( int width, int height )
{
  // switch to orthographic projection
  glMatrixMode( GL_PROJECTION );
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D( 0, width, 0, height );
  // invert the y axis, down is positive
  glScalef( 1.0f, -1.0f, 1.0f );
  // move the origin from bottom-left to upper-left
  glTranslatef( 0.0f, -height, 0.0f );
  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glLoadIdentity();
}

void switchPerspectiveProjection()
{
  // switch back to perspective projection
  glMatrixMode( GL_PROJECTION );
  glPopMatrix();
  glMatrixMode( GL_MODELVIEW );
}

void drawGUI( int width, int height )
{
  char fps[32];
  char *c = &fps[0];

  (void) snprintf( fps, sizeof(fps), "%d fps", getFPS() );

  switchOrthographicProjection( width, height );

  glColor3f( 1.0f, 1.0f, 0.9f );    // why is it so dark?
  // overlay fps
  glRasterPos2f( 30.f, 35.f );
  while ( *c )
  {
    glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *c );
    c++;
  }

  switchPerspectiveProjection();
}

