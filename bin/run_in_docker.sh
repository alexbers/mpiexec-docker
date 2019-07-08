#!/bin/bash

ARGS="--network host -w /host/ --rm -e PMI_VERSION=2"
ARGS="$ARGS -e MV2_SMP_USE_CMA=0 -e OMPI_MCA_btl_vader_single_copy_mechanism=3"

if [ -c /dev/infiniband/rdma_cm -a -c /dev/infiniband/uverbs0 ]; then
    ARGS="$ARGS --device /dev/infiniband/rdma_cm --device /dev/infiniband/uverbs0"
fi

for env in $(printenv | grep -P '^(OMPI|OPAL|SLURMD?|MV2)_' | cut -d= -f 1); do
    ARGS="$ARGS -e $env"
done

docker run -i -v "$(pwd):/host/" $ARGS "$@"
