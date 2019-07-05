# mpiexec-docker

The goal of this project is to simplify distributed programs building and running by using containers. Containers provide a predictable environment to get reproducible results and keep the build instructions short.

The main script, called `mpiexec_docker`, runs the MPI task as containers. We support Open MPI, MPICH, MVAPICH2 and Intel MPI out of the box.

The distributed programs can be executed on HPC clusters. We pay attention to these peculiarities of such systems:

- workload managers are used. We integrate with Slurm
- high-speed interconnect is used. We integrate with InfiniBand
- users don't have superuser rights. We use Podman, the Docker-compatible container engine that doesn't need superuser rights

## Usage
Usually, MPI programs are started like this: 
```bash
mpiexec -np 2 ./task
```

With `mpiexec_docker` it looks similar:
```bash
mpiexec_docker my_image -np 2 ./task
```

On a cluster with Slurm the programs can be started this way:
```bash
sbatch -n 2 mpiexec_docker my_image ./task
```

## Getting Started ##
1. Install and configure Docker or Podman on the cluster, Podman is better for rootless
2. Install a inotifywait util. It is available in inotify-tools pkg in CentOS 7 (EPEL) or similar
3. Copy scripts from the _bin_ directory to any directory in your PATH
