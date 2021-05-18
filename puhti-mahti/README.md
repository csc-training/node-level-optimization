# Getting started with CSC supercomputers

Make sure you can log in to Puhti and Mahti (if you are interested
only in one type of CPUs you can use just that system). Create your
private scratch directory along the [general instructions](../exercise-instructions.md) and clone the course github repository there.

Try to run `lspcu` both on the login node (just `lscpu` in command
line), and in a compute node, i.e. via batch job script (`srun
lscpu`). Are the CPUs the same?

Investigate the NUMA configuration in Mahti:
```
module load numactl
numactl -H
```
Try both login and compute node.

You can try to run the `peak` and `stream` microbenchmarks also in
Puhti and Mahti, how do the results compare with the specifications?

