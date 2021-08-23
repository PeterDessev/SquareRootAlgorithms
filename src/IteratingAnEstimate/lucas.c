#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "IteratingAnEstimate/lucas.h"

typedef struct __lucasSeries{
    long double current;
    long double previous;
    long double preprevious;
} lucasSeries;

float lucas(float input, float estimate){
    lucasSeries* test;
    double result, check, P, Q;

    test->current = 1;
    test->previous = 0;
    P = 2;
    Q = 1 - input;
    check = 0;

    while(check < 0.9999 || check > 1.0001){
        test->preprevious = test->previous;
        test->previous = test->current;
        test->current = P * test->previous - Q * test->preprevious;

        // Prevent double overflow
        if(test->current > 1E5){
            test->current /= 1 << 30;
            test->previous /= 1 << 30;
        }

        result = test->current / test->previous - 1;
        check = (result * result) / input;
    }
    
    return result;
}

float lucasInverse(float input, float estimate){
    printf("LUCAS INVERSE NOT YET IMPLEMENTED\n");
    return 0.0f;
}