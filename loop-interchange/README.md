<!--
SPDX-FileCopyrightText: 2021 CSC - IT Center for Science Ltd. <www.csc.fi>

SPDX-License-Identifier: CC-BY-4.0
-->

# Loop interchange

The file `laplacian.cpp` / `laplacian.F90` calculates Laplacian of a two
dimensional field. The main computational part contains a simple performance
bug. Try to compile the code with different compilers and check whether they
can automatically fix the performance. You can use `-fopt-info-loop` (gcc),
`-Rpass=loop*` (clang), or `-qopt-report` (Intel) to get an optimization
report.

Do you get a similar performance with all the compilers? You can also check
if the optimization level (`O1`, `O2`, `O3`) has an effect.

The file `laplacian_matrix.cpp` / `laplacian_type.F90` contains a version
where the fields are implemented in a more complex data structure. Does this
data structure affect compiler optimizations?

Try to fix the performance bug in the second version manually, and compare
the performance to the initial version with simple arrays.
