/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define PADDING 8 // Assume 64 byte L1 cache line size

static long num_steps = 100000000;
double step;
int main ()
{
    double x, pi, sum = 0.0;
    double start_time, run_time;
    int max_threads = omp_get_max_threads();

    step = 1.0/(double) num_steps;

    start_time = omp_get_wtime();

    int num_threads;
#pragma omp parallel shared(num_threads)
{
    int ID = omp_get_thread_num();

    if (ID == 0) {
        num_threads = omp_get_num_threads();
    }

    double partial_sum = 0;
    for (int i=ID; i<= num_steps; i+= num_threads) {
        x = (i-0.5)*step;
        partial_sum += 4.0/(1.0+x*x);
    }

#pragma omp critical
    sum += partial_sum;
}

    pi = step * sum;
    run_time = omp_get_wtime() - start_time;
    printf("\n pi with %ld steps is %lf in %lf seconds\n ", num_steps, pi, run_time);
}
