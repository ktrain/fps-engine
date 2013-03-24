#ifndef LIGHT_H
#define LIGHT_H

#if __APPLE__ && __MACH__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Vector.h"
#include "SceneGraph.h"


class Light : protected Node
{
  public:
    Light( const char*, GLenum );

    // const funcs
    void draw( const Matrix* );

  protected:
    GLenum light_num;
    float position[3];
};

#endif  /* LIGHT_H */
