CC=gcc
CFLAGS=-O3 -fopenmp -march=native
STREAM_FLAGS=-DSTREAM_ARRAY_SIZE=80000000 -DNTIMES=20

all: stream

stream: stream.c
	$(CC) $(CFLAGS) $(STREAM_FLAGS) stream.c -o stream

clean:
	rm -f stream *.o

# an example of a more complex build line for the Intel icc compiler
stream.icc: stream.c
	icc -O3 -xCORE-AVX2 -ffreestanding -qopenmp -qopt-streaming-stores=always -DSTREAM_ARRAY_SIZE=80000000 -DNTIMES=20 stream.c -o stream.icc
