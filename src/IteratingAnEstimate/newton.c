#include <stdio.h>

#include "IteratingAnEstimate/newton.h"

float newton(float input, float estimate){
    float check = 0;

    while(check < 0.9999 || check > 1.0001){
        estimate = 0.5f * estimate + (input / (2 * estimate));
        check = (estimate * estimate) * input;
    }

    return estimate;
}

float newtonInverse(float input, float estimate){
    float inputOver2 = 0.5f * input;
    float check = 0;

    while(check < 0.9999 || check > 1.0001){
        estimate = estimate * (1.5f - inputOver2 * estimate * estimate);
        check = (estimate * estimate) * input;
    }

    return estimate;
}