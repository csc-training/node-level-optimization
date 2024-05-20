#include <iostream>
#include <chrono>
#include "matrix.hpp"

#ifndef BLOCK
#define BLOCK 10
#endif

using Clock = std::chrono::high_resolution_clock;

template <class T> void matmul(const Matrix<T> &a, const Matrix<T> &b,
                               Matrix<T> &c)
{
  int N = a.nx;
  // Matrix for the transpose of b
  auto t = Matrix<T> (N, N);

  // By transposing b first, later memory access will be more efficient
  for (int i=0;i<N;i++) {
    for (int j=0;j<N;j++) {
      t(i,j) = b(j,i);
    }
  }

  int block = BLOCK;
  int num_blocks = N / block;

  // zero c outside blocking
  for (int i=0; i < N; i++) {
    for (int j=0; j < N; j++) {
      c(i,j) = 0;
    }
  }


  // loop over blocks
  for (int bi=0 ;bi < num_blocks; bi++) {
    for (int bj=0; bj < num_blocks; bj++) {
      for (int bk=0; bk < num_blocks; bk++) {
        // loop within blocks
        for (int i=0; i < block; i++) {
          for (int j=0; j < block; j++) {
            for (int k=0; k < block; k++) {
              c(i + bi*block, j + bj*block) += a(i + bi*block, k + bk*block) *
                                               t(j + bj*block, k + bk*block);
            }
          }
        }
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

    if (N % BLOCK != 0) {
      std::cout << "N must be evenly dividible by BLOCK: N=" << N
                << " BLOCK=" << BLOCK << std::endl;
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
