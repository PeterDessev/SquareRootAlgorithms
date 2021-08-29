// Detect if is being compiled on unix
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
#define IS_UNIX
#endif

#ifdef IS_UNIX
#include <sys/time.h>
#endif
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "include/roots.h"

#define DEBUG 0
// Array of functions for producing a guess
static int prodSize = 4;
static float(* producing[]) (float input) = {
    inputOver,
    oneAsAnEstimate,
    floatingPoint,
    inverseSquare
};

// Array of functions for iterating a guess
static int iterSize = 3; 
static float(* iterating[]) (float input, float estimate) = {
    goldschmidt,
    newton,
    halley,
    goldschmidtInverse,
    newtonInverse,
    halleyInverse
};


// These two arrays are used to easily convert 
// between the index for the address of a function
// and its actual name for printing purposes
static char* prodNames[] = {
"Input Over S",
"One As An Estimate",
"Floating Point",
"Reciprocal Floating Point"
};
static char* iterNames[] = {
"Goldschmidt",
"Newton",
"Halley"
};

static void printResults(long int results[prodSize][iterSize][21]);

int main(){
    time_t beginBenchmark;
    time_t endBenchmark;

    double seconds;

    // This variable controls how mnay seconds the 
    // program will give each permutation of algorithms
    // to compute as many square roots as possible
    static const double benchmarkTime = 0.1;

    // This array stores the results of the benchmark
    long int results[prodSize][iterSize][21];


    // Begin testing
    // First loop to iterate through producing an estimate
    for(int prodIndex = 0; prodIndex < prodSize; prodIndex++){
        // Second loop to iterate through iterating on an estimate
        for(int iterIndex = 0; iterIndex < iterSize; iterIndex++){
            // Helper for storing results, more reliable than log10(input)
            int inputIndex = 0; 

            // Because the inverse square root method produces an estimate for the inverse square root,
            // a different set of functions is required to itareate over. They are contained in the
            // iterating function pointer array, but with an offset of 4 from their non-inverted counterparts
            int trueIterIndex = prodIndex == 3 ? iterIndex + 3 : iterIndex;
            
            float(* producer)(float) = producing[prodIndex];
            float(* iterator)(float input, float estimate) = iterating[trueIterIndex];

#if DEBUG >= 2
            printf("%s with %s:\n", prodNames[prodIndex], iterNames[iterIndex]);
#endif // DEBUG >= 2
            // Third loop dictates what number to find the square root of
            for(float input = 1E-10; input < 1E10; input *= 10){
#if DEBUG >= 3
                printf("Testing %s with %s, calculating the square root of %f for %f seconds...\n", prodNames[prodIndex], iterNames[iterIndex], input, benchmarkTime);
#endif // DEBUG >= 3
                long int count = 0;

                // Begin benchmark
#ifdef IS_UNIX 
                struct timeval tval_before, tval_after, tval_result;
                double timeSpent;

                gettimeofday(&tval_before, NULL);
                gettimeofday(&tval_after, NULL);

                timersub(&tval_after, &tval_before, &tval_result);

                timeSpent = (double)(long)tval_result.tv_sec + 
                    ((double)(long)tval_result.tv_usec )/ (double)1000000;

                while(timeSpent < benchmarkTime){
                    gettimeofday(&tval_after, NULL);
                    timersub(&tval_after, &tval_before, &tval_result);
                    
                    timeSpent = (double)(long)tval_result.tv_sec + 
                        ((double)(long)tval_result.tv_usec )/ (double)1000000;

#else // ifdef IS_UNIX 
                // Start time
                time(&beginBenchmark);

                while(difftime(time(NULL), beginBenchmark) < benchmarkTime){
#endif // ifdef IS_UNIX 
                    float estimate = (*producer) (input);
                    float result = (*iterator) (input, estimate);
                    count++;
                }
                results[prodIndex][iterIndex][inputIndex++] = count;

#if DEBUG >= 1
#ifdef IS_UNIX
                printf("%lf\n", timeSpent);
#else
                double bmTime = difftime(time(NULL), beginBenchmark);
                printf("%lf\n", bmTime);
#endif // ifdef IS_UNIX
#endif // if DEBUG >= 1

#if DEBUG >= 2
                printf("%c with %c on %.1e: %ld\n", prodNames[prodIndex][0], iterNames[iterIndex][0], input, count);
#endif // if DEBUG >= 2
            }
        }
    }
    printResults(results);
    return 0;
}

void printResults(long int results[prodSize][iterSize][21]){
    for(int prods = 0; prods < prodSize; prods++){
        for(int iters = 0; iters < iterSize; iters++){
            for(int oom = 0; oom < 21; oom++){
                double input = pow(10, (double)(oom - 10));
                printf("%c with %c (%.2e): %ld\n", prodNames[prods][0], iterNames[iters][0], input, results[prods][iters][oom]);
            }
        }
    }
}
