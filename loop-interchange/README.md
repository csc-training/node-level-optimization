# Loop interchange

The file `laplacian.cpp` / `laplacian.F90` calculates Laplacian of two dimensional field.
The main computational part contains a simple performance bug. Try to compile the code with 
different compilers and check whether they can automatically fix the performance. You can use 
`-fopt-info-loop` (gcc), `-Rpass=loop*` (clang), or `-qopt-report` (Intel) for optimization reports.
Do you get similar performance with all compilers? You can check also the effect of optimization 
level (`O1`, `O2`, `O3`).

The file `laplacian_matrix.cpp` / `laplacian_type.F90` contains a version where the fields are
implemented in a more complex data structures? Does this data structure affect compiler 
optimizations?

Try to fix the performance bug in second version manually, and compare the performance to the 
version with simple arrays.
