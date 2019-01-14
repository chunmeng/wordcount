#!/bin/bash

if [ -d "build" ]; then
    echo "Build existed, clean up to avoid conflict... "
    cmake --build ./build --target clean
fi

echo "Building... "
cmake -H. -Bbuild && \
cmake --build ./build && \
cmake --build ./build --target test



