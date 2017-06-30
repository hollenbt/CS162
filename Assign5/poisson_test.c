/*********************************************************************
 ** Program Filename: poisson_test.c
 ** Author: Tommy Hollenberg
 ** Date: 06/05/2017
 ** Description: This program only exists to demonstrate the correctness
 **   of the poisson_knuth algorithm.   
 ** Input: Pass in a double value for the average time between customer
 **   arrivals, as a command-line argument (do not include any tags).
 ** Output: The program prints the average number of arrivals per minute
 **   of 10000 samples. The algorithm returns an integer, but the
 **   average is a double for accuracy. The output should approximate
 **   one divided by the average time between arrivals.
 *********************************************************************/

#include "list.h"
#include "math.h"

int poisson_knuth(double lambda) {
    int k = 0;
    long double p = 1.0, L = exp(-lambda);
    do {
        ++k;
        p *= ((long double) rand() + 1) / ((long double) RAND_MAX + 1);
    } while (p > L);
    return k - 1;
}

int main(int argc, char *argv[]) {
    
    int i = 0;
    double sum = 0;

    srand(time(NULL));

    for (i = 0; i < 10000; ++i)
       sum += poisson_knuth(1.0 / atof(argv[1]));

    printf("Average arrivals per minute: %f\n", sum / i);

    return 0;

}
