#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "IteratingAnEstimate/goldschmidt.h"

float goldschmidt(float input, float estimate){
    double R, G, H, check;
    int count = 0;

    //estimate = 1 / estimate;
    G = input * estimate;
    H = estimate / 2;

    while((check < 0.9999f || check > 1.0001f) && count < 100){
        R = 0.5 - G * H;
        G = G + G * R;
        H = H + H * R;
        check = (G * G) / input;
        count++;
    }
    if(count == 99)
        return -1;
    
    return G;
}

float goldschmidtInverse(float input, float estimate){
    double R, G, H, check;

    G = input * estimate;
    H = estimate / 2;

    while(check < 0.9999f || check > 1.0001f){
        R = 0.5f - G * H;
        G = G + G * R;
        H = H + H * R;

        check = (4.0f * H * H) * input;
    }

    return 2 * H;
}