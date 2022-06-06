# Simple tasking

Explore tasking and data sharing with tasks

Starting from the skeleton code ([tasks.c](tasks.c) or
[tasks.F90](tasks.F90)), add an OpenMP parallel region to the code,
and start **tasks** so that each loop iteration is executed by a task.
At the end, the contents of `array` should be consistent with the
printouts from the tasks, *i.e.* array element `i` contains the id of 
the thread executing the task `i`, as an example:
```
Array at the beginning: 0 0 0 0 
Tasks created by 4
Task 0 executed by thread 0
Task 2 executed by thread 6
Task 3 executed by thread 4
Task 1 executed by thread 7
Array at the end: 0 7 6 4
```
Note that the output is generally different
between different runs of the code. 

Play around with different data sharing clauses (both for the parallel
region and for the tasks), and investigate how they affect the results.
What kind of clauses are needed for obtaining the results described above?
