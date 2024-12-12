<!--
SPDX-FileCopyrightText: 2021 CSC - IT Center for Science Ltd. <www.csc.fi>

SPDX-License-Identifier: CC-BY-4.0
-->

# Thread pinning for heat equation solver

The two dimensional heat equation solver here is memory bound. In Mahti,
the memory bandwidth per core, and sometimes also performance is improved
when the node is undersubscribed, i.e. all the cores are not used.

Build the code with the provided Makefile
```
make
```
If you want try different compilers load the corresponding module and provide `COMP`
variable for the Makefile
```
module load clang
make COMP=clang
```
(Note that for this exercise the compiler should make no difference).

With the default input data, single node performance in Mahti is best (although by a 
small margin) with 8 MPI tasks and 4 OpenMP threads (i.e using only 32 cores). Thread/process 
affinity can, however, have a large impact on perfomance. Try to run the code first with the 
settings
```
...
#SBATCH --ntasks-per-node=8
#SBATCH --cpus-per-task=4

export OMP_AFFINITY_FORMAT="Process %P level %L thread %0.3n affinity %A"
export OMP_DISPLAY_AFFINITY=true
export OMP_NUM_THREADS=4
srun ./heat_hybrid
```

How does the affinity look?

Next, try to place the MPI tasks more evenly by having `ntasks_per_node x cpus_per_task = 128`.
Can you explain the difference in the performance?

Then, try to pin the threads with `OMP_PLACES=cores` and investigate the effect of different
`OMP_PROC_BIND` settings. Pay attention to how affinity affects performance.

In CSC's Slurm configuration oversubscribing the cores by MPI tasks is not easy by accident, but
it is possible when SMT is enabled by the Slurm option `--hint=multithread`. Try the following 
Slurm settings, and pay attention to affinity and performance:
```
...
#SBATCH --ntasks-per-node=32
#SBATCH --cpus-per-task=4
#SBATCH --hint=multithread

export OMP_AFFINITY_FORMAT="Process %P level %L thread %0.3n affinity %A"
export OMP_DISPLAY_AFFINITY=true
export OMP_NUM_THREADS=4
srun ./heat_hybrid
```

Can you figure out how to fix the performance problem?


