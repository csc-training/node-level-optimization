# Number of independent operations, should be modified for investigating effects 
# of pipeline fill and register spill
NUM_OPS=1

# Vector width, change to 8 for AVX512
VECTOR_WIDTH=4

CC=g++
# General optimization flags
OPT=-O2 -ffast-math
# Vectorization options
VECOPT=-mavx2 -mfma # -fopenmp-simd

# OpenMP
OMP=
#OMP=-fopenmp


# PAPI options
PAPI=
#PAPI=-DPAPI -lpapi

CFLAGS=$(OPT) $(VECOPT) $(OMP) $(PAPI)

all: fma add mul div

fma: peak_flops.cpp kernels.hpp
	$(CC) -o peak_fma -DVECTOR_WIDTH=$(VECTOR_WIDTH) -DNUM_OPS=$(NUM_OPS) peak_flops.cpp $(CFLAGS)
add: peak_flops.cpp kernels.hpp
	$(CC) -o peak_add -DKERNEL_ADD -DVECTOR_WIDTH=$(VECTOR_WIDTH) -DNUM_OPS=$(NUM_OPS) peak_flops.cpp $(CFLAGS)
mul: peak_flops.cpp kernels.hpp
	$(CC) -o peak_mul -DKERNEL_MUL -DVECTOR_WIDTH=$(VECTOR_WIDTH) -DNUM_OPS=$(NUM_OPS) peak_flops.cpp $(CFLAGS)
div: peak_flops.cpp kernels.hpp
	$(CC) -o peak_div -DKERNEL_DIV -DVECTOR_WIDTH=$(VECTOR_WIDTH) -DNUM_OPS=$(NUM_OPS) peak_flops.cpp $(CFLAGS)

clean:
	rm -f peak_fma peak_add peak_mul
