<!--
SPDX-FileCopyrightText: 2021 CSC - IT Center for Science Ltd. <www.csc.fi>

SPDX-License-Identifier: CC-BY-4.0
-->

# Investigating performance limits

Investigate the performance limits of your own workstation.

Linux command `lscpu` can be used for finding information about the
CPU. Try to find specs for your particular system, and determine the
theoretical limits of peak floating point performance and memory
bandwidth. 

In [demos](../demos) there are some microbenchmarks for testing the
system limits, try to run [peak](../demos/peak) and [stream](../demos/stream) 
microbenchmarks, what kind of performance do you see with them?

Both microbenchmarks have `Makefile` which by default uses gcc. Clang or Intel compiler
can be chosen with
```
make COMP=clang
```
or
```
make COMP=intel
```

In `peak` benchmark, one issues `NUM_OPS` independent operations (fused multiply adds, 
multiplications, or additions). If `NUM_OPS` is too small, pipeline cannot be kept filled 
all the time, if it is too large operands cannot be kept in registers all the time 
(as there won't be enough registers). Investigate how `NUM_OPS` (specified in the `Makefile`) affects performance (*e.g.* with values like 4, 8, 12, 18, 34)

Try to make a roofline graph for your system, by using e.g. the
provided `plot_roofline.py` Python script under [tools](../tools).
