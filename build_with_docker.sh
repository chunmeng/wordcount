#!/bin/bash

IMAGE_NAME='builder'

# Build the docker build container image
docker build --network=host docker/ -t ${IMAGE_NAME}

# Currently the build process pull the googletest from github and requires
# cacerts to be installed on container. 
# This line below serves this purpose: -v /etc/ssl/certs:/etc/ssl/certs \
# This however requires the host machine to have similar certs style as the container (not portable)
# Have not figure out a better way
echo "Building project with docker image: ${IMAGE_NAME}"
docker run --rm -it \
    --net host \
    -v `pwd`:/src \
    -v /etc/ssl/certs:/etc/ssl/certs \
    -i ${IMAGE_NAME} \
    /src/build.sh