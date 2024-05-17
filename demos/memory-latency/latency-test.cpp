/*****************************************************************************
MIT License

Copyright (c) 2024 CSC HPC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

// Simple benchmark for measuring cache and memory access latencies with pointer chasing.

#include <cstdio>
#include <chrono>
#include <algorithm>
#include <random>
#ifdef PAPI
#include <papi.h>
#endif

using Clock = std::chrono::high_resolution_clock;

int main(int argc, char** argv)
{

  const int base_size = 1024 / sizeof(void *);
  const int cache_line = 64 / sizeof(void *);
  int accesses_per_cache_line = 8;
  int access_stride = cache_line / accesses_per_cache_line;
  bool random = true;
  const size_t num_accesses = 1048576; // 2^20

#ifdef PAPI
  PAPI_library_init(PAPI_VER_CURRENT);
  int eventset=PAPI_NULL;
  PAPI_create_eventset(&eventset);
  PAPI_add_named_event(eventset,"PAPI_TOT_CYC");
  long long papi_values;
#endif

  auto rng = std::default_random_engine {};

#ifdef PAPI
  printf("# mem (kiB)  latency (ns)  cycles\n");
#else
  printf("# mem (kiB)  latency (ns)\n");
#endif

  // Test up to 2^17 kiB = 64 MiB 
  for (int i=0; i < 17; i++)
  {
    size_t memsize_k = (1 << i);
    size_t memsize = base_size * memsize_k;
    std::vector<void *> mem(memsize*access_stride);

    std::vector<size_t> indices(memsize);
    for (size_t c=0; c < memsize; c++) {
        indices[c] = c;
    } 

    // Create either a random or sequentila chain of pointers
    if (random) std::shuffle(std::begin(indices), std::end(indices), rng);
    for (size_t c=0; c < memsize; c++) {
        mem[c*access_stride] = &mem[((indices[c] + 1) % memsize)*access_stride];
    }

    int num_trials = num_accesses / memsize;
    num_trials = (num_trials > 8) ? num_trials : 8;
    void *p = mem[0];
#ifdef PAPI
    PAPI_reset(eventset);
    PAPI_start(eventset);
#endif
    auto t0 = Clock::now();
    for (int n=0; n < num_trials; n++)
       for (int c=0; c < memsize; c++)
          // void pointers cannot be dereferenced so we need to cast
          p = *(void **) p; 

    auto t1 = Clock::now();
#ifdef PAPI
    PAPI_stop(eventset, &papi_values);
#endif
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0);
    double time_per_access = duration.count() / (double) (num_trials * memsize);
#ifdef PAPI
    int num_cycles = papi_values / (num_trials * memsize);
    printf("%10ld  %12.4f %8d\n", memsize_k, time_per_access, num_cycles);
#else
    printf("%10ld  %12.4f\n", memsize_k, time_per_access);
#endif

    // print final value to /dev/null to avoid optimizing out
    FILE* devnull;
    devnull = fopen("/dev/null", "w");
    fprintf(devnull, "p %p", p);
    fclose(devnull);

    // delete [] mem;
  }
}
