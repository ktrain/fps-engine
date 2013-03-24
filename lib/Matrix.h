#ifndef MATRIX_H
#define MATRIX_H

struct Vector;

struct Matrix
{
  public:
    double mat[4][4];

    // constructors
    Matrix( void );
    Matrix( const double (*)[4][4] );
    Matrix( const double* );
    Matrix( const Matrix& );
    Matrix( const Matrix* );

    // const funcs
    double get( int, int ) const;
    double getDeterminant( void ) const;
    char* toString( void ) const;

    // mutilators
    void set( const double (*)[4][4] );
    void set( const double* );
    void set( const Matrix& );
    void set( const Matrix* );
    void rotateX( double );
    void rotateY( double );
    void rotateZ( double );
    void rotate( double, const Vector* );
    void scale( double );
    void makeScale( double, double, double );
    void translate( double, double, double );
    void makeTranslate( double, double, double );
    void identity( void );

    // casts
    operator double*();
    operator const double*() const;

    // unary operators
    Matrix& operator +() const;
    Matrix& operator -() const;

    // binary operators
    bool operator ==( const Matrix& ) const;

    // statics
    static Vector* Multiply( Vector*, const Matrix*, const Vector* );
    static Matrix* Multiply( Matrix*, const Matrix*, const Matrix* );
    static Matrix* Invert( Matrix*, const Matrix* );

    static const Matrix IDENTITY;


  private:
    // statics
    const static char* STRING_TEMPLATE;
    const static int MAX_STRING_LEN = 256;
    const static double IDENTITY_ARR[4][4];
};

#endif  /* MATRIX_H */

