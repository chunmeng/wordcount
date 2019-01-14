# word-freq-assignment
A simple app for word freq count

# Reference/Credits
Here are some opensource works referenced when creating this project.

- https://gitlab.kitware.com/cmake/community/wikis/doc/ctest/Testing-With-CTest
- https://github.com/Crascit/DownloadProject (with older cmake)
- https://gist.github.com/johnb003/65982fdc7a1274fdb023b0c68664ebe4 (with newer cmake 3.9)

And ofcourse the ever so helpful stackoverflow.

# Build step

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

3. The executable binary is under build/src/

4. The test binary is under build/test/
   - Run the test
    ```
    cmake --build ./build --target test
    ```

- Alternatively
   - It can be runs individually
    ```
    ./build/test/Test
    ```
   - Or using ctest (Need to change directory)
    ```
    cd build && ctest -V
    ```
   - Or using make with target under project root directory
    ```
    make -C ./build test
    ```