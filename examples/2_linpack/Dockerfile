FROM centos:7
RUN yum install -y mvapich23 numactl
ENV PATH /usr/lib64/mvapich23/bin:/usr/bin:/bin
ENV LD_LIBRARY_PATH /usr/lib64/mvapich23/lib
ADD http://registrationcenter-download.intel.com/akdlm/irc_nas/9752/l_mklb_p_2018.3.011.tgz /
RUN tar xf /l_mklb_p_2018.3.011.tgz
RUN rm /l_mklb_p_2018.3.011.tgz
COPY exp1 exp2 /bin/
COPY HPL.dat /l_mklb_p_2018.3.011/benchmarks_2018/linux/mkl/benchmarks/mp_linpack/
