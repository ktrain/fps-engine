#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <stdlib.h>
#include <map>

#include "Matrix.h"

class Vector;



class Node
{
  protected:
    Node( void ) : name( NULL ), numChildren( 0 ) {}
    static const int MAX_CHILDREN = 64;

  protected:
    const char* name;
    int numChildren;
    Node* children[ MAX_CHILDREN ];

  public:
    // constructors
    Node( const Node* );
    //~Node( void );

    // const funcs
    const char* getName( void ) const;
    virtual void draw() const;

    // mutilators
    void add( Node* );
    void remove( Node* );
    void setName( const char* );

    // assignment operators
    Node& operator=( const Node& );
};


class Group : public Node
{
  protected:
    Matrix mTransform;

  public:
    // constructors
    Group( void );
    Group( const char* );
    Group( const Group& );
    ~Group(void);

    // const funcs
    void draw() const;

    // mutilators
    void loadMatrix( const Matrix* );
    void multMatrix( const Matrix* );
    void moveRelative( const Vector* );

    // assignment operators
    Group& operator=( const Group& );
};

// references a geometric object, material
class Shape3D : public Node
{
  //protected:
    //virtual void cull( void ) = \0;

  public:
    Shape3D( void );
    Shape3D( const char* );
};

#endif  /* SCENEGRAPH_H */

