#!/bin/sh

if mpiexec --help 2>&1 | grep -q -- --allow-run-as-root; then
    exec mpiexec --allow-run-as-root "$@"
else
    exec mpiexec "$@"
fi
