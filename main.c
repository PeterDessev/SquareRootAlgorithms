#include <stdio.h>
#include <time.h>

#include "include/roots.h"

#define DEBUG

int main(){
    time_t beginBenchmark;
    time_t endBenchmark;

    double seconds;

    // This variable controls how many times the program will run the algorithm
    // for each permutation of producers, iterators, and inputs
    static const int benchmarkCount = 1000;

    // These two arrays are used to easily convert 
    // between the index for the address of a function
    // and its actual name for printing purposes
    char* prodNames[] = {
        "inputOver",
        "oneAsAnEstimate",
        "floatingPoint",
        "inverseSquare"
    };

    char* iterNames[] = {
        "Goldschmidt",
        "newton",
        "halley"
    };

    // Array of functions for producing a guess
    int prodCount = 4;
    int(* producing[]) (float input) = {
        inputOver,
        oneAsAnEstimate,
        floatingPoint,
        inverseSquare
    };

    // Array of functions for iterating a guess
    int iterCount = 3; 
    int(* iterating[]) (float input, float estimate) = {
        goldschmidt,
        newton,
        halley,
        goldschmidtInverse,
        newtonInverse,
        halleyInverse
    };


    // Begin testing
    // First loop to iterate through producing an estimate
    for(int prodIndex = 0; prodIndex < prodCount; prodIndex++){
        // Second loop to iterate through iterating on an estimate
        for(int iterIndex = 0; iterIndex < iterCount; iterIndex++){
            // Third loop dictates what number to find the square root of
            for(float input = 1E-10; input < 1E10; input *= 10){
#ifdef DEBUG
                printf("Testing %s with %s, calculating the square root of %f 1000 times...\n", prodNames[prodIndex], iterNames[iterIndex], input);
#endif
                // Because the inverse square root method produces an estimate for the inverse square root,
                // a different set of functions is required to itareate over. They are contained in the
                // iterating function pointer array, but with an offset of 4 from their non-inverted counterparts
                int trueIterIndex = prodIndex == 3 ? iterIndex + 4 : iterIndex;
                int(* producer)(float) = producing[prodIndex];
                int(* iterator)(float) = iterating[trueIterIndex];

                // Start time
                time(&beginBenchmark);

                for(int count = 0; count < benchmarkCount; count++){
                    float estimate = (*producer) (input);
                    float result = (*iterator) (estimate);
                }
                
                // End time
                time(&endBenchmark);
                seconds = difftime(beginBenchmark, endBenchmark);

                printf("It took %lf seconds for %s with %s to finish calculating the square root of %f 1000 times\n\n", seconds, prodNames[prodIndex], iterNames[iterIndex], input);
            }
        }
    }

    return 0;
}