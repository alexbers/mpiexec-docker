#!/bin/sh

(
INJ=0
printf "%s" "$0 "
for ARG; do
    NAME="$(basename -- "$ARG")"
    case $NAME in
        hydra_pmi_proxy|orted|hydra_bstrap_proxy|pmi_proxy)
            [ $INJ -eq 0 ] && printf "%s" "run_in_docker.sh $IMAGE "; INJ=1;;
    esac
    printf "'"; printf "%s" "$ARG" | sed "s/'/'\\\\''/g"; printf "' "
done
) >> /tmp/host_cmd

while [ ! -s /tmp/host_ret ]; do sleep 1; done
exit "$(cat /tmp/host_ret)"
