#include <stdio.h>

#include "IteratingAnEstimate/halley.h"

float halley(float input, float estimate){
    float estimateSquare, numerator, denominator, check = 0;

    while(check < 0.9999 || check > 1.0001){
        estimateSquare = estimate * estimate;
        numerator = estimateSquare - input;
        denominator = 3 * estimateSquare + input;

        estimate = estimate - 2 * estimate * (numerator / denominator);
        
        check = (estimate * estimate) / input;
    }

    return estimate;
}

float halleyInverse(float input, float estimate){
    float estimateSquared, numerator, denominator, check = 0;

    while(check < 0.9999 || check > 1.0001){
        estimateSquared = estimate * estimate;
        numerator = estimateSquared * estimate * input + 3 * estimate;
        denominator = 3 * estimateSquared * input + 1;

        estimate = (numerator / denominator);
    
        check = (estimate * estimate) * input;
    }
    return estimate;
}