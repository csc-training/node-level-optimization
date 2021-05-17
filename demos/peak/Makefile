ifeq ($(COMP),)
COMP=gnu
endif

ifeq ($(COMP),gnu)
CC=g++
OPT=-O2 -ffast-math
# AVX2
VECTOR_WIDTH=4
AVX=-march=native -mfma
# AVX512
# VECTOR_WIDTH=8
# AVX=-march=native -mfma -mprefer-vector-width=512
CFLAGS = $(OPT) $(AVX) -fopenmp
endif

ifeq ($(COMP),intel)
CC=icpc
OPT=-O2 
# AVX2
VECTOR_WIDTH=4
AVX=-xCORE-AVX2 -fma
# AVX512
# VECTOR_WIDTH=8
# AVX=-xCORE-AVX512 -qopt-zmm-usage=high -fma
CFLAGS = $(OPT) $(AVX) -qopenmp
endif

ifeq ($(COMP),clang)
CC=clang++
OPT=-O2 -ffast-math
# AVX2
VECTOR_WIDTH=4
AVX=-march=native -mfma
# AVX512
# VECTOR_WIDTH=8
# AVX=-march=native -mfma -mprefer-vector-width=512
CFLAGS = $(OPT) $(AVX) -fopenmp
endif

# modify for investigating effects of pipeline fill and register usage
NUM_OPS=8

all: fma add mul

fma: peak_flops.cpp kernels.hpp
	$(CC) -o peak_fma -DVECTOR_WIDTH=$(VECTOR_WIDTH) -DNUM_OPS=$(NUM_OPS) $(CFLAGS) peak_flops.cpp
add: peak_flops.cpp kernels.hpp
	$(CC) -o peak_add -DKERNEL_ADD -DVECTOR_WIDTH=$(VECTOR_WIDTH) -DNUM_OPS=$(NUM_OPS) $(CFLAGS) peak_flops.cpp
mul: peak_flops.cpp kernels.hpp
	$(CC) -o peak_mul -DKERNEL_ADD -DVECTOR_WIDTH=$(VECTOR_WIDTH) -DNUM_OPS=$(NUM_OPS) $(CFLAGS) peak_flops.cpp

clean:
	rm -f peak_fma peak_add peak_mul
