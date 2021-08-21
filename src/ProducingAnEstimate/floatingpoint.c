#include <stdio.h>
#include <stdint.h>

#include "ProducingAnEstimate/floatingpoint.h"

static union { float f; uint32_t i; } val = {16};	/* Convert type, preserving bit pattern */	

float floatingPoint(float input){
    // The original algorithm found in wikipedia, 
    // after doing the math on my own I managed
    // to make it faster by removing a step
    // val.f = i;
    // val.i -= 1 << 23;	/* Subtract 2^m. */
    // val.i >>= 1;		/* Divide by 2. */
    // val.i += 1 << 29;	/* Add ((b + 1) / 2) * 2^m. */
    // printf("%f\n", val.f);

    val.f = input;
    val.i >>= 1;
    val.i += 0b1111111 << 22; //(((1 << 23) * 127) / 2);
    return val.f;
}