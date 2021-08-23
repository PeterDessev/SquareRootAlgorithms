#include <stdint.h>

#include "ProducingAnEstimate/inverseSquare.h"

static union { float f; uint32_t i; } val;

float inverseSquare(float input){
    val.f = input;
    val.i = 0x5f375a86 - (val.i >> 1);
    return val.f;
}