ifeq ($(COMP),)
COMP=gnu
endif

ifeq ($(COMP),gnu)
CC=gcc
CFLAGS=-O3 -fopenmp -march=native
endif

ifeq ($(COMP),clang)
CC=clang
CFLAGS=-O3 -fopenmp -march=native
endif

ifeq ($(COMP),intel)
CC=icc
CFLAGS=-O3 -xCORE-AVX2 -ffreestanding -qopenmp -qopt-streaming-stores=always
endif

STREAM_FLAGS=-DSTREAM_ARRAY_SIZE=80000000 -DNTIMES=20

all: stream

stream: stream.c
	$(CC) $(CFLAGS) $(STREAM_FLAGS) stream.c -o stream

clean:
	rm -f stream *.o

