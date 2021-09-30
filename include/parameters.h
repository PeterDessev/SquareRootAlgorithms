#pragma once
// Debug levels:
// -1: print nothing
// 0: print when a test fails
// 1: print what pair was tested with what input and what the result was
#define DEBUG 0

// The name of the file the program outputs data to
#define OUTPUT_NAME "output.csv"

// The way that data will be output
// outputCSV: outputs data to a file OUTPUT_NAME in CSV format
// printResults: print the results to std out
#define OUTPUT_METHOD outputCSV

// Fine control over the testing range in a log friendly way
// NOTE: The program has not been tested with any values other than these
// and is not constructed in a way that accounts for user modification,
// change at your own risk!!
// TEST_OOM_RANGE controls how many orders of magnitude (centered at 0)
// the test will cover. Must be odd, even numbers have not been tested
#define TEST_OOM_RANGE 21

// TEST_DIGIT_RANGE controls how many evenly spaced digits will be tested 
// within each order of magnitude, preferably a multiple of 10
#define TEST_DIGIT_RANGE 10


// This variable controls how mnay seconds the 
// program will give each permutation of algorithms
// to compute as many square roots as possible
#define BENCHMARK_TIME 0.1f

// The number of estimate producing algorithms
#define PROD_SIZE 4

// The number of estimate iterating algorithms
#define ITER_SIZE 4 

// These two arrays are used to easily convert 
// between the index for the address of a function
// and its actual name for printing purposes
extern const char* prodNames[PROD_SIZE];
extern const char* iterNames[ITER_SIZE];

// Array of functions for producing a guess
extern float(* producing[PROD_SIZE]) (float input);

// Array of functions for iterating a guess
extern float(* iterating[ITER_SIZE * 2]) (float input, float estimate);

