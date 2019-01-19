# Instruction

## About the App
A sample app for word freq count given an ascii text file

## Reference/Credits
Here are some open source works referenced when creating this project.

- https://gitlab.kitware.com/cmake/community/wikis/doc/ctest/Testing-With-CTest
- https://github.com/Crascit/DownloadProject

And of course the ever so helpful stackoverflow's contributors.

## Required packages
The build host is assumed Ubuntu 16.04. the following packages are required.
* build-essential - this contains all libraries and toolchain needed to build the project
* cmake - the project use cmake to create cross-platform makefile/project configuration file
* git - the project is committed in git, and use git to pull google-test for unit testing

Use the following command to install the package on a clean host.
```
sudo apt-get install -y --no-install-recommends \
build-essential \
cmake \
git
```

## Build Instructions
A convenient script is created to generate the app and execute the test.

### Using host environment to build
This requires the build tools and libraries to be installed on the host machine.
It can be invoked with:
```
./build.sh
```

### Using docker container
Alternatively, if docker is available, use this script to build in docker container.
It can be invoked with:
```
./build_with_docker.sh
```

This build the docker image (Ubuntu 16.04) with necessary tools installed, and invoke the build script
from the docker container.

### Output and Run
The executable program is created in ./build/src/. The program executable is named **wordfreq**.
To run the program:
```
./build/src/wordfreq -f <input filepath> -n N
```
e.g. assuming moby.txt is located in current directory
```
./build/src/wordfreq -f moby.txt -n 20
```

## Manual Build Steps

1. Generate the out of source Makefiles
```
// with cmake (< 3.13)
cmake -H. -Bbuild
// For cmake (> 3.13): cmake -S . -B build
```

2. Build the executable and test binaries
```
cmake --build ./build
```

## Unit Test

1. The test binaries are produced in build/test/, which can be generated with
   (done as part of the build.sh) and executed with
   - Run the test
    ```
    cmake --build ./build --target test
    ```

2. Alternatively
   - Each can be runs individually
    ```
    ./build/test/<TestBinary>
    ```
   - Or using ctest (Need to change directory)
    ```
    cd build && ctest -V
    ```
   - Or using make with target under project root directory
    ```
    make -C ./build test
    ```

## Clean Up
To clean up the build output without removing the makefiles generated, do
```
cmake --build ./build --target clean
```

To completely remove the build artifacts, do
```
rm -rf build/
```