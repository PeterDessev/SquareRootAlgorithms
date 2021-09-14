// Detect if is being compiled on unix or unix-like system
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

#define DEBUG 1

// Array of functions for producing a guess
#define PROD_SIZE 4
static float(* producing[PROD_SIZE]) (float input) = {
    inputOver,
    oneAsAnEstimate,
    floatingPoint,
    inverseSquare
};

// Array of functions for iterating a guess
#define ITER_SIZE 4 
static float(* iterating[ITER_SIZE * 2]) (float input, float estimate) = {
    babylonian,
    goldschmidt,
    newton,
    halley,
    babylonianInverse,
    goldschmidtInverse,
    newtonInverse,
    halleyInverse
};


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

// These two arrays are used to easily convert 
// between the index for the address of a function
// and its actual name for printing purposes
static const char* prodNames[] = {
"Input Over S",
"One As An Estimate",
"Floating Point",
"Reciprocal Floating Point"
};
static const char* iterNames[] = {
"Babylonian",
"Goldschmidt",
"Newton",
"Halley"
};

static void printResults(long int results[PROD_SIZE][ITER_SIZE][TEST_OOM_RANGE][TEST_DIGIT_RANGE]);
static void printCSV(long int results[PROD_SIZE][ITER_SIZE][TEST_OOM_RANGE][TEST_DIGIT_RANGE]);

int main(){
#ifndef IS_UNIX
    printf("Unable to locate posix libraries, tests will now each take a whole number of seconds each to finish instead of %g seconds\n", BENCHMARK_TIME);
#endif

    time_t beginBenchmark;

    // This array stores the results of the benchmark
    long int results[PROD_SIZE][ITER_SIZE][TEST_OOM_RANGE][TEST_DIGIT_RANGE];


    // Begin testing
    // First loop to iterate through producing an estimate
    for(int prodIndex = 0; prodIndex < PROD_SIZE; prodIndex++){
        // Second loop to iterate through iterating on an estimate
        for(int iterIndex = 0; iterIndex < ITER_SIZE; iterIndex++){
            // Because the inverse square root method produces an estimate for the inverse square root,
            // a different set of functions is required to itareate over. They are contained in the
            // iterating function pointer array, but with an offset of 4 from their non-inverted counterparts
            int trueIterIndex = prodIndex == 3 ? iterIndex + 3 : iterIndex;
            
            float(* producer)(float) = producing[prodIndex];
            float(* iterator)(float input, float estimate) = iterating[trueIterIndex];

#if DEBUG >= 3
            printf("%s with %s:\n", prodNames[prodIndex], iterNames[iterIndex]);
#endif // DEBUG >= 3

            // Third loop dictates what order of magnitude input should be in
            for(int OOM = 0 - ((TEST_OOM_RANGE - 1) / 2); OOM <= ((TEST_OOM_RANGE - 1) / 2); OOM++){
                // Fourht loop dictates what digit within OOM input should be
                for(int digit = (10 / TEST_DIGIT_RANGE); digit < 10; digit += (10 / TEST_DIGIT_RANGE)){
                    double input = (double)digit * pow(10, (double)OOM);

#if DEBUG >= 4
                printf("Testing %s with %s, calculating the square root of %f for %f seconds...\n", prodNames[prodIndex], iterNames[iterIndex], input, BENCHMARK_TIME);
#endif // DEBUG >= 4
                    long int count = 0;

                    // Begin benchmark
#ifdef IS_UNIX 
                struct timeval tval_before, tval_after, tval_result;
                double timeSpent;

                gettimeofday(&tval_before, NULL);
                gettimeofday(&tval_after, NULL);

                timersub(&tval_after, &tval_before, &tval_result);

                timeSpent = (double)(long)tval_result.tv_sec + 
                    ((double)(long)tval_result.tv_usec) / (double)1000000;

                while(timeSpent < BENCHMARK_TIME){
                    gettimeofday(&tval_after, NULL);
                    timersub(&tval_after, &tval_before, &tval_result);
                    
                    timeSpent = (double)(long)tval_result.tv_sec + 
                        ((double)(long)tval_result.tv_usec) / (double)1000000;

#else // ifdef IS_UNIX 
                    // Start time
                    time(&beginBenchmark);
                    float estimate, result;
                    while(difftime(time(NULL), beginBenchmark) < (BENCHMARK_TIME)){
#endif // ifdef IS_UNIX 

                        estimate = (*producer) (input);
                        result = (*iterator) (input, estimate);
                        count++;
                    } // while(difftime ...

                    if(result == -1){
                        printf("ERROR: %s with %s unable to properly produce estimate for %.2e\n", prodNames[prodIndex], iterNames[iterIndex], input);
                        results[prodIndex][iterIndex][OOM + ((TEST_OOM_RANGE - 1) / 2)][digit] = -1;
                    }else{
                        results[prodIndex][iterIndex][OOM + ((TEST_OOM_RANGE - 1) / 2)][digit] = count;
#if DEBUG >= 1
                        printf("%s with %s for %.2e: %.2e (%.2e)\n", prodNames[prodIndex], iterNames[iterIndex], input, result, prodIndex != 3 ? (result * result) : ((1 / result) * (1 / result)));
#endif // if DEBUG >= 2
                    }

#if DEBUG >= 2
#ifdef IS_UNIX
                    printf("%lf\n", timeSpent);
#else
                    double bmTime = difftime(time(NULL), beginBenchmark);
                    printf("Time: %lf\n", bmTime);
#endif // ifdef IS_UNIX
#endif // if DEBUG >= 2

#if DEBUG >= 3
                    printf("%c with %c on %.1e: %ld\n", prodNames[prodIndex][0], iterNames[iterIndex][0], input, count);
#endif // if DEBUG >= 3

                } // for(int digit = 0 ...
            } // for(int OOM = 0 - ...
        } // for(int iterIndex = 0 ...
    } // for(int prodIndex = 0 ...

    // Output results
    printCSV(results);
    // printResults(results);
    return 0;
}

void printResults(long int results[PROD_SIZE][ITER_SIZE][TEST_OOM_RANGE][TEST_DIGIT_RANGE]){
    for(int prods = 0; prods < PROD_SIZE; prods++){
        for(int iters = 0; iters < ITER_SIZE; iters++){
            for(int OOM = 0 - ((TEST_OOM_RANGE - 1) / 2); OOM <= ((TEST_OOM_RANGE - 1) / 2); OOM++){
                for(int digit = (10 / TEST_DIGIT_RANGE); digit < 10; digit += (10 / TEST_DIGIT_RANGE)){
                    double input = (double)digit * pow(10, (double)OOM);
                    printf("%c with %c (%.2e): %ld\n", prodNames[prods][0], iterNames[iters][0], input, results[prods][iters][OOM + ((TEST_OOM_RANGE - 1) / 2)][digit]);
                }
            }
        }
    }
}


void printCSV(long int results[PROD_SIZE][ITER_SIZE][TEST_OOM_RANGE][TEST_DIGIT_RANGE]){
    FILE* csv;
    csv = fopen("output.csv", "w+");

    // Corner Cell empty
    fputs(",", csv);

    // Print out column headers
    for(int prods = 0; prods < PROD_SIZE; prods++){
        for(int iters = 0; iters < ITER_SIZE; iters++){
            fprintf(csv, "%s with %s,", prodNames[prods], iterNames[iters]);
        }
    }
    fputs("\n", csv);

    // Print row headers and data
    for(int OOM = 0 - ((TEST_OOM_RANGE - 1) / 2); OOM <= ((TEST_OOM_RANGE - 1) / 2); OOM++){
        for(int digit = (10 / TEST_DIGIT_RANGE); digit < 10; digit += (10 / TEST_DIGIT_RANGE)){
            // Print row header
            double header = (double)digit * pow(10, (double)OOM);
            fprintf(csv, "%.2e,", header);
        
            // Print data
            for(int prods = 0; prods < PROD_SIZE; prods++){
                for(int iters = 0; iters < ITER_SIZE; iters++){
                    long result = results[prods][iters][OOM + ((TEST_OOM_RANGE - 1) / 2)][digit];
                    if(result != -1)
                        fprintf(csv, "%ld", result);
                    fprintf(csv, ",");
                }
            }
            fputs("\n", csv);
        }
    }
    fclose(csv);
}