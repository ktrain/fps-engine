#include "Light.h"


//
// Light
//

Light::Light( const char* n, GLenum light )
: light_num( light )
{
  float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  name = n;

  glEnable( GL_LIGHTING );
  glEnable( light_num );
  glLightfv( light_num, GL_DIFFUSE, diffuse );
}

void Light::draw( const Matrix* pm )
{
  // make a light lol
  position[0] = pm->get( 3, 0 );
  position[1] = pm->get( 3, 1 );
  position[2] = pm->get( 3, 2 );
  glLightfv( light_num, GL_POSITION, position );
}

