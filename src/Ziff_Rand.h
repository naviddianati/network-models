#ifndef ZIFF_RAND
#define ZIFF_RAND

/////////////////////////////////////////////////////////////////////////////
//////////////////Ziff Random number generator///////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// To use this random number generator, first seed it
// example: seed((unsigned) time(NULL)); // be sure to include <time.h>
//
// to get a integer use: NewRandomInteger.
// example: int A = NewRandomInteger;
// Use DRand in a similar fashion.
// Note: DRand returns a double in the range [0,1] (both inclusive on 0 and 1)

#define M  16383
long    ra[M+1], nd;

#define NewRandomInteger (++nd,ra[nd&M] = ra[(nd-471)&M]^ra[(nd-1586)&M]^ra[(nd-6988)&M]^ra[(nd-9689)&M])
#define DRand ( (double) (++nd,ra[nd&M] = ra[(nd-471)&M]^ra[(nd-1586)&M]^ra[(nd-6988)&M]^ra[(nd-9689)&M]) / 2147483648)

void seed(long seed)
{
        double a, ee = -1 + 1/2147483648.0;
        long i;
        extern long nd, ra[M+1];

        a = seed/2147483648.0;
        for (nd = 0; nd <= M; nd++)
        {
                a *= 16807;
                a += ee * (long)(a);
                if (a >= 1) a += ee;
                ra[nd] = (long) (2147483648.0 * a);
        }
        nd = M;
        for(i = 0; i<100001; i++)
                NewRandomInteger;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#endif

