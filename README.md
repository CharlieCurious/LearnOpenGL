# Learn OpenGL with C

Trying to go through [LearnOpenGL](https://learnopengl.com) using C exclusively.

## Build

Set up CMake:

You can setup the build to compile tests and use debug symbols, or to be optimized.

### To compile tests and use debug symbols use (default)

`cmake -S . -B <your-build-directory> -DENABLE_TESTING=ON`

or just

`cmake -S . -B <your-build-directory>`

### To compile with optimization use

`cmake -S . -B <your-build-directory> -DENABLE_TESTTING=OFF`

## Build 

You can build with tests and debug symbols or with optimization.

`cmake --build <your-build-directory>`

## Test
`ctest --test-dir <your-build-directory>`

optionally your can use the `-V` to print the results of each indivitual test function, and `-T memcheck` to run valgrind.