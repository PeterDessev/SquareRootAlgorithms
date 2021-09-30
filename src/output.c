#include <stdio.h>
#include <math.h>

#include "output.h"

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


void outputCSV(long int results[PROD_SIZE][ITER_SIZE][TEST_OOM_RANGE][TEST_DIGIT_RANGE]){
    FILE* csv;
    csv = fopen(OUTPUT_NAME, "w+");

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