---
title:  A look into modern CPU architecture
author: CSC Training
date:   2024-05
lang:   en
---

# Modern CPU core {.section}

# von Neumann architecture

<div class=column>
- A CPU core is still largely based on the von Neumann model
    - sequency of operations (instructions) performed on given data
    - instructions and data are fetched from memory into registers in CPU
    - ALU performs operations on data in registers
    - Result is stored back to memory
- From an external point of view, operations are executed sequentially
</div>
<div class=column>

<!--Image copyright By Kapooht - Own work, CC BY-SA 3.0, -->
![](https://upload.wikimedia.org/wikipedia/commons/e/e5/Von_Neumann_Architecture.svg){.center width=60%}

</div>


# Modern CPU core

<div class=column>
- Internally, each core is highly complex
- **Superscalar out-of-order** instruction execution
- **SIMD** instructions
- Multiple levels of hierarchical **cache memory**
</div>
<div class=column>

<!-- Image copyright Public Domain -->
![](https://en.wikichip.org/w/images/f/f2/zen_2_core_diagram.svg){.center width=45%}

</div>

# How CPU core operates?

- Clock frequency determines the pace at which CPU works
- Zero to **N** instructions start at each clock cycle
- Instruction latency = number of clock cycles that are required for
  completing the execution
- Instruction throughput = number of clock cycles to wait before
  starting same kind of instruction again
    - Throughput can be much smaller than the latency
    - Sometimes given as cycles per instruction (CPI) or its inverse, instructions per cycle (IPC)

# Fetch-decode-execute cycle

<div class=column>
- Instructions are executed in stages
- Fetch (F): control unit fetches instruction from memory
- Decode (D): decode the instruction and determine operands
    - Instructions are broken into uops
- Execute (E): perform the instruction 
    - Utilize ALU or access memory
- Enables simpler logic and **pipelining** the operations
</div>
<div class=column>

![](img/front-vs-backend.png){.center width=50%}
</div>
  
# Pipelining

- Instruction execution and arithmetic units can be *pipelined*
    - Instruction execution: work on multiple instructions
      simultaneously
    - Arithmetic units: execute different stages of a an instruction
      at the same time in an assembly line fashion
    - Together: one result per cycle after the pipeline is full
- Within the pipeline, hardware can execute instructions in different 
 order than they were issued (**out-of-order** scheduling)
- Requires complicated software (compiler) and hardware
   to keep the pipeline full
- Conditional branches can cause the pipeline to stall
        
# Pipelining: example

<div class=column>
- Wind-up and wind-down phases: no instructions retired
- First result available after 5 cycles, total time 7 cycles compared
  to 15 cycles without a pipeline
- Real pipeline in modern CPU cores can be much more complex
</div>

<div class=column>
![](https://simplecore-ger.intel.com/techdecoded/wp-content/uploads/sites/11/figure-2-3.png){.center width=70%}
</div>

# Superscalar execution

<div class=column>
- Hardware Instruction Level Parallelism (ILP)
- Multiple instructions per cycle issued to the multiple execution
  units
- Hardware data dependency resolution preserve sequential execution
  semantics
    - Actual execution may be out-of-order
- Pipelining and superscalar execution allow instruction throughputs
less than one

</div>

<div class=column>

<!-- Image copyright CSC, see LICENSE -->
![](img/ilp.svg){.center width=60%}

</div>

# Latency, throughput, and concurrency

- In order to keep the pipeline full and multiple execution units fully utilized, 
  there needs to be enough independent instructions that can be run concurrently
- Little's law
$$
\textrm{Concurrency} = \textrm{Latency} \times \textrm{Throughput}
$$
- Example: vector fused multiply add (vfma) in Intel Cascade Laked
    - latency 4 cycles, throughput 2 IPC
    - minimum of eight independent instructions are needed to achieve maximum throughput

# Vectorization

- Modern CPUs have SIMD (Single Instruction, Multiple Data) units and instructions 
    - Operate on multiple elements of data with single instructions
- AVX2 256 bits = 4 double precision numbers
- AVX512 512 bits = 8 double precision numbers
    - single AVX512 fused multiply add instruction can perform 16 FLOPS

<br>
<!-- Image copyright CSC, see LICENSE -->
![](img/simd.svg){.center width=70%}
  
# Cache memory

<div class=column>
- In order to alleviate the memory bandwidth bottleneck, CPUs have multiple levels of cache memory
    - when data is accessed, it will be first fetched into cache
    - when data is reused, subsequent access is much faster
- L1 cache is closest to the CPU core and is fastest but has smallest capacity
- Each successive level has higher capacity but slower access
</div>

<div class=column>
<!-- Image copyright CSC, see LICENSE -->
![](img/memory_hierarchy.svg){.center width=90%}
</div>

  
# Symmetric Multithreading (SMT)

<div class=column>
- It is difficult to fill-in all the available hardware resources in a 
  CPU core
    - Pipeline stalls due to main memory latency, I/O, etc.
- To maximize hardware utilization, several hardware threads can be executed on a single core
    - Seen as logical cores by OS
- Benefits depend on the application, and SMT can also worsen the performance
</div>
  
<div class=column>
<!-- Image copyright CSC, see LICENSE -->
![](img/smt.svg){.center width=70%}
</div>


# Multicore CPU schematic

<div class=column>
- The multicore CPU is packeted in a socket
- Typically, L1 and L2 caches are private per core, and L3 cache is shared 
  between set of cores
- All cores have shared access to the main memory
</div>

<div class=column>
<!-- Image copyright CSC, see LICENSE -->
![](img/multicore-schematic.svg){.center width=60%}
</div>

# Cache coherency

<div class=column>
- With private caches per core, hardware needs to ensure that the data is consistent between the cores
- When a core writes to a cache, CPU may need to update the caches of other cores
    - Possibly expensive operation
</div>

<div class=column>
<!-- Image copyright CSC, see LICENSE -->
![](img/cache-coherency.svg){.center width=50%}
</div>
   
# NUMA architectures

<div class=column>
- A node can have multiple sockets with memory attached to each socket
- Non Uniform Memory Access (NUMA)
    - All memory within a node is accessible, but latencies and bandwidths vary
- Hardware needs to maintain cache coherency also between different NUMA nodes (ccNUMA)
</div>

<div class=column>
<!-- Image copyright CSC, see LICENSE -->
![](img/numa-schematic.png){.center width=70%}
</div>

# Summary

- Modern multicore CPUs are complex beasts
- In order to maximally utilize the CPU, application needs to:
    - use multiple threads (or processes)
    - utilize caches for feeding data to CPU at fastest possible pace
    - keep the pipeline full and utilize instruction level parallelism
    - use vector instructions for maximizing FLOPS per instruction

# Web resources

- Detailed information about processor microarchitectures: 
    - <https://en.wikichip.org/wiki/WikiChip>
    - <https://uops.info/>
- Agner's optimization resources <https://www.agner.org/optimize/>
    
    
