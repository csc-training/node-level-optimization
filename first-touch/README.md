# First touch memory policy

The file `laplacian.cpp` / `laplacian.F90` calculates Laplacian of two dimensional field.
The actual computation is parallalized with OpenMP, however, the initialization of arrays is
done serially by the master thread which can result in performance degradation in NUMA systems.

Modify the code so that also the initialization is done in parallel, and compare the performance
to the original code with different number of threads and thread binding options (`OMP_PLACES` and `OMP_PROC_BIND`). As NUMA effects are more pronounced in Mahti, it is recommended to carry out the
exercise first there, however, you might want to investigate also Puhti.

## NUMA configuration in CSC supercomputers

Both Mahti and Puhti nodes are dual socket systems, i.e. there is memory and a CPU is attached to 
each socket. Even though all the memory within the node is shared, a CPU can access the memory 
which is in the same socket faster.

In Mahti, a CPU is furthermore divided into 4 NUMA domains, so that the whole node contains 8 NUMA 
domains, with 16 cores in each domain (https://docs.csc.fi/computing/systems-mahti/). 



