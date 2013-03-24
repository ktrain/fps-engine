#ifndef INPUT_H
#define INPUT_H

#include "lib/BasicMath.h"
#include "lib/Vector.h"
#include "lib/Matrix.h"


//
// static classes for handling input
//

class Keyboard
{
  public:
    static void keyPress( unsigned char, int, int );
    static void keyRelease( unsigned char, int, int );
    static const Vector* getMovement( void );

  protected:
    static Vector movement;
    static bool moveLeft, moveRight, moveForward, moveBackward,
                crouch;
};

class Mouse
{
  public:
    static void init( int, int );
    static void motion( int, int );
    static void click( int, int, int, int );
    static const Matrix* getRotation( void );

  protected:
    static int width, height;
    static Matrix rotation;
    static bool left_click, right_click, middle_click;

    static inline void calculateMouseCoords( int x, int y, Vector* v )
    {
      double z2;

      v->x = ( (2.0 * x) / width ) - 1.0;
      v->y = 1.0 - ( (2.0 * y) / height );
      z2 = 1 - ( v->x * v->x ) - ( v->y * v->y );
      v->z = ( z2 > 0.0 ) ? sqrt( z2 ) : 0.0;
    }
};


#endif  /* INPUT_H */

