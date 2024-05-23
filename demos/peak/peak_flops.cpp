// Simple microbenchmark for measuring peak floating point performance
// 
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <chrono>
#ifdef PAPI
#include <papi.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#endif

#if defined KERNEL_ADD
#define KERNEL add
const int flops_per_calc = 1; // Add = 1 operation
char kernel_name[4] = "add";
#elif defined KERNEL_MUL
#define KERNEL mul
const int flops_per_calc = 1; // Multiply = 1 operation
char kernel_name[4] = "mul";
#elif defined KERNEL_DIV
#define KERNEL div
const int flops_per_calc = 1; // Multiply = 1 operation
char kernel_name[4] = "div";
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

const int n_trials = 1000000000 / NUM_OPS;

using Clock = std::chrono::high_resolution_clock;

int main() {


#pragma omp parallel
  { } // Create the thread pool

  int nthreads = 1;
#ifdef _OPENMP
  nthreads = omp_get_max_threads();
#endif

  double fcheck = 0.0;

#ifdef PAPI
  PAPI_library_init(PAPI_VER_CURRENT);
  int eventset=PAPI_NULL;
  PAPI_create_eventset(&eventset);
  PAPI_add_named_event(eventset,"PAPI_TOT_INS");
  PAPI_add_named_event(eventset,"PAPI_TOT_CYC");
  
  std::vector<std::string> papi_events;
  // Measure always total instructions and cycles
  papi_events.push_back("PAPI_TOT_INS");
  papi_events.push_back("PAPI_TOT_CYC");
  if (std::getenv("PAPI_EVENTS") != nullptr) {
    std::string events_from_env(std::getenv("PAPI_EVENTS"));
    std::stringstream ss(events_from_env);
    char delimiter = ',';
    std::string event_name;
    while (getline(ss, event_name, delimiter)) { 
      if (PAPI_add_named_event(eventset, event_name.c_str()) != PAPI_OK) {
        std::cout << "Adding PAPI event " << event_name << " failed" << std::endl;
      } else {
        std::cout << "Adding PAPI event " << event_name << std::endl;
        papi_events.push_back(event_name);
      }
    }
  } 
  
  int num_papi_events = papi_events.size();

  long long *papi_values = new long long[num_papi_events];

  PAPI_reset(eventset);
  PAPI_start(eventset);
#endif

  //const double t0 = omp_get_wtime(); // start timer
  auto t0 = Clock::now();
#pragma omp parallel
  { 
    double fa[VECTOR_WIDTH*NUM_OPS], fb[VECTOR_WIDTH], fc[VECTOR_WIDTH];

    int i, j, t;

    for (i=0, j=0; i < VECTOR_WIDTH; i++) {
       for (int n=0; n < NUM_OPS; n++, j++)
          fa[j] = 1.2345;
       fb[i] = 0.5678; 
       fc[i] = 3.0102; 
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
         fcheck += fa[j];
    }
  }
  
  //const double t1 = omp_get_wtime();
  auto t1 = Clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
  double elapsed_seconds = 1.0e-6 * duration.count();
  // double elapsed_seconds = t1 - t0;

#ifdef PAPI
  //PAPI_hl_region_end("computation");
  PAPI_stop(eventset, papi_values);
#endif

  // Convert everything to doubles for avoiding integer overflows
  const double gflops = 1.0e-9 * (double)VECTOR_WIDTH *
                        (double)n_trials * (double)flops_per_calc * 
                        (double)nthreads * (double)NUM_OPS;
  printf("Num %ss=%d, vector width=%d, threads=%d GFLOPs=%.1f, time=%.6f s, performance=%.1f GFLOP/s\n",
         kernel_name, NUM_OPS, VECTOR_WIDTH, nthreads, gflops, elapsed_seconds, gflops / elapsed_seconds);

#ifdef PAPI
  const double ins_per_flop = (double)nthreads * (double) papi_values[0] * 1.0e-9 / gflops;
  const double cyc_per_flop = (double)nthreads * (double) papi_values[1] * 1.0e-9 / gflops;
  const double ins_per_cycle = (double) papi_values[0] / (double) papi_values[1];
  const double clock_freq = 1.0e-9 * (double) papi_values[1] / elapsed_seconds;
  printf("PAPI metrics:\n");
  for (int i=0; i < num_papi_events; i++) {
     printf("%12s  %14lld\n", papi_events[i].c_str(), papi_values[i]);
  }
  printf("Derived metrics: \n");
  printf("Ins per flop=%.3f, cyc per flop=%.3f, IPC=%.3f, clock freq=%.3f GHz\n",
          ins_per_flop,cyc_per_flop,ins_per_cycle, clock_freq);
#endif
  
  // print fcheck to dev/null to prevent too aggressive compiler optimizations
  FILE* devnull;
  devnull = fopen("/dev/null", "w");
  fprintf(devnull, "fcheck %f", fcheck);
  fclose(devnull);
}

