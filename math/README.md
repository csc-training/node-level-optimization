# Replacing division with multiplication

The file `laplacian.cpp` / `laplacian.F90` calculates Laplacian of two dimensional field.
The numerical formula contains divisions within the main computational loop. In floating 
point arithemetic `x / y != x * (1/y)`, so by default compilers won't replace the division by
multiplication. Try to compile the code with "fast math" options, do you get better performance?
Try to replace the division also manually with multiplication, how does the performance compare
to the original version with and without "fast math" compilation?

Note! In real world applications there is possibility for a loss in precision, so it is import
to check that results remain correct
