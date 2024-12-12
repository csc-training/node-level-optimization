<!--
SPDX-FileCopyrightText: 2021 CSC - IT Center for Science Ltd. <www.csc.fi>

SPDX-License-Identifier: CC-BY-4.0
-->

# Matrix multiplication parallelized with tasks

One possible way to parallelize matrix multiplication is to divide the
whole computation into blocks, and have each block calculated by a
single task. The code [matmul.c](matmul.c) performs the blocking,
parallelize the code by adding appropriate tasking directives. Hint:
there can be dependencies between blocks.
