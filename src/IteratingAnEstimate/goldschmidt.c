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

    return count == 99 || isnan(G) || isinf(G) ? -1 : G;
}

float goldschmidtInverse(float input, float estimate){
    double R, G, H, check;
    int count = 0;

    //estimate = 1 / estimate;
    G = input * estimate;
    H = estimate / 2;

    while((check < 0.9999f || check > 1.0001f) && count < 100){
        R = 0.5f - G * H;
        G = G + G * R;
        H = H + H * R;
        check = (G * G) / input;
        count++;
    }

    return count == 99 || isnan(G) || isinf(G) ? -1 : 2 * H;
}