PROG=quicksort

CXX = g++
CXXFLAGS=-O3 -fopenmp
LDFLAGS=-fopenmp

debug:
	$(CXX) $(CXXFLAGS) -g -O0 ${PROG}.cpp -o ${PROG}.exe

release:
	$(CXX) $(CXXFLAGS) -O3 ${PROG}.cpp -o ${PROG}.exe

solution:
	$(CXX) $(CXXFLAGS) -O3 ${PROG}-solved.cpp -o ${PROG}-solved.exe

run:
	./${PROG}.exe

clean:
	rm -f ${PROG}.exe ${PROG}-solved.exe ${PROG}.o *~
