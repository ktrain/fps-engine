#ifndef OBJECT_H
#define OBJECT_H

struct Vector;
class Shape3D;


class Object
{
  public:
    // constructors
    Object( const char*, Shape3D* );

    // mutilators
    void moveRelative( Vector* );

  protected:
    const char* name;
    Shape3D* mShape;
};

#endif  /* OBJECT_H */

