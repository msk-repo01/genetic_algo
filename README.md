**Genetic Algorithm (genetic_algo)**
====================================
This repository contains a generic implementation of [Genetic Algorithm](https://en.wikipedia.org/wiki/Genetic_algorithm) written in C++11. This code is meant to be used in almost any problem domain, as long as the problem specific part of the code is implemented by the user. The "**util**" directory is provided for beginners and other users who want to minimize their effort on implementations that are commonly used in most of the problems.



## Repository Contents

- A template of simple Genetic Algorithm
- An example for solving N-Queen problem using simple GA
- An example of general mathematical function minimizer (2-variables) using simple GA
    - Examples of using function minimizer to minimize
        - Cross-In-Tray function
        - McCormick function
        - Schaffer N.4 function
- Implementation of some common crossover operators



## Read more:

- [Run Demo](#run-demo)
	- [C++ Compiler](#c-compiler)
	- [Use CMake](#use-cmake)
- [Solve another Problem](#solve-another-problem)



### Run Demo

For test you can run demos from **src/examples**. You can compile and run demos individually. If you want to run all the demos then you can also use **cmake**.



#### C++ Compiler

It requires at least a C++11 compliant compiler as it uses C++11 library for random number generation and for some of its other features.

For GNU compiler, use:

```
g++ -std=c++11
```
or
```
g++ -std=c++0x
```



#### Use CMake

To build demos together if you want to use cmake, then run the cmake and select the root directory **genetic_algo** as your directory for source code. Once your Makefile (or other build system file) is generated then run make (or other build system command) to generate executables. The executables would be inside **bin** directory of your build directory.

For running a **Mccormick function** demo on a Linux machine, it would look something like this on a commandline :

```sh
cd /path/to/genetic_algo

mkdir build
cd build

# generate Makefile using parent directory
# "genetic_algo" as the source directory
cmake ../

# run make to compile/link
make

# execute mccormick_demo that is inside "bin" directory
bin/mccormick_demo
```



## Solve another Problem

If you have a different function to minimize or a different problem to solve then check its wiki page to learn to write your own GA using the existing simple GA.

