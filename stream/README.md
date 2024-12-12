<!--
SPDX-FileCopyrightText: 2021 CSC - IT Center for Science Ltd. <www.csc.fi>

SPDX-License-Identifier: CC-BY-4.0
-->

# Main memory bandwidth

[Stream](https://www.cs.virginia.edu/stream/ref.html) is common benchmark for 
investigating the main memory bandwidth.

A version of stream is included in the [demos/stream](../demos/stream) directory.
Build the code with the provided Makefile and investigate main memory bandwidth
both in Puhti and Mahti (you may try also your own laptop or other HPC systems you
have access to).

- Run the code with a single thread / core, as well as with multiple threads / cores
  up to the full node (40 cores in Puhti, 128 cores in Mahti).
- With each thread count, try both `OMP_PROC_BIND=close` and `OMP_PROC_BIND=spread`
  thread affinity settings. Do you see differences in performance?
- What thread count / affinity gives the best performance?
- How close are the results to the theoretical peak bandwidth?
- Can you understant the behaviour of the main memory bandwidth in your investigations?

## NUMA configuration in CSC supercomputers

Both Mahti and Puhti nodes are dual socket systems, i.e. there is memory and a CPU is attached to
each socket. Even though all the memory within the node is shared, a CPU can access the memory
which is in the same socket faster.

In Mahti, a CPU is furthermore divided into 4 NUMA domains, so that the whole node contains 8 NUMA
domains, with 16 cores in each domain (https://docs.csc.fi/computing/systems-mahti/).

NUMA configuration can be investigated with the `numactl -H` command. Note that the login
and compute nodes might have different configurations.


