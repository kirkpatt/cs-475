#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <iostream>
#include <fstream>
#include <cmath>

// system state variables
int NowYear = 2017;          // 2017 - 2022
int NowMonth = 0;         // 0 - 11

float NowPrecip;      // inches of rain per month
float NowTemp;        // temperature this month
float NowHeight = 1.0;      // grain height in inches
int NowNumDeer = 1;       // number of deer in the current population
float YearlyGrain = 0.0;	// How much grain was grown in the past year
int SantaNeed = 0;			// How many graindeer Santa will kidnap this year. Should be 0 if it isn't December
int previousNumDeer = 1;

// constants
const float GRAIN_GROWS_PER_MONTH = 8.0;
const float ONE_DEER_EATS_PER_MONTH = 0.5;
const float AVG_PRECIP_PER_MONTH = 6.0;    // average
const float AMP_PRECIP_PER_MONTH = 6.0;    // plus or minus
const float RANDOM_PRECIP = 2.0;           // plus or minus noise
const float SQUATCH_CHANCE = 10.0;         // how likely we are to see a squatch
const float AVG_TEMP = 50.0;               // average
const float AMP_TEMP = 20.0;               // plus or minus
const float RANDOM_TEMP = 10.0;            // plus or minus noise
const float MIDTEMP = 40.0;
const float MIDPRECIP = 10.0;

float Ranf(unsigned int *seedp,  float low, float high) {
    float r = (float)rand_r(seedp);
    return(low + r * (high - low) / (float)RAND_MAX);
}

int Ranf(unsigned int *seedp, int ilow, int ihigh) {
    float low = (float)ilow;
    float high = (float)ihigh + 0.9999f;
    return (int)(Ranf(seedp, low,high));
}

float sqr(float n) {
    return n * n;
}

void GrainDeer() {
    while (NowYear < 2023) {
		previousNumDeer = NowNumDeer;
        if (NowNumDeer < NowHeight) {
            NowNumDeer++;
        } else if (NowNumDeer > NowHeight) {
            NowNumDeer--;
			if (NowNumDeer < 0){ NowNumDeer = 0; }
        }

        #pragma omp barrier
		NowNumDeer = NowNumDeer - SantaNeed;
		if (NowNumDeer < 0){ NowNumDeer = 0; }


        #pragma omp barrier

        #pragma omp barrier
		
    }
}

void Grain() {
    while (NowYear < 2023) {
		// Using a temporary local var so the grain or the deer don't get confused
		int tempHeight = NowHeight; // "Temp" as in "temporary" not "temperature"
        float tempFactor = exp(-sqr((NowTemp - MIDTEMP) / 10.0));
        float precipFactor = exp(-sqr((NowPrecip - MIDPRECIP) / 10.0));

        tempHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
        tempHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
        if (tempHeight < 0.0) { tempHeight = 0.0;}
		if(NowMonth == 0){ 
			YearlyGrain = tempHeight; 
		}else{ 
			YearlyGrain += tempHeight; 
		}

        #pragma omp barrier

        NowHeight = tempHeight;

        #pragma omp barrier

        #pragma omp barrier
		
    }
}

void Watcher() {
	unsigned int seed = time(NULL);
    printf("year,month,precip,temp,grain height,deer,annual grain yield,santa's victims\n");
    while (NowYear < 2023) {

        #pragma omp barrier

        #pragma omp barrier
		// Everything's done running by now
		printf("%d,%d,%f,%f,%f,%d,%f,%d\n",NowYear,NowMonth,NowPrecip,(5.0/9.0)*(NowTemp-32.0),(NowHeight * 2.54),NowNumDeer,(YearlyGrain * 2.54),SantaNeed);

        NowMonth++;
        if (NowMonth == 12) {
            NowYear += 1;
			NowMonth = 0;
        }

        // Start prepping for the next cycle
		if(NowMonth != 11){
			SantaNeed = 0;
		}
        float ang = (30.0 * (float)NowMonth + 15.0) * (M_PI /180.0);

        float temp = AVG_TEMP - AMP_TEMP * cos(ang);
        NowTemp = temp + Ranf(&seed, -RANDOM_TEMP, RANDOM_TEMP);

        float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
        NowPrecip = precip + Ranf(&seed, -RANDOM_PRECIP, RANDOM_PRECIP);
        if (NowPrecip < 0.0) {
            NowPrecip = 0.0;
        }
        #pragma omp barrier

    }
}

void Santa() {
	unsigned int seed = time(NULL);
    while (NowYear < 2023) {
        // If the grain crop over the year was low, some of Santa's reindeer will die out. He's got places to be though, so he'll recruit a few graindeer, since they're close enough. The lower the crop over the year, the more graindeer Santa will need to replace.
		// Santa will never need fewer than 0 deer.
		// Santa will never need more than 8 reindeer (we can assume Rudolph is immortal), but it would take a horrible year for Santa to need that many.
		// Functionally, Santa will never need more than 4 reindeer, because I don't want to wipe out the deer every December.

		// In the end, this did effectively wipe them out every December though. Maybe I shouldn't be a game designer.
		
		if(NowMonth == 11){
			
			if (YearlyGrain > 70.0){
				SantaNeed = 0;
			}
			if ((YearlyGrain > 40.0) && (YearlyGrain < 50.0)){
				SantaNeed = Ranf(&seed,0,2);
			}
			if ((YearlyGrain > 30.0) && (YearlyGrain < 40.0)){
				SantaNeed = Ranf(&seed,1,3);
			}
			if (YearlyGrain < 30.0){
				SantaNeed = 4;
			}
			
		}
        #pragma omp barrier

        #pragma omp barrier

        #pragma omp barrier
		
    }
}

int main(int argc, char *argv[]) {
	// This stuff is also repeated every month
    float ang = (30.0 * (float)NowMonth + 15.0) * (M_PI /180.0);
	
    float temp = AVG_TEMP - AMP_TEMP * cos(ang);
	unsigned int seed = time(NULL);
    NowTemp = temp + Ranf(&seed, -RANDOM_TEMP, RANDOM_TEMP);

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
    NowPrecip = precip + Ranf(&seed, -RANDOM_PRECIP, RANDOM_PRECIP);
    if (NowPrecip < 0.0) {
        NowPrecip = 0.0;
    }

	omp_set_num_threads( 4 );	// same as # of sections
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			GrainDeer( );
		}

		#pragma omp section
		{
			Grain( );
		}

		#pragma omp section
		{
			Watcher( );
		}

		#pragma omp section
		{
			Santa( );
		}
	}       // implied barrier -- all functions must return in order
			// to allow any of them to get past here

    return 0;
}