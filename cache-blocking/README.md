# Optimizing matrix multiplication

The file `matmul.cpp` / `matmul.F90` contains a naive implementation of
matrix-matrix multiplication, which has very inefficient cache usage. Try to
improve the performance by

 1. Creating a transposed copy of one of the source matrices. This will allow
    both right hand side matrices in the innermost loop to be traversed
    contiguously
 2. Implement cache blocking for the computational loop
