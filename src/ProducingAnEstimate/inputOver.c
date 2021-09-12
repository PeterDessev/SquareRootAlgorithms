#include "ProducingAnEstimate/inputOver.h"

float inputOver(float input){
    if(input > 1)
        return input / 2;
    else if(input < 1) 
        return input * 2;
    // input must equal 1, adding this does not slow the other two down, but makes 
    // claculating the square root of 1 faster.
    else 
        return 1;
}