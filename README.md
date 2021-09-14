# Square Root Algorithms

A testing program for several different methods of computing square roots in software.

## Paper
The paper to go along with this study is available here:

https://docs.google.com/document/d/1e1kNdTjHdQQyEId8orjOof3VnSAWD3e5kDFTlawNjvI/edit?usp=sharing

While reading is not required to understand any of the program, it still offers insights into the math behind each algorithm, and anaylsis on the results

## Build
To build the project use the make command in the project root directory

    make

The program has been tested working on Ubuntu and Windows 10, but not MacOS

## Overview of Algorithms and Testing

The algorithms in this paper are split into two categories

- Estimate Production
- Estimate Iteration

Each estimate producing algorithm is paired with every estimate iterating algorithm and given a set ammount of time to calculate the square root of the same number as many times as possible. Inputs are logarithmically dispersed across 21 powers of ten to allow for different algorithms to show where they are strong and where they are weak.

Algorithms that produce an estimate do not contain a loop. They have the same execution time for any input, and have no check for accuracy.

Algorithms that iterate on a guess function on a loop. The loop continually runs until a certain accuracy threshold is reached. Every method that iterates on a guess contains an almost identical check algorithm, so one algorithm does not get an advantage over another due to a check algorithm. 

### Estimate Production

- One as an estimate
- Input Over
- Floating Point Estimation
- Inverse Floating Point Estimation

### Estimate Iteration

- Babylonian Method
- Goldschmidt Equations
- Halley's Method
- Newton's Method

## Results

By default, the results are output to a CSV file, however, data can also be printed or output raw in a text file.

## Debug

By default the DEBUG flag in `main.c` is set to 0. This means that only when an algorithm does not properly compute the square root will a message be printed in standard out. Setting the DEBUG flag to 1 will print both errors and results of algorithms that successfully computed the square root. DEBUG levels 2-4 send extra information to standard out that are either redundant or not useful to the end user.