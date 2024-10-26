# Learn OpenGL with C

Trying to go through [LearnOpenGL](https://learnopengl.com) using C exclusively.

## Build

Set up CMake:

You can setup the build to compile tests and use debug symbols, or to be optimized. You must also set the CHAPTER variable to tell cmake which chapter example to compile, i.e. getting_started/shaders.

### To compile tests and use debug symbols use (default)

`cmake -S . -B <your-build-directory> -DENABLE_TESTING=ON -DCHAPTER=<chapter-to-compile>`

or just

`cmake -S . -B <your-build-directory> -DCHAPTER=<chapter-to-compile>`

### To compile with optimization use

`cmake -S . -B <your-build-directory> -DENABLE_TESTTING=OFF -DCHAPTER=<chapter-to-compile>`

## Compile

You can compile with tests and debug symbols or with optimization.

`cmake --build <your-build-directory>`

## Test

`ctest --test-dir <your-build-directory>`

optionally your can use the `-V` to print the results of each indivitual test function, and `-T memcheck` to run valgrind.
