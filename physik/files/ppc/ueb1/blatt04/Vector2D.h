#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

using namespace::std;

class Vector2D{

public:
  inline Vector2D(double x1, double x2);
  inline Vector2D();

  inline friend Vector2D operator*(double, const Vector2D &);
  inline friend Vector2D operator+(const Vector2D &,const Vector2D &);
  inline friend Vector2D operator-(const Vector2D &,const Vector2D &);
  inline Vector2D operator-();
  inline double &operator[](int i);
  inline double  operator[](int i) const;
  inline friend ostream &operator<<(ostream &, const Vector2D &);

  inline Vector2D &operator+=(const Vector2D &);
  inline Vector2D &operator-=(const Vector2D &);

private:
  double x[2];
};

// constructor calls
//        (1) default
Vector2D::Vector2D(){
  x[0] = x[1] = 0.;
}

//        (2) with components
Vector2D::Vector2D(double ax0, double ax1){
  x[0] = ax0;
  x[1] = ax1;
}

// 'vector space' operations:
// multiplication with scalar, sum, difference of vectors, unary -
Vector2D
operator*(double s, const Vector2D &v){
  return Vector2D(s*v.x[0],s*v.x[1]);
}


Vector2D
operator+(const Vector2D &a, const Vector2D &b){
  return Vector2D(a.x[0] + b.x[0], a.x[1] + b.x[1]);
}

Vector2D
operator-(const Vector2D &a, const Vector2D &b){
  return Vector2D(a.x[0] - b.x[0], a.x[1] - b.x[1]);
}

Vector2D
Vector2D::operator-(){
  return Vector2D(-x[0],-x[1]);
}

// access to the components in C fashion
double &
Vector2D::operator[](int i){
  return x[i];
}

double
Vector2D::operator[](int i)const{
  return x[i];
}

// output operator - outputs the components in 'double'
ostream &
operator<<(ostream &o, const Vector2D &a){
  return  o << a.x[0] << " " << a.x[1];
}

Vector2D &
Vector2D::operator+=(const Vector2D &b){
  (*this)[0] += b[0];
  (*this)[1] += b[1];
  return *this;
}

Vector2D &
Vector2D::operator-=(const Vector2D &b){
  (*this)[0] -= b[0];
  (*this)[1] -= b[1];
  return *this;
}

#endif
