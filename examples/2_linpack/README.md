= Linpack

The purpose of the example is to show how to build images with complex software and changable config.

The HPL.dat is the config. It can be changed without the image rebuilding.

The MPI implementation MVAPICH 2.3 is used. It has Infiniband support.


= Build and Launch

```bash
docker build -t linpack .
mpiexec_docker linpack -ppn 1 -np 1 xhpl_intel64_dynamic
```

The example of distributed launch in Slurm on two nodes:

```bash
salloc -N 2 bash
docker build -t linpack .
srun docker build -t linpack .
mpiexec_docker linpack -ppn 1 -np 2 xhpl_intel64_dynamic
```

In Podman the *docker-archive:linpack.img:linpack* image name can be used to build the image only once and save as a file:
```bash
salloc -N 2 bash
docker build -t docker-archive:linpack.img .
mpiexec_docker docker-archive:linpack.img -ppn 1 -np 2 xhpl_intel64_dynamic

```


