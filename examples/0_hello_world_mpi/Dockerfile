FROM alpine:3.10
RUN apk add --no-cache -X http://dl-cdn.alpinelinux.org/alpine/edge/testing openmpi openmpi-dev gcc libc-dev
COPY hello.c /root/
RUN mpicc /root/hello.c -o /root/hello
