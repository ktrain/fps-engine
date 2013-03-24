#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BasicMath.h"
#include "Vector.h"
#include "Matrix.h"



//
// constructors
//

Matrix::Matrix()
{
  identity();
}

Matrix::Matrix( const double (*elts)[4][4] )
{
  int i, j;

  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      mat[i][j] = (*elts)[i][j];
    }
  }
}

Matrix::Matrix( const double* fp )
{
  
}

Matrix::Matrix( const Matrix& a )
{
  set(a);
}

Matrix::Matrix( const Matrix* a )
{
  set( (const double*) a );
}



//
// const funcs
//

double Matrix::get ( int x, int y ) const
{
  return mat[x][y];
}

double Matrix::getDeterminant() const
{
  double det =
      mat[0][0] * mat[1][1] * mat[2][2] * mat[3][3]
    + mat[0][0] * mat[1][2] * mat[2][3] * mat[3][1]
    + mat[0][0] * mat[1][3] * mat[2][1] * mat[3][2]
  +
      mat[0][1] * mat[1][0] * mat[2][3] * mat[3][2]
    + mat[0][1] * mat[1][2] * mat[2][0] * mat[3][3]
    + mat[0][1] * mat[1][3] * mat[2][2] * mat[3][0]
  +
      mat[0][2] * mat[1][0] * mat[2][1] * mat[3][3]
    + mat[0][2] * mat[1][1] * mat[2][3] * mat[3][0]
    + mat[0][2] * mat[1][3] * mat[2][0] * mat[3][1]
  +
      mat[0][3] * mat[1][0] * mat[2][2] * mat[3][1]
    + mat[0][3] * mat[1][1] * mat[2][0] * mat[3][2]
    + mat[0][3] * mat[1][2] * mat[2][1] * mat[3][0]
  -
      mat[0][0] * mat[1][1] * mat[2][3] * mat[3][2]
    - mat[0][0] * mat[1][2] * mat[2][1] * mat[3][3]
    - mat[0][0] * mat[1][3] * mat[2][2] * mat[3][1]
  -
      mat[0][1] * mat[1][0] * mat[2][2] * mat[3][3]
    - mat[0][1] * mat[1][2] * mat[2][3] * mat[3][0]
    - mat[0][1] * mat[1][3] * mat[2][0] * mat[3][2]
  -
      mat[0][2] * mat[1][0] * mat[2][3] * mat[3][1]
    - mat[0][2] * mat[1][1] * mat[2][0] * mat[3][3]
    - mat[0][2] * mat[1][3] * mat[2][1] * mat[3][0]
  -
      mat[0][3] * mat[1][0] * mat[2][1] * mat[3][2]
    - mat[0][3] * mat[1][1] * mat[2][2] * mat[3][0]
    - mat[0][3] * mat[1][2] * mat[2][0] * mat[3][1];

  return det;
}

char* Matrix::toString() const
{
  char* string = (char*) calloc( MAX_STRING_LEN, sizeof(char) );

  (void) snprintf( string, MAX_STRING_LEN, STRING_TEMPLATE,
                  mat[0][0], mat[0][1], mat[0][2], mat[0][3],
                  mat[1][0], mat[1][1], mat[1][2], mat[1][3],
                  mat[2][0], mat[2][1], mat[2][2], mat[2][3],
                  mat[3][0], mat[3][1], mat[3][2], mat[3][3]
                );

  return string;
}



//
// mutilators
//

void Matrix::set( const double (*elts)[4][4] )
{
  int i, j;

  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      mat[i][j] = (*elts)[i][j];
    }
  }
}

void Matrix::set( const double* elts )
{
  set( (const double (*)[4][4]) elts );
}

void Matrix::set( const Matrix &a )
{
  set( (const double*) a );
}

void Matrix::set( const Matrix *a )
{
  set( (const double*) *a );
}

// turns this matrix into a rotation matrix about the x axis
// rotates theta degrees
void Matrix::rotateX( double theta )
{
  theta = BasicMath::radians( theta );
  double c = cos( theta );
  double s = sin( theta );

  mat[0][0] = 1.0;
  mat[1][0] = 0.0;
  mat[2][0] = 0.0;
  mat[3][0] = 0.0;
  mat[0][1] = 0.0;
  mat[1][1] = c;
  mat[2][1] = -s;
  mat[3][1] = 0.0;
  mat[0][2] = 0.0;
  mat[1][2] = s;
  mat[2][2] = c;
  mat[3][2] = 0.0;
  mat[0][3] = 0.0;
  mat[1][3] = 0.0;
  mat[2][3] = 0.0;
  mat[3][3] = 1.0;
}

// turns this matrix into a rotation matrix about the y axis
// rotates theta degrees
void Matrix::rotateY( double theta )
{
  theta = BasicMath::radians( theta );
  double c = cos( theta);
  double s = sin( theta );

  mat[0][0] = c;
  mat[1][0] = 0.0;
  mat[2][0] = s;
  mat[3][0] = 0.0;
  mat[0][1] = 0.0;
  mat[1][1] = 1.0;
  mat[2][1] = 0.0;
  mat[3][1] = 0.0;
  mat[0][2] = -s;
  mat[1][2] = 0.0;
  mat[2][2] = c;
  mat[3][2] = 0.0;
  mat[0][3] = 0.0;
  mat[1][3] = 0.0;
  mat[2][3] = 0.0;
  mat[3][3] = 1.0;
}

// turns this matrix into a rotation matrix about the z axis
// rotates theta degrees
void Matrix::rotateZ( double theta )
{
  theta = BasicMath::radians( theta );
  double c = cos( theta );
  double s = sin( theta );

  mat[0][0] = c;
  mat[1][0] = -s;
  mat[2][0] = 0.0;
  mat[3][0] = 0.0;
  mat[0][1] = s;
  mat[1][1] = c;
  mat[2][1] = 0.0;
  mat[3][1] = 0.0;
  mat[0][2] = 0.0;
  mat[1][2] = 0.0;
  mat[2][2] = 1.0;
  mat[3][2] = 0.0;
  mat[0][3] = 0.0;
  mat[1][3] = 0.0;
  mat[2][3] = 0.0;
  mat[3][3] = 1.0;
}

void Matrix::rotate( double theta, const Vector* axis )
{
  double x = axis->x;
  double y = axis->y;
  double z = axis->z;
  double x2 = x * x;
  double y2 = y * y;
  double z2 = z * z;
  double s = sin( theta );
  double c = cos( theta );

  mat[0][0] = x2 + (c * (1 - x2));
  mat[1][0] = (x * y * (1 - c)) - (z * s);
  mat[2][0] = (x * z * (1 - c)) + (y * s);
  mat[3][0] = 0.0;
  mat[0][1] = (x * y * (1 - c)) + (z * s);
  mat[1][1] = y2 + (c * (1 - y2));
  mat[2][1] = (y * z * (1 - c)) - (x * s);
  mat[3][1] = 0.0;
  mat[0][2] = (x * z * (1 - c)) - (y * s);
  mat[1][2] = (y * z * (1 - c)) + (x * s);
  mat[2][2] = z2 + (c * (1 - z2));
  mat[3][2] = 0.0;
  mat[0][3] = 0.0;
  mat[1][3] = 0.0;
  mat[2][3] = 0.0;
  mat[3][3] = 1.0;
}

void Matrix::scale( double s )
{
  int i, j;
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      mat[i][j] *= s;
    }
  }
}

void Matrix::makeScale( double xScalar, double yScalar, double zScalar )
{
  mat[0][0] = xScalar;
  mat[0][1] = 0.0;
  mat[0][2] = 0.0;
  mat[0][3] = 0.0;
  mat[1][0] = 0.0;
  mat[1][1] = yScalar;
  mat[1][2] = 0.0;
  mat[1][3] = 0.0;
  mat[2][0] = 0.0;
  mat[2][1] = 0.0;
  mat[2][2] = zScalar;
  mat[2][3] = 0.0;
  mat[3][0] = 0.0;
  mat[3][1] = 0.0;
  mat[3][2] = 0.0;
  mat[3][3] = 1.0;
}

void Matrix::translate( double xTrans, double yTrans, double zTrans )
{
  mat[3][0] += xTrans;
  mat[3][1] += yTrans;
  mat[3][2] += zTrans;
}

void Matrix::makeTranslate( double xTrans, double yTrans, double zTrans )
{
  mat[0][0] = 1.0;
  mat[0][1] = 0.0;
  mat[0][2] = 0.0;
  mat[0][3] = 0.0;
  mat[1][0] = 0.0;
  mat[1][1] = 1.0;
  mat[1][2] = 0.0;
  mat[1][3] = 0.0;
  mat[2][0] = 0.0;
  mat[2][1] = 0.0;
  mat[2][2] = 1.0;
  mat[2][3] = 0.0;
  mat[3][0] = xTrans;
  mat[3][1] = yTrans;
  mat[3][2] = zTrans;
  mat[3][3] = 1.0;
}

void Matrix::identity()
{
  mat[0][0] = 1.0;
  mat[0][1] = 0.0;
  mat[0][2] = 0.0;
  mat[0][3] = 0.0;
  mat[1][0] = 0.0;
  mat[1][1] = 1.0;
  mat[1][2] = 0.0;
  mat[1][3] = 0.0;
  mat[2][0] = 0.0;
  mat[2][1] = 0.0;
  mat[2][2] = 1.0;
  mat[2][3] = 0.0;
  mat[3][0] = 0.0;
  mat[3][1] = 0.0;
  mat[3][2] = 0.0;
  mat[3][3] = 1.0;
}



//
// casts
//

Matrix::operator double*()
{
  return ( (double*) mat );
}

Matrix::operator const double*() const
{
  return ( (const double*) mat );
}



//
// unary operators
//

Matrix& Matrix::operator +() const
{
  return *( new Matrix( this ) );
}

Matrix& Matrix::operator -() const
{
  Matrix* mresult = new Matrix( this );
  mresult->scale( -1.0 );
  return *mresult;
}



//
// binary operators
//

bool Matrix::operator ==( const Matrix& other ) const
{
  int i, j;

  for ( i = 0; i < 4; i++ )
  {
    for ( j = 0; j < 4; j++ )
    {
      if ( mat[i][j] != other.mat[i][j] )
      {
        return false;
      }
    }
  }

  return true;
}



//
// statics
//

Vector* Matrix::Multiply( Vector* vdest, const Matrix* m, const Vector* v )
{
  if ( !vdest || !m || !v ) return NULL;

  int i, j, k, l;
  double next;
  double result[4];
  double* vf = (double*) v;

  for ( l = 0, j = 0; l < 4; l++, j++ )
  {
    result[l] = 0.0;   // zero it out
    for ( k = 0, i = 0; k < 4; k++, i++ )
    {
      next = m->mat[i][j] * vf[k];
      result[l] += next;
    }
  }

  // homogenize the 4D result
  vdest->x = result[0] / result[3];
  vdest->y = result[1] / result[3];
  vdest->z = result[2] / result[3];

  return vdest;
}

Matrix* Matrix::Multiply( Matrix* mdest, const Matrix* m1, const Matrix* m2 )
{
  if ( !mdest || !m1 || !m2 ) return NULL;

  int i, j, k, l, m, n;
  double next;
  // must work on a separate array
  double result[4][4];

  for (n = 0, j = 0; n < 4; n++, j++)
  {
    for (m = 0, k = 0; m < 4; m++, k++)
    {
      result[m][n] = 0.0;                           // clean it out LOLOLOLOL
      for (i = 0, l = 0; i < 4; i++, l++)
      {
        next = m1->get( i, j ) * m2->get( k, l );
        result[m][n] += next;
      }
    }
  }

  // copy the results into the dest matrix
  (void) memcpy( (void*) mdest, (void*) result, sizeof(result) );

  return mdest;
}

// ridiculous
Matrix* Matrix::Invert( Matrix* mdest, const Matrix* src )
{
  double result[4][4];
  double det = src->getDeterminant();

  result[0][0] =
      src->mat[1][1] * src->mat[2][2] * src->mat[3][3]
    + src->mat[1][2] * src->mat[2][3] * src->mat[3][1]
    + src->mat[1][3] * src->mat[2][1] * src->mat[3][2] 
  -
      src->mat[1][1] * src->mat[2][3] * src->mat[3][2]
    - src->mat[1][2] * src->mat[2][1] * src->mat[3][3]
    - src->mat[1][3] * src->mat[2][2] * src->mat[3][1];
  result[0][1] = 
      src->mat[0][1] * src->mat[2][3] * src->mat[3][2]
    + src->mat[0][2] * src->mat[2][1] * src->mat[3][3]
    + src->mat[0][3] * src->mat[2][2] * src->mat[3][1] 
  -
      src->mat[0][1] * src->mat[2][2] * src->mat[3][3]
    - src->mat[0][2] * src->mat[2][3] * src->mat[3][1]
    - src->mat[0][3] * src->mat[2][1] * src->mat[3][2];
  result[0][2] = 
      src->mat[0][1] * src->mat[1][2] * src->mat[3][3]
    + src->mat[0][2] * src->mat[1][3] * src->mat[3][1]
    + src->mat[0][3] * src->mat[1][1] * src->mat[3][2] 
  -
      src->mat[0][1] * src->mat[1][3] * src->mat[3][2]
    - src->mat[0][2] * src->mat[1][1] * src->mat[3][3]
    - src->mat[0][3] * src->mat[1][2] * src->mat[3][1];
  result[0][3] = 
      src->mat[0][1] * src->mat[1][3] * src->mat[2][2]
    + src->mat[0][2] * src->mat[1][1] * src->mat[2][3]
    + src->mat[0][3] * src->mat[1][2] * src->mat[2][1] 
  -
      src->mat[0][1] * src->mat[1][2] * src->mat[2][3]
    - src->mat[0][2] * src->mat[1][3] * src->mat[2][1]
    - src->mat[0][3] * src->mat[1][1] * src->mat[2][2];
  result[1][0] = 
      src->mat[1][0] * src->mat[2][3] * src->mat[3][2]
    + src->mat[1][2] * src->mat[2][0] * src->mat[3][3]
    + src->mat[1][3] * src->mat[2][2] * src->mat[3][0] 
  -
      src->mat[1][0] * src->mat[2][2] * src->mat[3][3]
    - src->mat[1][2] * src->mat[2][3] * src->mat[3][0]
    - src->mat[1][3] * src->mat[2][0] * src->mat[3][2];
  result[1][1] = 
      src->mat[0][0] * src->mat[2][2] * src->mat[3][3]
    + src->mat[0][2] * src->mat[2][3] * src->mat[3][0]
    + src->mat[0][3] * src->mat[2][1] * src->mat[3][2] 
  -
      src->mat[0][0] * src->mat[2][3] * src->mat[3][2]
    - src->mat[0][2] * src->mat[2][0] * src->mat[3][3]
    - src->mat[0][3] * src->mat[2][2] * src->mat[3][0];
  result[1][2] = 
      src->mat[0][0] * src->mat[1][3] * src->mat[3][2]
    + src->mat[0][2] * src->mat[1][0] * src->mat[3][3]
    + src->mat[0][3] * src->mat[1][2] * src->mat[3][0] 
  -
      src->mat[0][0] * src->mat[1][2] * src->mat[3][3]
    - src->mat[0][2] * src->mat[1][3] * src->mat[3][0]
    - src->mat[0][3] * src->mat[1][0] * src->mat[3][2];
  result[1][3] = 
      src->mat[0][0] * src->mat[1][2] * src->mat[2][3]
    + src->mat[0][2] * src->mat[1][3] * src->mat[2][0]
    + src->mat[0][3] * src->mat[1][0] * src->mat[2][2] 
  -
      src->mat[0][0] * src->mat[1][3] * src->mat[2][2]
    - src->mat[0][2] * src->mat[1][0] * src->mat[2][3]
    - src->mat[0][3] * src->mat[1][2] * src->mat[2][0];
  result[2][0] = 
      src->mat[1][0] * src->mat[2][1] * src->mat[3][3]
    + src->mat[1][1] * src->mat[2][3] * src->mat[3][0]
    + src->mat[1][3] * src->mat[2][1] * src->mat[3][1] 
  -
      src->mat[1][0] * src->mat[2][3] * src->mat[3][1]
    - src->mat[1][1] * src->mat[2][0] * src->mat[3][3]
    - src->mat[1][3] * src->mat[2][1] * src->mat[3][0];
  result[2][1] = 
      src->mat[0][0] * src->mat[2][3] * src->mat[3][1]
    + src->mat[0][1] * src->mat[2][0] * src->mat[3][3]
    + src->mat[0][3] * src->mat[2][1] * src->mat[3][0] 
  -
      src->mat[0][0] * src->mat[2][1] * src->mat[3][3]
    - src->mat[0][1] * src->mat[2][3] * src->mat[3][0]
    - src->mat[0][3] * src->mat[2][0] * src->mat[3][1];
  result[2][2] = 
      src->mat[0][0] * src->mat[1][1] * src->mat[3][3]
    + src->mat[0][1] * src->mat[1][3] * src->mat[3][0]
    + src->mat[0][3] * src->mat[1][0] * src->mat[3][1] 
  -
      src->mat[0][0] * src->mat[1][3] * src->mat[3][1]
    - src->mat[0][1] * src->mat[1][0] * src->mat[3][3]
    - src->mat[0][3] * src->mat[1][1] * src->mat[3][0];
  result[2][3] = 
      src->mat[0][0] * src->mat[1][3] * src->mat[2][1]
    + src->mat[0][1] * src->mat[1][0] * src->mat[2][3]
    + src->mat[0][3] * src->mat[1][1] * src->mat[2][0] 
  -
      src->mat[0][0] * src->mat[1][1] * src->mat[2][3]
    - src->mat[0][1] * src->mat[1][3] * src->mat[2][0]
    - src->mat[0][3] * src->mat[1][0] * src->mat[2][1];
  result[3][0] = 
      src->mat[1][0] * src->mat[2][2] * src->mat[3][1]
    + src->mat[1][1] * src->mat[2][0] * src->mat[3][2]
    + src->mat[1][2] * src->mat[2][1] * src->mat[3][0] 
  -
      src->mat[1][0] * src->mat[2][1] * src->mat[3][2]
    - src->mat[1][1] * src->mat[2][2] * src->mat[3][0]
    - src->mat[1][2] * src->mat[2][0] * src->mat[3][1];
  result[3][1] = 
      src->mat[0][0] * src->mat[2][1] * src->mat[3][2]
    + src->mat[0][1] * src->mat[2][2] * src->mat[3][0]
    + src->mat[0][2] * src->mat[2][0] * src->mat[3][1] 
  -
      src->mat[0][0] * src->mat[2][2] * src->mat[3][1]
    - src->mat[0][1] * src->mat[2][0] * src->mat[3][2]
    - src->mat[0][2] * src->mat[2][1] * src->mat[3][0];
  result[3][2] = 
      src->mat[0][0] * src->mat[1][2] * src->mat[3][1]
    + src->mat[0][1] * src->mat[1][0] * src->mat[3][2]
    + src->mat[0][2] * src->mat[1][1] * src->mat[3][0] 
  -
      src->mat[0][0] * src->mat[1][1] * src->mat[3][2]
    - src->mat[0][1] * src->mat[1][2] * src->mat[3][0]
    - src->mat[0][2] * src->mat[1][0] * src->mat[3][1];
  result[3][3] = 
      src->mat[0][0] * src->mat[1][1] * src->mat[2][2]
    + src->mat[0][1] * src->mat[1][2] * src->mat[2][0]
    + src->mat[0][2] * src->mat[1][0] * src->mat[2][1] 
  -
      src->mat[0][0] * src->mat[1][2] * src->mat[2][1]
    - src->mat[0][1] * src->mat[1][0] * src->mat[2][2]
    - src->mat[0][2] * src->mat[1][1] * src->mat[2][0];

  mdest->set( &result );
  mdest->scale( 1.0 / det );
  (void) Multiply( mdest, src, mdest );

  return mdest;
}


const Matrix Matrix::IDENTITY( &IDENTITY_ARR );


const char* Matrix::STRING_TEMPLATE =
"[ %f, %f, %f, %f\n"
"  %f, %f, %f, %f\n"
"  %f, %f, %f, %f\n"
"  %f, %f, %f, %f ]";

const double Matrix::IDENTITY_ARR[4][4] =
{
  { 1, 0, 0, 0 },
  { 0, 1, 0, 0 },
  { 0, 0, 1, 0 },
  { 0, 0, 0, 1 }
};

