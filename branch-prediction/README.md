<!--
SPDX-FileCopyrightText: 2021 CSC - IT Center for Science Ltd. <www.csc.fi>

SPDX-License-Identifier: CC-BY-4.0
-->

# Branch misprediction

The file `branch-misprediction.cpp` generates random numbers between 1 and 10, and 
calculates then the sum of all the values below 6. As the data is random, hardware branch
predictor has hardtime figuring out which branch is taken.

Try to sort the data before calling `test_memory`, does the performance improve? 
(effect can be seen better with moderate compiler settings, *i.e*. `-O1`)

Try to compare branch prediction related performance counters *e.g.* `perf stat -e branch-misses` for the two cases.

There is also a Fortran version, however, as there are no sorting routines in the standard library
implementing the sorting is more tedious here.
