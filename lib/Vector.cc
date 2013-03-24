#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Vector.h"


//
// constructors
//

Vector::Vector()
: x( 0.0 ), y( 0.0 ), z( 0.0 ), w( 1.0 )
{
}

Vector::Vector( double x0, double y0, double z0 )
: x( x0 ), y( y0 ), z( z0 ), w( 1.0 )
{
}

Vector::Vector( const Vector& parent )
: x( parent.x ), y( parent.y ), z( parent.z ), w( 1.0 )
{
}

Vector::Vector( const Vector* parent )
: x( parent->x ), y( parent->y ), z( parent->z ), w( 1.0 )
{
}



//
// const functions
//

double Vector::getMagnitude() const
{
  return sqrt( (x * x) + (y * y) + (z * z) );
}

// this method is for weeding out zeroes and crazy nans.
bool Vector::isNonZero() const
{
  double mag = getMagnitude();
  return ( mag && isfinite( mag ) );
}

char* Vector::toString() const
{
  char* string = NULL;

  // this should be faster
  string = (char*) calloc( MAX_STRING_LEN, sizeof(char) );
  (void) snprintf( string, MAX_STRING_LEN, STRING_TEMPLATE, x, y, z );

  return string;
}



//
// mutilators
//

void Vector::zero()
{
  x = 0.0;
  y = 0.0;
  z = 0.0;
}

void Vector::set( const Vector* other )
{
  x = other->x;
  y = other->y;
  z = other->z;
}

void Vector::normalize()
{
  double magnitude = getMagnitude();

  if ( !magnitude ) return;

  double scalar = 1.0 / magnitude;
  x *= scalar;
  y *= scalar;
  z *= scalar;
}



//
// casts
//

Vector::operator double*()
{
  return &x;
}

Vector::operator const double*() const
{
  return &x;
}



//
// unary operators
//

Vector& Vector::operator +() const
{
  return *( new Vector( this ) );
}

Vector& Vector::operator -() const
{
  Vector* result = new Vector( this );
  result->x = -x;
  result->y = -y;
  result->z = -z;
  return *result;
}



//
// binary operators
//

Vector Vector::operator +( const Vector &a ) const
{
  Vector* result = new Vector( this );
  *result += a;
  return *result;
}

Vector Vector::operator -( const Vector &a ) const
{
  Vector* result = new Vector( this );
  *result -= a;
  return *result;
}

Vector Vector::operator *( double scalar ) const
{
  Vector* result = new Vector( this );
  *result *= scalar;
  return *result;
}

Vector Vector::operator /( double scalar ) const
{
  Vector* result = new Vector( this );
  *result /= scalar;
  return *result;
}



//
// assignment operators
//

Vector& Vector::operator =( const Vector &a )
{
  x = a.x;
  y = a.y;
  z = a.z;

  return *this;
}

Vector& Vector::operator +=( const Vector &a )
{
  x += a.x;
  y += a.y;
  z += a.z;

  return *this;
}

Vector& Vector::operator -=( const Vector &a )
{
  x -= a.x;
  y -= a.y;
  z -= a.z;

  return *this;
}

Vector& Vector::operator *=( double factor )
{
  x *= factor;
  y *= factor;
  z *= factor;

  return *this;
}

Vector& Vector::operator /=( double factor )
{
  x /= factor;
  y /= factor;
  z /= factor;

  return *this;
}



//
// statics
//

const char* Vector::STRING_TEMPLATE = "[%f, %f, %f]";

double Vector::Dot( const Vector* a, const Vector* b )
{
  return ( (a->x * b->x) + (a->y * b->y) + (a->z * b->z) );
}

Vector* Vector::Cross( Vector* out, const Vector* a, const Vector* b )
{
  out->x = ( a->y * b->z ) - ( a->z * b->y );
  out->y = ( a->z * b->x ) - ( a->x * b->z );
  out->z = ( a->x * b->y ) - ( a->y * b->x );

  return out;
}

