**Genetic Algo (genetic_algo)**
===============================
This repository contains a generic implementation of [Genetic Algorithm](https://en.wikipedia.org/wiki/Genetic_algorithm) written in C++11. This code is meant to be used in almost any problem domain, as long as the problem specific part of the code is implemented by the user. The "**util**" folder is provided for beginners and other users who want to minimize their effort on implementations that are commonly used in most of the problems.

## Repository Contents
- A template of simple Genetic Algorithm
- An example for solving N-Queen problem using simple GA
- Implementation of some common crossover operators

## Read more:
- [Run Demo](run-demo)
	- [C++ Compiler](c-compiler)

### Run Demo
For testing you can run demo from **src/examples**.

#### C++ Compiler
It requires at least a C++11 compliant compiler as it uses C++11 library for random number generation.

For GNU compiler, use:

```
g++ -std=c++11 ..
```
or
```
g++ -std=c++0x ..
```
