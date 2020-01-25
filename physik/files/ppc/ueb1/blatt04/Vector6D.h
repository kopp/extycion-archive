#ifndef VECTORND_H
#define VECTORND_H 6 //DIMENSIOn

#include <iostream>

/*****
 * die dimension anpassen und dito anzahl der argumente der Constructoren
 * und den Namen und die groesse von x[]
 *                                                         *******************/

using namespace::std;

class Vector6D{

public:
  inline Vector6D(double, double, double, double, double ,double);
  inline Vector6D();

  inline friend Vector6D operator*(double, const Vector6D &);
  inline friend Vector6D operator+(const Vector6D &,const Vector6D &);
  inline friend Vector6D operator-(const Vector6D &,const Vector6D &);
  inline Vector6D operator-();
  inline double &operator[](int i);
  inline double  operator[](int i) const;
  //inline friend ostream &operator<<(ostream &, const Vector6D &);

  inline Vector6D &operator+=(const Vector6D &);
  inline Vector6D &operator-=(const Vector6D &);

private:
  double x[6];
};

// constructor calls
//        (1) default
Vector6D::Vector6D(){
	for( int i = 0; i < VECTORND_H; i ++)
		x[i] = 0.;
}

//        (2) with components
Vector6D::Vector6D(double ax0, double ax1, double ax2, double ax3, double ax4, double ax5){
  x[0] = ax0;
  x[1] = ax1;
  x[2] = ax2;
  x[3] = ax3;
  x[4] = ax4;
  x[5] = ax5;
}

// 'vector space' operations:
// multiplication with scalar, sum, difference of vectors, unary -
Vector6D
operator*(double s, const Vector6D &v){
  //return Vector6D(s*v.x[0],s*v.x[1], s*v.x[2]);
  Vector6D foo;
  for( int i = 0; i < VECTORND_H; i ++ )
	  foo.x[i] = s*v.x[i];
  return foo;
}


Vector6D
operator+(const Vector6D &a, const Vector6D &b){
  //return Vector6D(a.x[0] + b.x[0], a.x[1] + b.x[1], a.x[2] + b.x[2]);
  Vector6D foo;
  for( int i = 0; i < VECTORND_H; i++)
	  foo.x[i] = a.x[i] + b.x[i];
  return foo;
}

Vector6D
operator-(const Vector6D &a, const Vector6D &b){
  //return Vector6D(a.x[0] - b.x[0], a.x[1] - b.x[1], a.x[2] - b.x[2]);
  Vector6D foo;
  for( int i = 0; i < VECTORND_H; i++)
	  foo.x[i] = a.x[i] - b.x[i];
  return foo;
}

Vector6D
Vector6D::operator-(){
  //return Vector6D(-x[0],-x[1],-x[2]);
  Vector6D foo;
  for( int i = 0; i < VECTORND_H; i++)
	  foo.x[i] = -x[i];
  return foo;
}

// access to the components in C fashion
double &
Vector6D::operator[](int i){
  return x[i];
}

double
Vector6D::operator[](int i)const{
  return x[i];
}

// output operator - outputs the components in 'double'
// to be implemented ... 
/*
ostream &
operator<<(ostream &o, const Vector6D &a){
  //return  o << a.x[0] << " " << a.x[1] << " " << a.x[2];
  for( int i = 0; i < VECTORND_H; i++ )
	  o << "  " << a.x[i];
  return 0;
}
*/

Vector6D &
Vector6D::operator+=(const Vector6D &b){
  /*
  (*this)[0] += b[0];
  (*this)[1] += b[1];
  (*this)[2] += b[2];
  */
  for( int i = 0; i < VECTORND_H; i ++ )
	(*this)[i] += b.x[i];
  return *this;
}

Vector6D &
Vector6D::operator-=(const Vector6D &b){
  /*
  (*this)[0] -= b[0];
  (*this)[1] -= b[1];
  (*this)[2] -= b[2];
  */
  for( int i = 0; i < VECTORND_H; i ++ )
	(*this)[i] -= b.x[i];
  return *this;
}

#endif
