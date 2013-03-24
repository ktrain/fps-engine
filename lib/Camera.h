#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"

class Matrix;


class Camera
{
  public:
    // constructors
    Camera( void );

    // const funcs
    /*const Vector& getPosition( void ) const;
    const Vector& getLookAt( void ) const;
    const Vector& getUp( void ) const;*/

    // mutilators
    void setPerspective( double, int, int, double, double );
    void moveRelative( Vector* );
    void setRotation( const Matrix* );
    void setViewParams( /*const Vector*,*/ const Vector* /*, const Vector**/ );

  protected:
    Vector mLookAt;                 // look-at point (eye point)
    Vector mPosition;               // position of the camera (reference point)
    Vector mUp;                     // up vector
    Vector mLookAtBase;
    Vector mUpBase;
    Matrix mRotation;               // rotation matrix

    // mutilators
    void apply( void );             // apply view parameters to OpenGL
};

#endif    /* CAMERA_H */

