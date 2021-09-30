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
#include "output.h"

int main(){
    // If the system is not compiled on Unix with Posix support, the more
    // grainular Posix timing library is not available, only the C time
    // library which can only time whole second values
#ifndef IS_UNIX
    printf("Unable to locate posix libraries, tests will now each take a whole number of seconds each to finish instead of %g seconds\n", BENCHMARK_TIME);
    time_t beginBenchmark;
#endif

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
            int trueIterIndex = prodIndex == (PROD_SIZE - 1) ? iterIndex + ITER_SIZE : iterIndex;
            
            // Get the producing and iterating algorithms
            float(* producer)(float) = producing[prodIndex];
            float(* iterator)(float input, float estimate) = iterating[trueIterIndex];

            // Third loop dictates what order of magnitude input should be in
            for(int OOM = 0 - ((TEST_OOM_RANGE - 1) / 2); OOM <= ((TEST_OOM_RANGE - 1) / 2); OOM++){
                // Fourht loop dictates what digit within OOM input should be
                for(int digit = (10 / TEST_DIGIT_RANGE); digit < 10; digit += (10 / TEST_DIGIT_RANGE)){
                    double input = (double)digit * pow(10, (double)OOM);
                    long int count = 0;
                    char check;
                    float estimate, result;

                    // Check that the algorithm can produce a result
                    estimate = (*producer) (input);
                    result = (*iterator) (input, estimate);
                    check = iterIndex == trueIterIndex ? 
                        fabs(1 - (result * result) / input) > 0.1f :
                        fabs(1 - result * result * input) > 0.1f;

                    // Begin benchmark if algorithm performs correctly
                    if(result != -1 && !check){
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
                        while(difftime(time(NULL), beginBenchmark) < (BENCHMARK_TIME)){
#endif // ifdef IS_UNIX 
                            estimate = (*producer) (input);
                            result = (*iterator) (input, estimate);
                            count++;
                        } // while(difftime ...

                        results[prodIndex][iterIndex][OOM + ((TEST_OOM_RANGE - 1) / 2)][digit] = count;
#if DEBUG >= 1
                        printf("%s with %s for %.2e: %.2e (%.2e)\n", prodNames[prodIndex], iterNames[iterIndex], input, result, prodIndex != 3 ? (result * result) : ((1 / result) * (1 / result)));
#endif // if DEBUG >= 1
                    }else{ // if(result != -1 && !check)
#if DEBUG >= 0
                        printf("ERROR: %s with %s unable to properly produce estimate for %.2e\n", prodNames[prodIndex], iterNames[iterIndex], input);
#endif // if DEBUG >= 0
                        results[prodIndex][iterIndex][OOM + ((TEST_OOM_RANGE - 1) / 2)][digit] = -1;
                    } // if(result != -1 && !check)
                } // for(int digit = 0 ...
            } // for(int OOM = 0 - ...
        } // for(int iterIndex = 0 ...
    } // for(int prodIndex = 0 ...

    // Output results
    OUTPUT_METHOD(results);
    return 0;
}