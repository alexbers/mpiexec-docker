FROM ubuntu:18.04
RUN apt-get update
RUN apt-get install -y mpich libmpich-dev
COPY hello.c /root/
RUN mpicc /root/hello.c -o /root/hello
