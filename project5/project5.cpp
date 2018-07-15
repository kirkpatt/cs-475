#include <omp.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "simd.p5.h"

int main() {
	int currentarrSize = 1000;
    while (true){	// There are better ways to do this, but since the instructions specified between 1k and 32m, I figured I would make sure to do exactly 1k and exactly 32k every run.
        float* a = new float[currentarrSize];
        float* b = new float[currentarrSize];
        float* c = new float[currentarrSize];
		
		double time0 = omp_get_wtime();
        SimdMul(a, b, c, currentarrSize);
        double time1 = omp_get_wtime();
		double totalTime = time1 - time0;
		printf("%d,%f,SimdMul\n",currentarrSize,totalTime); // Since I'm going to have to do 8000 things in excel this time anyway, I'm not going to bother with nice formatting for outputs this time.
		
        time0 = omp_get_wtime();
        for (int i = 0; i < currentarrSize; i++) {
            c[i] = a[i] * b[i];
        }
        time1 = omp_get_wtime();
		totalTime = time1 - time0;
		printf("%d,%f,MyMul\n",currentarrSize,totalTime);
		
		time0 = omp_get_wtime();
        double simdSum = SimdMulSum(a, b, currentarrSize);
        time1 = omp_get_wtime();
		totalTime = time1 - time0;
		printf("%d,%f,SimdMulSum\n",currentarrSize,totalTime);
		
        int mulsum = 0;
        time0 = omp_get_wtime();
        for (int i = 0; i < currentarrSize; i++) {
            mulsum += a[i] * b[i];
        }
        time1 = omp_get_wtime();
		totalTime = time1 - time0;
		printf("%d,%f,MyMulSum\n",currentarrSize,totalTime);
		
		// Since these ifs are a bit ugly, I'll explain each.
		if (currentarrSize == 1000){
			currentarrSize = 0;				// The stray 1000 in every other currentarrSize after the first would make some annoying values without this.
		}
		if (currentarrSize == 32000000){	// Since we while (true), we need to get out of the last one somehow
			return 0;
		}
		currentarrSize += 500000;
    }
    return 0;
}