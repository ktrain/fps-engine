#include <stdio.h>

#if __APPLE__ && __MACH__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Matrix.h"
#include "Camera.h"



//
// constructors
//

Camera::Camera( void )
: mLookAt( 0.0, 0.0, 1.0 ), mPosition(), mUp( 0.0, 1.0, 0.0 ),
  mLookAtBase( 0.0, 0.0, 1.0 ), mUpBase( 0.0, 1.0, 0.0 )
{
}



//
// const funcs
//

/*const Vector& Camera::getPosition() const
{
  return mPosition;
}


const Vector& Camera::getLookAt() const
{
  return mLookAt;
}


const Vector& Camera::getUp() const
{
  return mUp;
}*/


//
// mutilators
//


void Camera::setPerspective( double fieldOfView, int viewWidth, int viewHeight, double near, double far )
{
  if ( viewHeight <= 0 ) viewHeight = 1;
  double aspectRatio = (double) viewWidth / (double) viewHeight;

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( fieldOfView, aspectRatio, near, far );
}


// Vector v should already be oriented via Player::moveRelative()
void Camera::moveRelative( Vector* v )
{
  if ( !v ) return;

  mPosition += *v;
  mLookAt += *v;

  apply();
}


void Camera::setRotation( const Matrix* m )
{
  if ( !m ) return;

  //if ( mRotation == *m ) return;

  mRotation = *m;

  //(void) printf( "%s, %s, %s\n", mLookAt.toString(), mPosition.toString(), mUp.toString() );

  // rotate look-at vector
  Matrix::Multiply( &mLookAt, m, &mLookAt );

  // rotate up vector
  Matrix::Multiply( &mUp, m, &mUp );

  apply();
}


void Camera::setViewParams( /*const Vector* lookAt,*/ const Vector* pos/*, const Vector* up*/ )
{
  // copy params
  //if ( lookAt ) mLookAt = *lookAt;
  if ( pos ) mPosition = *pos;
  //if ( up ) mUp = *up;

  // apply params
  apply();
}


void Camera::apply()
{
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  gluLookAt(
    mLookAt.x, mLookAt.y, mLookAt.z,
    mPosition.x, mPosition.y, mPosition.z,
    mUp.x, mUp.y, mUp.z
  );
}

