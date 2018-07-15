#include <omp.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>
#include <math.h>

#define XMIN    0.0
#define XMAX    3.0
#define YMIN    0.0
#define YMAX    3.0

#define TOPZ00  0.0
#define TOPZ10  1.0
#define TOPZ20  0.0
#define TOPZ30  0.0

#define TOPZ01  1.0
#define TOPZ11  6.0
#define TOPZ21  1.0
#define TOPZ31  0.0

#define TOPZ02  0.0
#define TOPZ12  1.0
#define TOPZ22  0.0
#define TOPZ32  4.0

#define TOPZ03  3.0
#define TOPZ13  2.0
#define TOPZ23  3.0
#define TOPZ33  3.0

#define BOTZ00  0.0
#define BOTZ10  -3.0
#define BOTZ20  0.0
#define BOTZ30  0.0

#define BOTZ01  -2.0
#define BOTZ11  10.0
#define BOTZ21  -2.0
#define BOTZ31  0.0

#define BOTZ02  0.0
#define BOTZ12  -5.0
#define BOTZ22  0.0
#define BOTZ32  -6.0

#define BOTZ03  -3.0
#define BOTZ13   2.0
#define BOTZ23  -8.0
#define BOTZ33  -3.0

float Height(int iu, int iv, int NUMNODES) {
	
    float u = (float)iu / (float)(NUMNODES-1);
    float v = (float)iv / (float)(NUMNODES-1);

									// the basis functions:

    float bu0 = (1.-u) * (1.-u) * (1.-u);
    float bu1 = 3. * u * (1.-u) * (1.-u);
    float bu2 = 3. * u * u * (1.-u);
    float bu3 = u * u * u;

    float bv0 = (1.-v) * (1.-v) * (1.-v);
    float bv1 = 3. * v * (1.-v) * (1.-v);
    float bv2 = 3. * v * v * (1.-v);
    float bv3 = v * v * v;

									// finally, we get to compute something:
        float top =       bu0 * ( bv0*TOPZ00 + bv1*TOPZ01 + bv2*TOPZ02 + bv3*TOPZ03 )
                        + bu1 * ( bv0*TOPZ10 + bv1*TOPZ11 + bv2*TOPZ12 + bv3*TOPZ13 )
                        + bu2 * ( bv0*TOPZ20 + bv1*TOPZ21 + bv2*TOPZ22 + bv3*TOPZ23 )
                        + bu3 * ( bv0*TOPZ30 + bv1*TOPZ31 + bv2*TOPZ32 + bv3*TOPZ33 );
						
        float bot =       bu0 * ( bv0*BOTZ00 + bv1*BOTZ01 + bv2*BOTZ02 + bv3*BOTZ03 )
                        + bu1 * ( bv0*BOTZ10 + bv1*BOTZ11 + bv2*BOTZ12 + bv3*BOTZ13 )
                        + bu2 * ( bv0*BOTZ20 + bv1*BOTZ21 + bv2*BOTZ22 + bv3*BOTZ23 )
                        + bu3 * ( bv0*BOTZ30 + bv1*BOTZ31 + bv2*BOTZ32 + bv3*BOTZ33 );
        return top - bot;   		
									// if the bottom surface sticks out above the top surface
									// then that contribution to the overall volume is negative
}

int main() {

    int NUMT = 1;
    int NUMNODES = 1000;

    omp_set_num_threads(NUMT);

									// Start the time
    double time0 = omp_get_wtime();
									// the area of a single full-sized tile:
    float fullTileArea = (
        (( XMAX - XMIN )/(float)(NUMNODES-1))  *
        (( YMAX - YMIN )/(float)(NUMNODES-1))
    );
									// sum up the weighted heights into the variable "volume"
    double volume = 0.0;

    for (int i = 0; i < NUMNODES*NUMNODES; i++) {
        int iu = i % NUMNODES;
        int iv = i / NUMNODES;

        double preVolume = Height(iu, iv, NUMNODES) * fullTileArea;

        if (iu == 0 || iu == (NUMNODES - 1)) {preVolume *= 0.5;}
        if (iv == 0 || iv == (NUMNODES - 1)) {preVolume *= 0.5;}
        volume += preVolume;
    }

    int heights_calculated = (NUMNODES * NUMNODES);
									// Stop the time
    double time1 = omp_get_wtime();
    double time = (time1 - time0);
	
	printf( "%d,%d,%8.15f,%8.15f \n", NUMNODES,NUMT,volume,time);

    return 0;
}