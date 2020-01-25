#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

using namespace::std;

class Vector3D{

public:
  inline Vector3D(double, double, double);
  inline Vector3D();

  inline friend Vector3D operator*(double, const Vector3D &);
  inline friend Vector3D operator+(const Vector3D &,const Vector3D &);
  inline friend Vector3D operator-(const Vector3D &,const Vector3D &);
  inline Vector3D operator-();
  inline double &operator[](int i);
  inline double  operator[](int i) const;
  inline friend ostream &operator<<(ostream &, const Vector3D &);

  inline Vector3D &operator+=(const Vector3D &);
  inline Vector3D &operator-=(const Vector3D &);

private:
  double x[3];
};

// constructor calls
//        (1) default
Vector3D::Vector3D(){
  x[0] = 0.;
  x[1] = 0.;
  x[2] = 2.;
}

//        (2) with components
Vector3D::Vector3D(double ax0, double ax1, double ax2){
  x[0] = ax0;
  x[1] = ax1;
  x[2] = ax2;
}

// 'vector space' operations:
// multiplication with scalar, sum, difference of vectors, unary -
Vector3D
operator*(double s, const Vector3D &v){
  return Vector3D(s*v.x[0],s*v.x[1], s*v.x[2]);
}


Vector3D
operator+(const Vector3D &a, const Vector3D &b){
  return Vector3D(a.x[0] + b.x[0], a.x[1] + b.x[1], a.x[2] + b.x[2]);
}

Vector3D
operator-(const Vector3D &a, const Vector3D &b){
  return Vector3D(a.x[0] - b.x[0], a.x[1] - b.x[1], a.x[2] - b.x[2]);
}

Vector3D
Vector3D::operator-(){
  return Vector3D(-x[0],-x[1],-x[2]);
}

// access to the components in C fashion
double &
Vector3D::operator[](int i){
  return x[i];
}

double
Vector3D::operator[](int i)const{
  return x[i];
}

// output operator - outputs the components in 'double'
ostream &
operator<<(ostream &o, const Vector3D &a){
  return  o << a.x[0] << " " << a.x[1] << " " << a.x[2];
}

Vector3D &
Vector3D::operator+=(const Vector3D &b){
  (*this)[0] += b[0];
  (*this)[1] += b[1];
  (*this)[2] += b[2];
  return *this;
}

Vector3D &
Vector3D::operator-=(const Vector3D &b){
  (*this)[0] -= b[0];
  (*this)[1] -= b[1];
  (*this)[2] -= b[2];
  return *this;
}

#endif
