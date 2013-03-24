#ifndef PLAYER_H
#define PLAYER_H

#include "Vector.h"
#include "Matrix.h"
#include "Object.h"

class Camera;
class Shape3D;

enum PlayerState
{
  STANDING = 1,
  CROUCHING = 2
};

class Player
{
  public:
    // constructors
    Player();

    // mutilators
    void getRelativeMotion( Vector*, const Vector* );
    void setRotation( const Matrix* );
    void setState( PlayerState );

  protected:
    //Object mObj;
    Vector mPosition;
    Matrix mRotation;
    double mVelocity;
    PlayerState state;

    // statics
    static const double SPEEDS[2];
};


#endif  /* PLAYER_H */

