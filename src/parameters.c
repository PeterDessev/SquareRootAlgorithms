#include "parameters.h"
#include "roots.h"

// Array of functions for producing a guess
// IMPORTANT: inverseSquare MUST be the last element
// in the array
float(* producing[PROD_SIZE]) (float input) = {
    inputOver,
    oneAsAnEstimate,
    floatingPoint,
    inverseSquare
};

// Array of functions for iterating a guess
float(* iterating[ITER_SIZE * 2]) (float input, float estimate) = {
    babylonian,
    goldschmidt,
    newton,
    halley,
    babylonianInverse,
    goldschmidtInverse,
    newtonInverse,
    halleyInverse
};

// These two arrays are used to easily convert 
// between the index for the address of a function
// and its actual name for printing purposes
const char* prodNames[PROD_SIZE] = {
    "Input Over S",
    "One As An Estimate",
    "Floating Point",
    "Reciprocal Floating Point"
};

const char* iterNames[ITER_SIZE] = {
    "Babylonian",
    "Goldschmidt",
    "Newton",
    "Halley"
};