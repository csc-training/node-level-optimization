#include <cstdio>
#include <omp.h>
#include <vector>

#define NX 11000
#define NY 11000

int main()
{

  constexpr int niters = 50;

  int nx = NX;
  int ny = NY;

  // Use static to ensure allocation from heap; allocation from stack can segfault
  static double A[NX][NY];
  static double L[NX][NY];

  double dx = 1.0 / double(nx);
  double dy = 1.0 / double(ny);

  // Initialize arrays
#pragma omp parallel firstprivate(dx, dy)
{
  double x, y;
  #pragma omp for 
  for (int i = 0; i < nx; i++)
      for (int j = 0; j < ny; j++)
        {
          x = i*dx;
          y = j*dy;
          A[i][j] = x*x + y*y;
          L[i][j] = 0.0;
        }
}

  double t0 = omp_get_wtime();
  // Compute Laplacian
#pragma omp parallel
  for (int iter = 0; iter < niters; iter++)
    #pragma omp for 
    for (int i = 1; i < nx-1; i++)
      #pragma omp simd
      for (int j = 1; j < ny-1; j++)
        L[i][j] = (A[i-1][j] - 2.0*A[i][j] + A[i+1][j]) / (dx*dx) +
	           (A[i][j-1] - 2.0*A[i][j] + A[i][j+1]) / (dy*dy);

  double t1 = omp_get_wtime();

  // Check the result
  double meanL = 0.0;
  for (int i = 1; i < nx-1; i++)
    for (int j = 1; j < ny-1; j++)
      meanL += L[i][j];

  meanL /= ((nx - 1) * (ny - 1));

  printf("Numerical solution %6.4f\n", meanL);
  printf("Analytical solution %6.4f\n", 4.0);

  printf("Time %7.4f\n", t1 - t0);

  return 0;
}
