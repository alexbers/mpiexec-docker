#!/bin/bash

ARGS="--privileged -v /dev/:/dev/ --network host -w /host/ --rm -e PMI_VERSION=2"

for env in $(printenv | grep -P '^(OMPI|OPAL|SLURMD?|MV2)_' | cut -d= -f 1); do
    ARGS="$ARGS -e $env"
done

docker run -i -v "$(pwd):/host/" $ARGS "$@"
