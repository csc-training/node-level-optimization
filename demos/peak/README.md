# Microbenchmark for CPU peak performance

Very simple benchmark for testing CPU performance. Code carries out
number of double processing floating point operations, either:

- multiply : `a = a * b`
- add: `a = a + c`
- multiply and add: `a = a * b + c`

## Build

Makefile contains parameters for GCC, compile all the three operations with default options:
```
make
```

## Running

Set `OMP_NUM_THREADS` and run with chosen number of threads:

```
./peak_fma
# or
./peak_mul
# or
./peak_add
```


