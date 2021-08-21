#include <stdio.h>

#include "IteratingAnEstimate/newton.h"

float newton(float input){
    float S = 100;
    float E = 1;
    for(int i = 0 ; i < 10; i++){
        E = 0.5f * E + (S / (2 * E));
    }
    printf("%f\n", E);
}