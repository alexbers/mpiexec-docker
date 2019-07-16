# mpiexec-docker

The goal of this project is to simplify the building and running of distributed programs by using containers. Containers provide a predictable environment to get reproducible results and keep the build instructions short.

We focus on MPI technology for distributing programming. The main script, called `mpiexec_docker`, runs the MPI task as one or more containers. We support Open MPI, MPICH, MVAPICH2 and Intel MPI out of the box.

The distributed programs can be executed on HPC clusters. We pay attention to these peculiarities of such systems:

- workload managers — we integrate with Slurm
- high-speed interconnect — we integrate with InfiniBand
- users without superuser rights — we use Podman, the Docker-compatible container engine that doesn't need superuser rights

## Usage
Usually, MPI programs are started like this: 
```bash
mpiexec -np 2 /root/hello
```

With `mpiexec_docker` it looks similar:
```bash
mpiexec_docker alexbers/mpiexec-docker-example:exp0 -np 2 /root/hello
```

The image will be downloaded automatically.

If Slurm is used on a cluster, the programs can be started this way:
```bash
sbatch -n 2 mpiexec_docker alexbers/mpiexec-docker-example:exp0 /root/hello
```

More examples are in the */examples* dir.

## Getting Started
On all hosts:
1. Install and configure Docker or Podman, Podman is better for rootless. The [instructions](https://github.com/containers/libpod/blob/master/install.md)
2. Install an inotifywait util. It is available in inotify-tools pkg on Ubuntu and CentOS (in the EPEL repo)
3. Copy all scripts from the _bin_ directory to any directory in your PATH

## Image preparation

No specific image preparation required. The MPI should be installed in the container. Some distros, like CentOS, doesn't place MPI binaries and libraries in standard pathes, so these pathes should be specified with PATH and LD_LIBRARY_PATH environment variables.

The Dockerfile example to build and run Open MPI tasks:

```
FROM centos:7
RUN yum install -y openmpi openmpi-dev gcc
ENV PATH /usr/lib64/openmpi/bin:/usr/bin:/bin
ENV LD_LIBRARY_PATH /usr/lib64/openmpi/lib
```

## Docker vs Podman

Podman has two killer-features which makes it recommended:
1. It supports a rootless mode. Docker support for the rootless mode hasn't released yet
2. It can build an image and store it as a file with a single command. Storing images as files is convinient on clusters where the file system is shared between nodes. Docker requires some extra steps to export and import images.

## How it works

When the _mpiexec_docker_ runs a program on a single node the things are straightforward. It calls docker run, passing a set of parameters:

- current directory is maped as /host in the container
- MPI-specific environment variables are passed inside the container
- if InfiniBand devices are detected, they are also passed inside the container. Other devices like GPUs are also passed.

However there are one thing to keep in mind: old Open MPI refuse to run as the root user unless --allow-run-as-root argument is specified. The container engine maps the current user to the root using namespaces, actually not giving him additional rights. Open MPI not able to see this. To solve this problem the _mpiexec_choose.sh_ is mapped into container and launched instead of the original mpiexec. This scripts detects Open MPI and adds the option if it is needed

The *distributed task launch* is more tricky. The mpiexec calls programs like *ssh* for remote launching. However, if it detect Slurm-specific environment variables, it calls *srun* instead. But srun, if installed, needs to authenticate on slurm controller, which usually done with munge daemon.

Instead of copying srun with libraries and munge unix sockets in the container, the tool provides means to run the host's srun command from the containers. This is done by mapping the *run_on_host.sh* script as /usr/bin/srun inside the container. This script communicates with host using files shared between the container and host. The script sends a command to run on host and the host executes it and returns the result code.

The program on the remote host should be launched in the container. The *run_on_host.sh* script modifies the command, pasting a *run_in_docker.sh* script before the program name. The *run_in_docker.sh* script runs the command in the container.

The *mpiexec_docker* can be integrated with workload managers by mapping *run_on_host.sh* to the desired program path, e.g. */usr/bin/ssh*.

**Important: by design, the MPI launch inside the container is no more secure than without the container.** The project focuses on the reproducibility and performance instead of providing an additional security.
