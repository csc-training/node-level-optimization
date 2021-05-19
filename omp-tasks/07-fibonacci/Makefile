PROG=fibonacci

CC=gcc
CCFLAGS=-O3 -fopenmp
LDFLAGS=-fopenmp

debug:
	$(CC) $(CCFLAGS) -g -O0 ${PROG}.c -o ${PROG}.exe

release:
	$(CC) $(CCFLAGS) -O3 ${PROG}.c -o ${PROG}.exe

solution:
	$(CC) $(CCFLAGS) -O3 ${PROG}-solved.c -o ${PROG}-solved.exe

run:
	./${PROG}.exe < input

clean:
	rm -f ${PROG}.exe ${PROG}-solved.exe  ${PROG}.o *~
