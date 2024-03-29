# General exercise instructions

Hands-on exercises can be done in CSC's Puhti and Mahti
supercomputers. Some exercises you may want to try also on your local
workstation / laptop.

## Exercise material

Part of the exercise material is in this GitHub repository, which you
can download with

```
git clone https://github.com/csc-training/node-level-optimization.git
```

If you have a GitHub account you can also **Fork** this repository and
clone then your fork. 

Intel exercise material is not publicly available, but can be found
in the CSC supercomputers during the course.

## Using own workstation

In order to use your own computer, a C/C++ and Fortran compilers are
needed, for example GNU compilers.

We recommended to install also Intel OneAPI toolkits and AMD uProf
performance analysis tool.

### Installing Intel OneAPI

Intel OneAPI toolkits include compilers, high performance libraries,
as well as performance analysis tools. We recommend to install both
the base toolkit, as well as the HPC toolkit (note that Fortran
compiler is included only in the HPC toolkit). Both toolkits provide
various installation options, and can be installed also with normal
user priviliges.

The Base toolkit can be downloaded from
https://software.intel.com/content/www/us/en/develop/tools/oneapi/base-toolkit/download.html

The HPC toolkit can be downloaded from
https://software.intel.com/content/www/us/en/develop/tools/oneapi/hpc-toolkit/download.html

There are also getting started guides:

- [Getting started with Base
  toolkit](https://software.intel.com/content/www/us/en/develop/documentation/get-started-with-intel-oneapi-base-linux/top.html)
- [Getting started with HPC
  toolkit](https://software.intel.com/content/www/us/en/develop/documentation/get-started-with-intel-oneapi-hpc-linux/top.html)
  
### Installing AMD uProf

AMD uProf performance analysis tool can be downloaded from
https://developer.amd.com/amd-uprof/

## Using CSC supercomputers

General instructions on using Mahti and Puhti can be found in [CSC user
documentation](https://docs.csc.fi/computing/overview/).

CSC's Mahti and Puhti supercomputers can be accessed via ssh using the
provided username (`trainingxxx`) and password:
```
ssh -Y training000@puhti.csc.fi
```
or
```
ssh -Y training000@mahti.csc.fi
```

For editing program source files you can use e.g. *nano* editor :

```
nano prog.f90
```
(`^` in nano's shortcuts refer to **Ctrl** key, *i.e.* in order to save file and exit editor press `Ctrl+X`).
Also other editors (*vi*, *emacs*) are available.

CSC supercomputers use **module** system for managing software
environments such as different compilers. You can see the current
modules with
```
module list
```

For graphical user interfaces we recommend to use the Puhti Web Interface:

- Go to puhti.csc.fi using a web browser and login using your training user account (same username and password you use when connecting with ssh).
- Start the [Desktop application](https://docs.csc.fi/computing/webinterface/desktop/)
- Open Terminal by double clicking the **Host terminal** in the desktop


### Disk areas

All the exercises in the supercomputers should be carried out in the
**scratch** disk area. The name of the scratch directory can be
queried with the command `csc-workspaces`. As the base directory is
shared between members of the project, you should create your own
directory:
```
cd /scratch/project_2000745/node_level_optimization_2022
mkdir -p $USER
cd $USER
```

### Batch jobs

The login nodes in Mahti and Puhti should be used only for compilation
and looking at the performance analysis results. All the runs need to
be done via the batch system. In order to minimize queuing time, a set
of nodes has been reserved during the course days at 09:00 - 17:00 (EEST).
Jobs can be submitted to reservation with
```
sbatch --reservation=training_tue job-script.sh
sbatch --reservation=training_wed job-script.sh
sbatch --reservation=training_thu job-script.sh
```

See **Puhti** and **Mahti** sections below for job script templates.

### Using Puhti

Puhti has GNU and Intel compiler suites available via modules as
```
module load gcc
```
or
```
module load intel
```
The Intel module contains the 19.0 compiler version, however, for this
course we recommend that you use a **test installation** of the more recent
Intel OneAPI, which can be activated as:
```
module purge
module load gcc
source /appl/opt/oneapihpc-2022.2/setvars.sh
```
(Note that once the latest OneAPI is installed in production
enviroment this installation will be removed).

When running OpenMP programs via the batch job system, one needs to use the `--cpus-per-task` Slurm option and the `OMP_NUM_THREADS` environment variable. 
Simple job running with 4 OpenMP threads can be submitted with the following batch job script:
```
#!/bin/bash
#SBATCH --job-name=example
#SBATCH --account=project_2000745
#SBATCH --partition=small
#SBATCH --time=00:05:00
#SBATCH --ntasks=1
#SBATCH --exclusive
#SBATCH --cpus-per-task=4

export OMP_NUM_THREADS=4  # or export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
srun ./my_exe
```

#### Performance analysis with Intel VTune

When using VTune, the collection of the performance results should be
done via batch system using the command line mode of VTune, e.g.
```
#SBATCH ...
srun vtune -collect performance-snapshot -- ./my_exe
```
You can get the corresponding command line from the VTune GUI, and
copy-paste it directly after `srun` in the batch job script.

Once the collection is finished, you can **Open** the results in VTune
GUI, which can be started with (for GUI we recommend to use the 
[Desktop app](https://docs.csc.fi/computing/webinterface/desktop/) in the Puhti web interface)
```
vtune-gui &
```
For example, the above collection command would create a directory
`r000ps` (each subsequent collection creates a new directory, you can
check Slurm output `slurm-xxxxx.out` for the name) which can be opened in the GUI.
You can also copy the full `r000ps` directory into your local laptop, 
and examine the results with VTune GUI there.

### Using Mahti

Mahti has GNU and AMD suites available via modules as
```
module load gcc
```
and
```
module load clang
```

Intel compiler is currently not supported by CSC in Mahti. There is, however, 
 similar **test installation** of Intel OneAPI as in Puhti:
```
module purge
module load gcc
source /appl/opt/oneapi2022.1.2/setvars.sh
```
Note that some Intel compiler options produce binaries that cannot be run on AMD CPUs.


When running OpenMP programs via the batch job system, one needs to use the `--cpus-per-task` Slurm option and the `OMP_NUM_THREADS` environment variable. 
Simple job running with 32 OpenMP threads can be submitted with the following batch job script:
```
#!/bin/bash
#SBATCH --job-name=example
#SBATCH --account=project_2000745
#SBATCH --partition=medium
#SBATCH --time=00:05:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=32

export OMP_NUM_THREADS=32  # or export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
srun my_exe
```

#### Performance analysis with AMD uprof

The AMD uprof is available as module, and can be loaded with
```
module load amduprof
```

When using AMD uprof, the collection of the performance results should be
done via batch system using the command line mode with the
`AMDuProfCLi` command. Kernel priviliges required by AMD uprof are available only in the "training" reservations.

```
#SBATCH ...

srun AMDuProfCLI collect --config tbp -o $PWD/prof-$SLURM_JOBID ./my_exe
```
Available performance analysis configurations can be listed with 
```
AMDuProfCLI info --list collect-configs
```

The profile is stored in the directory
specified with `-o`, and it can be opened with AMD uProf GUI:
```
AMDuProf &
```
followed by "Import Session". 

You can also copy the full directory into your local laptop, and examine the results
with AMDuProf there.



