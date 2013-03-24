#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#if __APPLE__ && __MACH__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Vector.h"
#include "SceneGraph.h"



//
// Node
//

//
// constructors
//

Node::Node( const Node* parent )
: name( parent->name ), numChildren( parent->numChildren )
{
  int i;

  for ( i = 0; i < MAX_CHILDREN; i++ )
  {
    children[i] = parent->children[i];
  }
}

/*Node::~Node( void )
{
  int i;
  if ( name ) delete name;
  for ( i = 0; i < MAX_CHILDREN; i++ )
  {
    if ( children[i] )
    {
      delete children[i];
    } else {
      break;
    }
  }
}*/



//
// const funcs
//

const char* Node::getName() const
{
  return name;
}

void Node::setName(const char *n)
{
  name = n;
}

void Node::draw( void ) const
{
  int i;
  (void) printf( "Node's draw, wtf?\n" );

  for ( i = 0; i < numChildren; i++ )
  {
    glPushMatrix();
    children[i]->draw();
    glPopMatrix();
  }
}



//
// mutilators
//

void Node::add( Node* n )
{
  if ( numChildren < MAX_CHILDREN )
  {
    children[numChildren++] = n;
    //printf("%s added child %s (%d)\n", name, n->getName(), numChildren);
  }
  else
  {
    (void) fprintf(stderr, "%s has %d children! cannot add %s\n",
        name, MAX_CHILDREN, n->getName());
  }
  //printf("%s has %d children\n", name, numChildren);
}

// remove a child node
void Node::remove( Node* n )
{
  int i;

  for (i = 0; i < numChildren; i++)
  {
    if (children[i] == n)
    {
      delete children[i];
      while (i < numChildren)
      {
        children[i] = children[i + 1];
        i++;
      }
      children[i] = NULL;
      numChildren--;
      break;
    }
  }
}



//
// assignment operators
//

Node& Node::operator=( const Node& parent )
{
  int i;

  numChildren = parent.numChildren;
  name = parent.name;

  for ( i = 0; i < numChildren; i++ )
  {
    children[i] = parent.children[i];
  }

  return *this;
}





//
// Group
//

// constructors

Group::Group( void )
: mTransform()
{
  //name = "World";
}

Group::Group( const char *n )
: mTransform()
{
  name = n;
}

Group::~Group()
{
}



//
// const funcs
//

void Group::draw( void ) const
{
  int i;

  //(void) fprintf( stderr, "Group %s: drawing %d children\n", name, numChildren );

  glPushMatrix();
  glMultMatrixd( (double*) &mTransform );

  for ( i = 0; i < numChildren; i++ )
  {
    children[i]->draw();
  }

  glPopMatrix();
}



//
// mutilators
//

void Group::loadMatrix( const Matrix* m )
{
  mTransform.set( m );
}

void Group::multMatrix( const Matrix* m )
{
  Matrix::Multiply( &mTransform, &mTransform, m );
}

void Group::moveRelative( const Vector* v )
{
  mTransform.translate( v->x, v->y, v->z );
}



//
// Shape3D
//

Shape3D::Shape3D( void )
{
}

Shape3D::Shape3D(const char *n)
{
  name = n;
}

