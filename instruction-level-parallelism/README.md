# Simple vectorization and instruction level parallelism

In this exercise you can investigate with a simple microbenchmark how vectorization and instruction
level parallelism show up in the performance. We suggest you to try here both Mahti and Puhti.

[peak](../demos/peak) is microbenchmark, where one issues independent operations (fused multiply adds, multiplications, or additions). Operands can be kept in registers, so the 
the code is purely compute bound and can reach close to theoretical peak 
floating point performance. The code uses C++ template metaprogramming, but in pseudocode the main kernel looks like (for fused multiply add, multiply and add correspondingly):
```
for i = 1, width
  a_1[i] = a_1[i] * b[i] + f[c]
  ... 
  a_xx[i] = a_xx[i] * b[i] + f[c]
```
With a proper `width`, vector instructions can be used.

The number of independent operations is a compile time constant that is specified in the
[Makefile](../demos/peak/Makefile) in `NUM_OPS` variable.


## Vectorization

In order to make the illustration of performance topics easier, we focus here only
on the behaviour of GCC with very basic compiler options. Other compilers might perform some optimization discussed here
by default or at lower optimization levels, and we encourage you to investigate later on
also Intel and Clang compilers.

With the default options in [Makefile](../demos/peak/Makefile), GCC does not vectorize 
the code. Here, you can investigate how enabling vectorization affects performance. 

- Compile and run the code first (with a single thread / core) with the default settings.
- Enable then vectorization by adding the `-fopenmp-simd` option, how does the 
  performance change?
- Most of the current CPUs have vector units that can perform the fused multiply add 
  operation in one instruction. However, that changes the semantics of floating point 
  arithmetics a bit, and thus GCC does not use FMA instructions with the given options. Enable 
  FMA instructions by adding `-mfma` option. How does the performance change?
- In Puhti, try to use AVX512 instead of the default AVX2 (change `VECTOR_WIDTH` to 8
  and compile with `-mavx512f -mprefer-vector-width=512`). 
- Try to get compiler optimization report (e.g. by adding `-fopt-info-vec`) both
  with vectorization enabled and disabled.
- Try to look also into assembly code both with and without vectorization 
  (you can produce `peak_xxx.s` file with `-S -fverbose-asm`). You can look 
  e.g. for `xmm` (SSE), ´ymm` (AVX2), and `zmm` (AVX512) registers. 
  As GCC does not inform about the use of FMA instructions in the optimization reports, 
  looking into assembly is often the only way to find out if they are used.

## Pipelining and register spilling

- Compile and run the code with different `NUM_OPS` (e.g. 1, 4, 8, 10), and 
  investigate the performance (at this stage, use still only single core / thread). 
    - You can avoid editing [Makefile](../demos/peak/Makefile) by `make -B NUM_OPS=4)
  What is the minimum value that is needed  for peak performance with different 
  operations and with different CPUs (AMD, Intel)? 

You may look for the latencies and throughput of corresponding floating point instructions
in [Agner's optimization manual](https://www.agner.org/optimize/instruction_tables.pdf), how well does your observations correspond with the 
```
concurrency = latency * throughput
```
formula?

- In Mahti, AMD CPU cores have 16 AVX registers, the Intel CPU cores in Puhti 32. With 
large enough `NUM_OPS`, all operands can no longer be kept in registers. Try to work out on
pen and paper how many registers are needed for different operations. What is the 
critical value for `NUM_OPS`? Investigate what happens to performance when this value is
exceeded.  

- How does the maximum single core performance you obtain correspond with the 
theoretical peak performance of the corresponding CPU?

- Finally, enable multithreading by adding `-fopenmp` and run the code with several
  cores/threads. Does the performance scale linearly?

## Simple performance analysis with perf

`perf` is a Linux command line tool that can collect various hardware
performance counters during the execution of a program. Available counters depend on
the underlying hardware, and can be seen with `perf list`.

- Repeat some of the previous tests with `perf` and try to get further understanding
  by looking into proper counters. As an example, number of instructions and 
  cycles (and also number of instructions per cycle, IPC) can be seen with
```
srun ... perf stat -e instructions,cycles ./peak_fma
```

Tip: look what happens to L1 accesses when too large `NUM_OPS` starts to cause register 
spilling.

## Simple performance analysis with PAPI

PAPI is most often used together with other performance analysis tools (TAU, scorep, ...),
but we have added to this microbenchmark a possibility to collect some metrics also
with PAPI.

In order to use PAPI, you should uncomment the PAPI options in the Makefile, and load relevant modules:
- Mahti
```
module load gcc/13.1.0 papi/7.1.0
```
- Puhti
```
module load papi
```

By default, the code prints out `PAPI_TOT_INS` and `PAPI_TOT_CYC` metrics, but user can
provide additional metrics as a comma separated list in `PAPI_EVENTS` environment variable, e.g. `export PAPI_EVENTS=PAPI_FP_INS,PAPI_FP_OPS`

The available metrics depend again on the underlying hardware and can be seen with `papi_avail -a` command.

- Repeat some of the previous tests with PAPI, do you get similar results as with `perf` in the previous step? Note that `perf` and PAPI cannot be used simultaneously (the metrics are garbage).

- Can you work out on the pen and paper expected IPC? How do the performance counter data
correspond with your estimate?

