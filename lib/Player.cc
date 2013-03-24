#include <stdio.h>

#include "Timing.h"
#include "Player.h"
#include "Camera.h"


const double Player::SPEEDS[2] =
{
  0.5,
  0.25
};


Player::Player()
: mPosition(), mRotation(), mVelocity( SPEEDS[STANDING] ), state( STANDING )
{
}


// Calculate the relative movement vector based on input vector v and
// store it into movement param.
// The position vector is not applied to the player's polygons since
// it's actually the WORLD that moves!!!
void Player::getRelativeMotion( Vector* movement, const Vector* v )
{
  if ( !movement || !v ) return;

  movement->zero();

  static long last_time = 0;
  long this_time = runtime();
  long dt = this_time - last_time;
  if ( !dt )
  {
    // no time has passed ... ?
    return;
  }
  last_time = this_time;

  // orient the vector
  Matrix::Multiply( movement, &mRotation, v );

  // scale the vector according to velocity
  double dPos = mVelocity / dt;
  *movement *= dPos;

  // translate position
  // this is merely so we know the player's real location
  mPosition += *movement;
}


// This is merely so we know which way the player is actually facing.
// The rotation matrix is not applied to the player's polygons since
// it's not the player that rotates, but the WORLD!!!
void Player::setRotation( const Matrix* m )
{
  mRotation = *m;
}

