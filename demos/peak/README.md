# Microbenchmark for CPU peak performance

Very simple benchmark for testing CPU performance. Code carries out
number of double processing floating point operations, either:

- multiply : `a = a * b`
- add: `a = a + c`
- multiply and add: `a = a * b + c`

## Build

Makefile uses by default GCC, compile all the three operations with default options:
```
make
```
Intel or Clang can be used with `make COMP=intel` or `make COMP=clang`.

By default, code is compiled for AVX2, but Makefile has parameters for also AVX512 which
are commented out.

The parameter NUM_OPS (default 10) in Makefile controls how many floating point operations
are issued at the time. The parameter can be used for investigating effect of pipeline
utilization (small value does not necessarily fully fill the CPU pipeline) and register fill-up
(with large values all operations cannot be performed in registers).

## Running

Set `OMP_NUM_THREADS` and run with chosen number of threads:

```
./peak_fma
# or
./peak_mul
# or
./peak_add
```


