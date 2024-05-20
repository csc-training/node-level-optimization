#include <iostream>
#include <chrono>
#include "matrix.hpp"

using Clock = std::chrono::high_resolution_clock;

template <class T> void matmul(const Matrix<T> &a, const Matrix<T> &b,
                               Matrix<T> &c)
{
  int N = a.nx;

  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      c(i,j) = 0.0;
      for (int k=0; k<N; k++) {
         c(i,j) += a(i,k) * b(k,j);
      }
    }
  }
}


int main(int argc, char *argv[])
{
    int maxiter, N;

    if (argc==3) {
      maxiter = std::atoi(argv[1]);
      N = std::atoi(argv[2]);
    }
    else {
      std::cout << "usage: ./matmul number-of-iterations array-size"
                << std::endl;
      exit(0);
    }

    auto a = Matrix<double> (N, N);
    auto b = Matrix<double> (N, N);
    auto c = Matrix<double> (N, N);

    // initialization a and b
    for (int i=0; i<N; i++) {
      for (int j=0; j<N; j++) {
        a(i,j) = 5.0e-1;
        b(i,j) = 2.0e-1;
      }
    }

    auto start = Clock::now();

    for (int iter=0; iter < maxiter; iter++)
      matmul(a, b, c);

    auto stop = Clock::now();

    std::chrono::duration<double> elapsed_seconds = stop - start;

    std::cout << "Matrix multiplication N=" << N
              << " " << elapsed_seconds.count() / maxiter << " s "
              << "check: " <<  c(N-1, N-1) << std::endl;

    return 0;
}
