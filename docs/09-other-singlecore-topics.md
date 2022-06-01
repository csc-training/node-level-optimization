---
title:  Miscellaneous single core optimizations
author: CSC Training
date:   2022-06
lang:   en
---

# Outline

- Loop transformations
- Mathematical routines
- Branches
- Function inlining
- Intrinsic functions

# Loop transformations {.section}

# Loop transformations

- Loop transformations can provide better vectorization prospects, improve 
  instruction level parallelism, pipeline utilization and cache usage
- Common transformations: interchange, unrolling, fusion, fission, sectioning,
  unroll and jam
- In many cases compiler can make loop transformations with high
  enough optimization level
    - Understanding the concepts is still be useful for the programmer
- In some cases manual programming can be useful
    - When misused, transformation can be disadvantageous for performance
        - Readability of code often suffers

# Loop unrolling

<div class=column>
- If the loop body is very small, overhead from incrementing the loop counter
  and from the test for the end of the loop can be high
- When vectorizing, loop is implicitly unrolled by the vector length
- May improve pipeline utilization and instruction level parallelism
- Additional logic needed for remainder
- May increase register pressure

</div>
<div class=column>
```fortran
do i=1,N
  c[i] = a[i] + b[i]
end do
```
```fortran
do i=1,N,4  ! unroll four times
  c[i] = a[i] + b[i]
  c[i+1] = a[i+1] + b[i+1]
  c[i+2] = a[i+2] + b[i+2]
  c[i+3] = a[i+3] + b[i+3]
end do
```
</div>

# Loop fission

<div class=column>
- Loop fission (or loop distribution) splits one loop into sequence of loops
- May improve cache usage and reduce register pressure
- May allow vectorization by moving dependencies 
- Some dependencies may prohibit fission
</div>
<div class=column>
```fortran
do j=1,N
  b(i) = a(i) * a(i)
  d(i) = c(i) - d(i-1)    ! flow dependency
end do
```
<br>
```fortran
do j=1,N  ! vectorization possible
  b(i) = a(i) * a(i)
end do
do j=1,N
  d(i) = c(i) - d(i-1)
end do
```
</div>

# Loop fusion

<div class=column>
- Loop fusion (or loop jamming) merges multiple loops into one
- May improve cache usage 
- May allow better pipeline utilization and instruction level parallelism
- May cause dependencies which prevent applying the transformation
</div>
<div class=column>
```fortran
do j=1,N
  b(i) = a(i) * a(i)
end do
do j=1,N
  c(i) = c(i) * a(i) 
end do
```
<br>
```fortran
do j=1,N
  b(i) = a(i) * a(i)
  c(i) = c(i) * a(i) 
end do
```
</div>

# Loop sectioning

<div class=column>
- Loop sectioning (or strip mining) transforms a loop into smaller chunks by 
  creating additional inner loops
- May improve cache usage
- May make the code easier for compiler to vectorize
</div>
<div class=column>
```fortran
do i=1,N
  process1(data(i))
  process2(data(i))
end do
```
<br>
```fortran
do i=1,N,S
  do j=i, min(N, i + S)
     process1(data(i))
  end do
  do j=i, min(N, i + S)
    process2(data(i))
  end do
end do
```
</div>

# Loop unroll and jam

<div class=column>
- Unroll and jam unrolls an outer loop and fuses then the inner loop 
- May allow better pipeline utilization and instruction level parallelism
- May potentiate other optimizations
</div>
<div class=column>
<small>
```fortran
do i=1,N  
  do j=1,M
    b = 2 * a(i, j) 
	c(i,j) = b * b
  end do
end do
```
<br>
```fortran
do j=1,N,2
  do i=1,M
    b1 = 2 * a(i, j)
	b2 = 2 * a(i, j + 1)
	c(i, j) = b1*b1
	c(i, j + 1) = b2*b2
  end do
end do

```
</small>
</div>

# Other optimizations {.section}

# Optimizing mathematical operations

- Due to finite precision of floating point numbers, compilers need to
  be carefull in some optimizations 
  $$(a + b) + c \neq a + (b + c)$$
- Some mathematical routines (`sqrt`, `pow`, `sin`, `cos`, ...) can be
  calculated with different algorithms with different performance and
  precision
    - In some applications it is possible to compromise precision for speed
- Most compilers have an option for faster mathematics 
  ('`-ffast-math`' for gcc/clang and '`-fp-model fast=2`' for Intel)
    - Important to check that results are valid !
	  
# Optimizing mathematical operations

<div class=column>
- If *fast math* options cannot be use (*i.e.* part of the application 
  requires higher precision), programmer can make some optimizations by hand
- Examples:
    - Move division out of the loop
	- Replace `pow(x, n)` where `n` is small integer with multiplications 
	  (C/C++)
</div>
<div class=column>
<small>
```fortran
do i=1, n
  do j=1, m
    L(i,j) = (A(i-1,j) - 2.0*A(i,j) + A(i+1,j)) / dx**2 + &
             (A(i,j-1) - 2.0*A(i,j) + A(i,j+1)) / dx**2
  end do
end do
```
<center> vs. </center>
```fortran
idx2 = 1.0 / dx**2
do i=1, n
  do j=1, m
    L(i,j) = (A(i-1,j) - 2.0*A(i,j) + A(i+1,j)) * idx2 + &
             (A(i,j-1) - 2.0*A(i,j) + A(i,j+1)) * idx2
  end do
end do
```
<br>
```c++
double x3 = x*x*x  // instead of pow(x, 3)
```
</small>
</div>


# Optimizing branches

- Branches have the possibility of stalling the CPU pipeline, and can thus be 
  expensive
- When possible, `if` statements should be outside loop bodies
    - manual loop transformations can be helpful
- Hardware branch predictor works well when the branching follows 
  regular pattern
    - performing extra work for improving predictability may be worthwhile

# Inline functions

- When inlining, compiler replaces a call to function by the function body
    - Reduces function call overhead
	- If function is called within a loop, may provide additional optimization 
	  prospects
- Compiler uses heuristics to decide if inlining is beneficial
    - Might require "interprocedural optimization" options
- In C/C++ `inline` keyword is *hint* for the compiler to inline
- In Fortran, programmer can force inlining only via compiler directives, 
  otherwise compiler makes the decision whether to inline a function 
- Overuse of inlining increases the executable size and may hurt performance
  
# Intrinsic functions

- Intrinsic functions are special functions that the compiler replaces with 
  equivalent CPU instruction
    - "high level assembly"
	- Often compiler specific
- Examples:
    - Software prefetch: `_mm_prefetch` (C/C++), `mm_prefetch` (Fortran)
	- Non-temporal stores: `_mm_stream_xxx` (C/C++ only)
	- AVX instructions
- Recommended only in special cases
    - Can make the code non-portable
	- Can also degragade performance - compiler might know better when to use

# Summary

- Loops can be transformed in various ways in order to improve
  performance
    - Often better leave the transformations for the compiler
- Many mathematical operations can be performed faster with some
  compromise on precision
- Hard to predict branches may stall the CPU pipeline

# Web resources

- Intel Intrinsics guide: <https://software.intel.com/sites/landingpage/IntrinsicsGuide/>

