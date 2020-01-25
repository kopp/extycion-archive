//BEGIN
/*---------------------------------------------------------------------------
  $Id: PTSRandom.h,v 1.7 1998/11/26 17:28:44 sts Exp $

  contains several random number generators

  UNIFORM DISTRIBUTIONS

  1. PTS_MarsagliaRNG - Marsaglia's random number generator
       is tuned to deliver floating point numbers (double's with
       about 8 significant digits) with very long periods and
       completely architecture independent. A test routine for
       the generator is provided (.test()).
       Int, Unsigned are implemented by multiplying the generic
       float randoms by 4096*4096 - reflecting their granularity.

  2. PTS_KPS250RNG  - the Kirkpatrick Stoll XOR Generator 250/103
       is tuned towards speed (for int and unsigned) and long sequences.
       its 'generic' type are unsigned ints where the entire available range
       is covered uniformly. positive ints and doubles are formed by
       masking the first bit, respectively dividing by the largest
       unsigned.

  3. PTS_Cong1RNG - a simple PORTABLE congruential random number
       generator THAT SHOULD NOT be used in serious computations
       when long series of random numbers (more than several 100000) are
       needed.

  USAGE:

  PTS_KPS250RNG   rng;    // seed is current time in seconds since Jan 1970
  PTS_KPS250RNG   rng(1); // produce always the same sequence, depending on
                          //  on seed value, here 1
  PTS_KPS250RNG   rng(1,3); // two seeds are possible, distinct sequences
                          // for all integer pairs from 0 .. about 30000

  same intialization for
  PTS_MarsagliaRNG rng, rng(1), rng(1,3);

  PTS_Cong1RNG    rng, rng(1);  // the two seed form is not available

  //    cf.
  //
  //    - S. Kirkpatrick, E. Stoll, J. Comput. Phys. 40, 517(1981).
  //    - A.M. Ferrenberg, D.P. Landau, Y.J. Wong, PRL 69, 3382(1992)
  //            for problems when this generator is combined with the
  // 	        Wolff cluster-flipping MC method, but dependend on the
  //            seeding.
  //    - G. Marsaglia, B. Narasimhan, A. Zaman,
  //            Comput. Phys. Commun. 60, 345(1990)
  //       original reference for a subtract with carry generator which
  // 	   also seems to have good statistical properties (as alternative).
  //    - Ziff, cond-mat/9710104 four tap shift register...

  ------------------------------------------------------------------------*/
//END

#ifndef PTS_RANDOM_H
#define PTS_RANDOM_H

#include <sys/types.h>
#include <time.h>
#include <limits.h>
#include <cstdlib>
#include <iostream>

using namespace std;

/* ------------------- base class */

/** base (interfaced) class for random number generators and ddistributions
 */
class PTS_RNG {
public:
  /** user interface */

  /** functions returning random numbers of the respective types */
  virtual double   Double() = 0;      // double valued rn. in [0..double_max]
  virtual int      Int(){ return (int) (Double() * int_max); }
  virtual unsigned Unsigned()
                  { return (unsigned) (Double() * unsigned_max); } // unsigned

  /** max data range of random numbers */
  virtual int IntMax()          { return int_max; }
  virtual unsigned UnsignedMax(){ return unsigned_max; }
  virtual double DoubleMax()    { return double_max; }

  virtual int IntMin()          { return 0; }
  virtual unsigned UnsignedMin(){ return 0u; }
  virtual double DoubleMin()    { return 0.; }

  /** tests current generator to some extent, returns > 0 on success */
  virtual int      test();

protected:
  /** the constants shall only be changed by derived generators who can
      then make their ctors public
    */
  PTS_RNG( int i_max=INT_MAX, unsigned u_max=UINT_MAX, double d_max=1.) :
    int_max(i_max), unsigned_max(u_max), double_max(d_max) {}

  /** random numbers will distributed between 0 and ..max */
  int      int_max;
  unsigned unsigned_max;
  double   double_max;

  // test sections
  int     uniformity();
};


/*************************************************************************/

/** a very simple congruential random number generator
 *  Ref: numerical recipes in c, page 209, 211         */
class PTS_Cong1RNG: public PTS_RNG {

public:
  PTS_Cong1RNG( int aseed=-1 ) :
    im(243000), ia(4561), ic(51349)
  {
    int_max      = im-1;
    unsigned_max = im-1;

    if ( aseed > 0 )
      is = (aseed + ic) % im;
    else
      is = (time(0) + ic) % im;
  }

  int      Int();
  double   Double();
  unsigned Unsigned();

private:
  const int im /* = 243000 */;
  const int ia /* = 4561 */;
  const int ic /* = 51349 */;
  int       is;

  int       seed;
};


inline int PTS_Cong1RNG::Int()
{
  return is = (is * ia + ic) % im;
}

inline unsigned PTS_Cong1RNG::Unsigned()
{
  return (unsigned)( is = (is * ia + ic) % im );
}

inline double PTS_Cong1RNG::Double()
{
  return (is = (is * ia + ic) % im) / (double) int_max;
}



/**********************************************************************/

/** the 'great Marsaglia generator': portable and rather long sequence */
class PTS_MarsagliaRNG: public PTS_RNG
{
  /*--------------------------------------------------------------------
  ranmar.c

  C Version of Marsaglias ranmar

C This random number generator originally appeared in "Toward a Universal
C Random Number Generator" by George Marsaglia and Arif Zaman.
C Florida State University Report: FSU-SCRI-87-50 (1987)
C
C It was later modified by F. James and published in "A Review of Pseudo-
C random Number Generators"
C
C THIS IS THE BEST KNOWN RANDOM NUMBER GENERATOR AVAILABLE.
C       (However, a newly discovered technique can yield
C         a period of 10~600. But that is still in the development stage.)
C
C It passes ALL of the tests for random number generators and has a period
C   of 2~144, is completely portable (gives bit identical results on all
C   machines with at least 24-bit mantissas in the floating point
C   representation).
C
C The algorithm is a combination of a Fibonacci sequence (with lags of 97
C   and 33, and operation "subtraction plus one, modulo one") and an
C   "arithmetic sequence" (using subtraction).
C
C On a Vax 11/780, this random number generator can produce a number in
C    13 microseconds.
C======================================================================== */

  int           seed1, seed2;

  float         tmpU[97], *U, C, CD, CM;
  //  float         *U = &tmpU[-1];
  int           I97, J97;

public:
  PTS_MarsagliaRNG(int aseed1=-1, int aseed2=12345);
  double   Double();
  unsigned Unsigned();
  int      Int();

  int      test();   // will just be verbose about problems, dont use return
                     // value as indication that things are ok.
};


inline double PTS_MarsagliaRNG::Double()
{
  /* -----------------------------------------------------------------
C This is the random number generator proposed by George Marsaglia in
C Florida State University Report: FSU-SCRI-87-50
C It was slightly modified by F. James to produce an array of pseudorandom
C numbers.
  -------------------------------------------------------------------- */

  float  uni;

  /* this can't happen in C++ */
  // if(! TEST )
  //  {
  //    printf("(ranmar) Call the init routine (RMARIN) before calling RANMAR"
  //             );
  //    exit (1);
  //  }

  uni = U[I97] - U[J97];
  if( uni < 0.0 ) uni += 1.0;
  U[I97] = uni;
  if( --I97 == 0) I97 = 97;
  if( --J97 == 0) J97 = 97;
  if( (C -= CD) < 0.0 ) C += CM;
  uni -= C;
  if( uni < 0.0 ) uni += 1.0;

  return uni;
}


inline unsigned PTS_MarsagliaRNG::Unsigned()
{
  return (unsigned) (Double() * 4096 * 4096);
}

inline int PTS_MarsagliaRNG::Int()
{
  return (int)      (Double() * 4096 * 4096);
}


/********************************************************************/


/** general 2-tap-xor generator
    (this one and the 4-tap generators could be cleaned up
    a bit using recursion templates - create a general N-tap
    generator and write the recursion over the number of taps)
  */
template< int I, int J >
class PTS_2TapRNG: public PTS_RNG{
public:
  /** requires another generator as 'seed' */
  PTS_2TapRNG(PTS_RNG &a_rng): ind1(0), ind2(J-I) {
    init_array(a_rng);
  }

  /** or uses Marsaglia */
  PTS_2TapRNG(int aseed1=-1, int aseed2=12345): ind1(0), ind2(J-I) {
    PTS_MarsagliaRNG   rng(aseed1,aseed2);
    init_array(rng);
  }

  /** uniform random numbers */
  inline double   Double();
  inline unsigned Unsigned();
  inline int      Int();

protected:
  int ind1, ind2;   // indices to be kept between calls
  unsigned  rnd[J]; // status array

  /** seeds status array */
  inline int init_array(PTS_RNG &);
};


template< int I, int J>
unsigned PTS_2TapRNG<I,J>::Unsigned(){
  ind1++; if ( ind1 >= J ) ind1 = 0;
  ind2++; if ( ind2 >= J ) ind2 = 0;
  return( rnd[ind1] ^= rnd[ind2] );
}

template< int I, int J>
int PTS_2TapRNG<I,J>::Int(){
  ind1++; if ( ind1 >= J ) ind1 = 0;
  ind2++; if ( ind2 >= J ) ind2 = 0;
  return( (rnd[ind1] ^= rnd[ind2]) & int_max );
}

template< int I, int J>
double PTS_2TapRNG<I,J>::Double(){
  ind1++; if ( ind1 >= J ) ind1 = 0;
  ind2++; if ( ind2 >= J ) ind2 = 0;

#if defined(PT_CRAY_T3E) && defined(PT_NATIVE)
  //workaround for cray bug:
  unsigned int uitmp=(rnd[ind1] ^= rnd[ind2]);
  return uitmp/(double)UINT_MAX;
#else
  return ( (rnd[ind1] ^= rnd[ind2]) / (double) unsigned_max );
#endif
}

template< int I, int J>
int PTS_2TapRNG<I,J>::init_array(PTS_RNG &a_rng) {
  int i, j, i_try=0;
  int i_half = a_rng.IntMax()/2;
  unsigned mask;

  do {
    // seed the status array bitwise
    for( i=0; i< J; i++)
      rnd[i] = 0;
    j=sizeof(unsigned)*CHAR_BIT;
    do {
      j--;
      for ( i=0; i< J; i++ )
	  {
	    if ( a_rng.Int() >= i_half ) // set the bit to one
	      mask = 1u << j;
	    else
	      mask = 0u;
	    rnd[i] |= mask;
	  }
      } while (j>0);

    // check the most obvious problems
    mask = 0;
    for (i = 0; i < J; i++)
      mask |= rnd[i];
    if (mask != ~0u )
      i_try++;

  } while ( mask != ~0u && i_try < 10 );

  if ( i_try >= 10 ) {
    cout << "failed to initialize";
  }

  return 1;
}

typedef PTS_2TapRNG<103,250> PTS_KPS250RNG;

//  Local Variables:
//  mode: c++
//  End:


#endif
