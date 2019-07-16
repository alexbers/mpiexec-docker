FROM centos:7
RUN yum install -y mvapich23 mvapich23-devel make gcc-c++
ENV PATH /mpi-benchmarks-IMB-v2019.3/:/usr/lib64/mvapich23/bin:/usr/bin:/bin
ENV LD_LIBRARY_PATH /usr/lib64/mvapich23/lib
ENV CXX mpicxx
ENV CC mpicc
ADD https://github.com/intel/mpi-benchmarks/archive/IMB-v2019.3.tar.gz /
RUN tar xf /IMB-v2019.3.tar.gz
RUN make -C /mpi-benchmarks-IMB-v2019.3/
