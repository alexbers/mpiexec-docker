FROM centos:7
RUN yum install -y mvapich23
ENV PATH /usr/lib64/mvapich23/bin:/l_mklb_p_2019.4.003/benchmarks_2019/linux/mkl/benchmarks/mp_linpack/:/usr/bin:/bin
ENV LD_LIBRARY_PATH /usr/lib64/mvapich23/lib
ADD https://software.intel.com/sites/default/files/managed/ee/cd/l_mklb_p_2019.4.003.tgz /
RUN tar xf /l_mklb_p_2019.4.003.tgz
