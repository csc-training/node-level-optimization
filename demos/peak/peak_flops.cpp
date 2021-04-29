// Simple microbenchmark for measuring peak floating point performance
// 
#include <stdio.h>
#include <omp.h>
#include <math.h>

#if defined KERNEL_ADD
#define KERNEL add
const int flops_per_calc = 1; // Add = 1 operation
char kernel_name[4] = "add";
#elif defined KERNEL_MUL
#define KERNEL mul
const int flops_per_calc = 1; // Multiply = 1 operation
char kernel_name[4] = "mul";
#else
#define KERNEL fma
const int flops_per_calc = 2; // Multiply + add = 2 operations
char kernel_name[4] = "fma";
#endif

#ifndef NUM_OPS // Number of operations, affects pipeline thoughput
#define NUM_OPS 8
#endif

#ifndef VECTOR_WIDTH // Vector width in number of doubles
#define VECTOR_WIDTH 4  // Default for AVX2
#endif

#include "kernels.hpp"

const int n_trials = 1000000000; 

int main() {

#pragma omp parallel
  { } // Create the thread pool

  double fcheck;
  const double t0 = omp_get_wtime(); // start timer
#pragma omp parallel
  { 
    double fa[VECTOR_WIDTH*NUM_OPS], fb[VECTOR_WIDTH], fc[VECTOR_WIDTH];

    int i, j, t;

    for (i=0, j=0; i < VECTOR_WIDTH; i++) {
       for (int n=0; n < NUM_OPS; n++, j++)
          fa[j] = 0.0; 
       fb[i] = 0.5; 
       fc[i] = 1.0; 
    }

#pragma nounroll // Try to prevent automatic unrolling
    for(t = 0; t < n_trials; t++)
#pragma omp simd 
      for (j = 0; j < VECTOR_WIDTH; j++) { 
          KERNEL<NUM_OPS, double>(&fa[j], &fb[j], &fc[j]);
      }

   // Prevent dead code elimination
   for (i=0, j=0; i < VECTOR_WIDTH; i++) {
       for (int n=0; n < NUM_OPS; n++, j++)
          fa[j] *= 2.0; 
    }
    fcheck = fa[0];
  }
  
  const double t1 = omp_get_wtime();

  // Convert everything to doubles for avoiding integer overflows
  const double gflops = 1.0e-9 * (double)VECTOR_WIDTH *
                        (double)n_trials * (double)flops_per_calc * 
                        (double)omp_get_max_threads() * (double)NUM_OPS;
  printf("Num %ss=%d, vector width=%d, threads=%d GFLOPs=%.1f, time=%.6f s, performance=%.1f GFLOP/s\n",
         kernel_name, NUM_OPS, VECTOR_WIDTH, omp_get_max_threads(), gflops, t1 - t0, gflops/(t1 - t0));
}

