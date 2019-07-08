FROM centos:7
RUN yum install -y openmpi openmpi-devel gcc
ENV PATH /usr/lib64/openmpi/bin:/usr/bin:/bin
ENV LD_LIBRARY_PATH /usr/lib64/openmpi/lib
COPY bandwidth.c /root/
RUN mpicc /root/bandwidth.c -o /root/bandwidth
