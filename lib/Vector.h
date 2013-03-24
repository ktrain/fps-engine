#ifndef VECTOR_H
#define VECTOR_H

// 3D Vector struct
struct Vector
{
  public:
    // the w is there just so Vectors can be
    // cast to double pointers and passed to OpenGL
    double x, y, z, w;

    // constructors
    Vector( void );
    Vector( double, double, double );
    Vector( const Vector& );
    Vector( const Vector* );

    // const functions
    double getMagnitude( void ) const;
    bool isNonZero( void ) const;
    char* toString( void ) const;

    // mutilators
    void zero( void );
    void set( const Vector* );
    void normalize( void );

    // casts
    operator double*();
    operator const double*() const;

    // unary operators
    Vector& operator +() const;
    Vector& operator -() const;

    // binary operators
    Vector operator +( const Vector& ) const;
    Vector operator -( const Vector& ) const;
    Vector operator *( double ) const;
    Vector operator /( double ) const;

    // assignment operators
    Vector& operator =( const Vector& );
    Vector& operator +=( const Vector& );
    Vector& operator -=( const Vector& );
    Vector& operator *=( double );
    Vector& operator /=( double );

    // statics
    static double Dot( const Vector*, const Vector* );
    static Vector* Cross( Vector*, const Vector*, const Vector* );

  private:
    // statics
    const static char* STRING_TEMPLATE;
    const static int MAX_STRING_LEN = 128;
};

#endif  /* VECTOR_H */

