# Compiler options

## Optimization reports

| Compiler    |  Basic report     | Extensive report |
| ----------- | ------------------|------------------|
| GNU         | `-fopt-info`      | `-fopt-info-all` |
| Intel       | `-qopt-report`    | `-qopt-report=5` |
| Clang       | `-Rpass=.*`       | `-Rpass=.*`      |

Specific reports for example with `-fopt-info-loop`,
`-fopt-info-loop-all`, `-Rpass=loop*`. See compiler manuals for more
details.

## Vectorization

| Compiler    |  AVX2     | AVX512 | Host |
| ----------- | ------------------|------------------|
| GNU/Clang         | `-mavx2`      | `-mavx512f -mprefer-vector-width=512` | `-march=native`
| Intel       | `-xCORE-AVX2`    | `-xCORE-AVX512 -qopt-zmm-usage=high` | `-XHost` |

When using OpenMP vectorization directives, OpenMP options `-fopenmp` (GNU/Clang) or `-qopenmp` 
(Intel) are needed.



