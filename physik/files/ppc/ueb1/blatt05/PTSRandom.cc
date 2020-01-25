#include <iostream>

#include "PTSRandom.h"

int PTS_RNG::test()
{
  return uniformity();
}

/** exercises the Double's, returns 1 on pass, 0 on fail
    improvement: should probably be a template member taking
    a member function pointer to the routine to be tested.
 */
int PTS_RNG::uniformity(){

  const unsigned int n_int=100;     // number of bins
  const unsigned int n_test=1<<24;  // number of test draws

  int rtn = 0;                      // return 1 on failure
  unsigned count[n_int];
  unsigned oob = 0;                 // numbers possibly out of bounds
  double min = DoubleMin();         // limits
  double max = DoubleMax();

  for ( unsigned i=0; i < n_int; i++ )
    count[i] = 0u;

  for ( unsigned i=0; i < n_test; i++ ) {
    double rnd = Double();
    if ( rnd < min || rnd > max ) {
      cout << "out of range " << min << ".." << max << ": " << rnd;
      rtn = 1;
      oob++;
    }
    else {
      int idx = (int) ( (rnd - min)/(max - min) * n_int);
      if ( idx >= n_int ) idx = n_int-1;
      count[idx]++;
    }
  }

  // analyze variance - we should probably do a full blow xi^2 test,
  // but I will go for the variance only
  double variance =0.;
  for ( unsigned i=0; i < n_int; i++ ){
    variance += (count[i] - (n_test / (double) n_int)) *
             (count[i] - (n_test / (double) n_int));
  }
  variance /= n_int;

  // let fail if the variance is a lot different from what we
  // expect: Npq
  double npq = double(n_test)/ n_int;
  if ( 1.3 * npq < variance || 0.7 * npq > variance || oob > 0 ){
    cout <<  "uniformity test failed, measured variance " << variance
		<< " vs expected " << npq << ", o.o. bounds " << oob;
    rtn = 1;
  }
  else {
    cout <<  "uniformity test passed, measured variance " << variance
		<< " vs expected " << npq;
    rtn = 0; // ok
  }

  return rtn;  // 0 == ok
}


// ============================    MARSGAGLIA   =====================


PTS_MarsagliaRNG::PTS_MarsagliaRNG(int IJ, int KL):
  PTS_RNG(), seed1(IJ), seed2(KL), U( &tmpU[0]-1 )
{
  /* ------------------------------------------------------------------

C This is the initialization routine for the random number generator RANMAR()
C NOTE: The seed variables can have values between:    0 <= IJ <= 31328
C                                                      0 <= KL <= 30081
C The random number sequences created by these two seeds are of sufficient
C length to complete an entire calculation with. For example, if sveral
C different groups are working on different parts of the same calculation,
C each group could be assigned its own IJ seed. This would leave each group
C with 30000 choices for the second seed. That is to say, this random
C number generator can create 900 million different subsequences -- with
C each subsequence having a length of approximately 10~30.
C
C Use IJ = 1802 & KL = 9373 to test the random number generator. The
C subroutine RANMAR should be used to generate 20000 random numbers.
C Then display the next six random numbers generated multiplied by 4096*4096
C If the random number generator is working properly, the random numbers
C should be:
C           6533892.0  14220222.0  7275067.0
C           6172232.0  8354498.0   10633180.0
   ------------------------------------------------------------------ */

  int i, j, k, l, m, ii, jj, tim=0;
  float s,t;

  // base class members
  int_max      = unsigned_max = 4096 * 4096;

  if( seed1 < 0 || seed2 < 0 )
    tim = time(0);

  if ( seed1 < 0 )
    seed1 = tim % (31328 + 1);
  else if ( seed1 > 31328 ){
    seed1 %= (31328 + 1);
    cout << "Marsaglia: seed 1 exceeds 31328 - using " << seed1 ;
  }

  if ( seed2 < 0 )
    seed2 = tim % (30081 + 1);
  else if ( seed2 > 30081 ) {
    seed2 %= (30081 + 1);
    cout <<  "Marsaglia: seed 2 exceeds 30081 - using " << seed2;
  }

  IJ = seed1; KL = seed2;

  i = (IJ/177) % 177 + 2;
  j =  IJ      % 177 + 2;
  k = (KL/169) % 178 + 1;
  l =  KL      % 169;

  for( ii=1; ii<=97; ii++)
    {
      s = 0.0; t = 0.5;
      for ( jj=0; jj < 24; jj++ )
       {
          m = (((i*j) % 179)*k) % 179;
          i = j;
          j = k;
          k = m;
          l = (53*l+1) % 169;
          if( (l*m) % 64 >= 32 )
            s = s + t;
          t = 0.5 * t;
        }
      U[ii] = s;
    }

  C  =   362436.0 / 16777216.0;
  CD =  7654321.0 / 16777216.0;
  CM = 16777213.0 / 16777216.0;

  I97 = 97;
  J97 = 33;

  return;
}


int PTS_MarsagliaRNG::test()
{
  PTS_MarsagliaRNG m(1802,9373);

  double   rn;
  int      flag=0;
  int      i;

  for ( i=0; i<20000; i++ )
    (void) m.Double();

  rn = m.Double()*4096*4096;
  flag |= ( rn !=  6533892.0 );
  rn = m.Double()*4096*4096;
  flag |= ( rn != 14220222.0 );
  rn = m.Double()*4096*4096;
  flag |= ( rn != 7275067.0 );
  rn = m.Double()*4096*4096;
  flag |= ( rn != 6172232.0 );
  rn = m.Double()*4096*4096;
  flag |= ( rn != 8354498.0 );
  rn = m.Double()*4096*4096;
  flag |= ( rn != 10633180.0 );

  cout << "MarsagliaRNG implementation test " << (flag ? "failed" : "passed") ;

  if ( flag ) {
    cout << "random sequence not reproducible, faulty implementation, "
            "tested MarsagliaRNG m(1802,9373)";
  }

  // call base class tests
  return ( PTS_RNG::test() | flag );
}












