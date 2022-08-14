#!/bin/bash

echo "Building OstentatiousOptimizer Docker Image"
sudo docker build --tag ostentatiousoptimizer .

test $? -eq 0 || { echo "OstentatiousOptimizer Docker image did not build."; exit 1; };

echo "Running OstentatiousOptimizer Docker Image"
sudo docker run --interactive --tty --rm \
    --volume `pwd`:/OstentatiousOptimizer \
    --name OstentatiousOptimizer \
    ostentatiousoptimizer
