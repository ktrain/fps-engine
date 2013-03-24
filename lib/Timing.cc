#if __APPLE__ && __MACH__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Timing.h"



long runtime( void )
{
  return glutGet( GLUT_ELAPSED_TIME );
}


int getFPS( void )
{
  const int MILLIS_TO_WAIT = 500;

  static long frames = 0, last_time = 0;
  static int fps = -1;

  long this_time = glutGet( GLUT_ELAPSED_TIME );
  long dt = this_time - last_time;

  frames++;

  // update fps every MILLIS_TO_WAIT ms
  if ( dt >= MILLIS_TO_WAIT )
  {
    fps = frames * 1000 / dt;
    last_time = this_time;
    frames = 0;
  }

  return fps;
}

