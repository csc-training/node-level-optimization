# Investigating performance limits

Investigate the performance limits of your own workstation.

Linux command `lscpu` can be used for finding information about the
CPU. Try to find specs for your particular system, and determine the
theoretical limits of peak floating point performance and memory
bandwidth. 

In [demos](../demos) there are some microbenchmarks for testing the
system limits, try to run [peak](../peak) and [stream](../stream) 
microbenchmarks, what kind of performance do you see with them?

Try to make a roofline graph for your system, by using e.g. the
provided `plot_roofline.py` Python script under [tools](../tools).
