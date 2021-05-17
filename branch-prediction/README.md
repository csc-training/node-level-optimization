# Branch misprediction

The file `branch-misprediction.cpp` generates random numbers between 1 and 10, and 
calculates then the sum of all the values below 6. As the data is random, hardware branch
predictor has hardtime figuring out which branch is taken.

Try to sort the data before calling `test_memory`, does the performance improve (compile only with
moderate optimization settings)?

There is also a Fortran version, however, as there are no sorting routines in the standard library
implementing the sorting is more tedious here.
