= MPI Benchmarks

The purpose of the example is to provide one more example how to build images and the software inside the images. 

Here we set compiler with CXX and CC vars and call make with -C option to specify the working directory. Also we add the directory with built files to the PATH var for convenience.

The MPI implementation MVAPICH 2.3 is used. It has Infiniband support.


= Build and Launch

```bash
docker build -t mpi-bench .
mpiexec_docker mpi-bench -np 4 IMB-MPI1
```

The example of distributed launch in Slurm on two nodes:

```bash
salloc -N 2 bash
docker build -t mpi-bench .
srun docker build -t mpi-bench .
mpiexec_docker mpi-bench IMB-MPI1
```

In Podman the *docker-archive:mpi-bench.img:mpi-bench* image name can be used to build the image only once and save as a file:
```bash
salloc -N 2 bash
docker build -t docker-archive:mpi-bench.img .
mpiexec_docker docker-archive:mpi-bench.img IMB-MPI1
```


