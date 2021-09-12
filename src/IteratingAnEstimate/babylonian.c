#include "IteratingAnEstimate/babylonian.h"

float babylonian(float input, float estimate){
    float check = 0;

    while(check < 0.9999 || check > 1.0001){
        estimate = 0.5f * (estimate + input / estimate);
        check = (estimate * estimate) / input;
    }
    return estimate;
}

float babylonianInverse(float input, float estimate){
    float inputInverse = 1 / input, check = 0;

    while(check < 0.9999 || check > 1.0001){
        estimate = 0.5f * (estimate + inputInverse / estimate);
        check = (estimate * estimate) * input;
    }
    return estimate;
}