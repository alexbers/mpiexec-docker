# mpiexec-docker

The `mpiexec_docker` script runs the MPI task on the cluster as a container. This gives reproducible environment and simpler program distribution.

Usually, the MPI program is started like this: 
```bash
mpiexec -np 2 ./task
```

With `mpiexec_docker` it looks similar:
```bash
mpiexec_docker my_image -np 2 ./task
```

Many clusters have a Slurm workload manager. The task can be started this way:
```bash
sbatch -n 2 mpiexec_docker my_image ./task
```

It works without root access if you install podman instead of docker. The podman is docker-compatible tool from RedHat.

Supported MPIs:
- Open MPI
- MPICH
- MVAPICH2
- Intel MPI

## Getting Started ##
1. Install and configure Docker or Podman on the cluster, Podman is better for rootless
2. Install a inotifywait util. It is available in inotify-tools pkg in CentOS 7 (EPEL) or similar
3. Copy scripts from the _bin_ directory to any directory in your PATH
