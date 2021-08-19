#include <stdio.h>
#include <stdint.h>

union { float f; uint32_t i; } val = {16};	/* Convert type, preserving bit pattern */	

int main(){
    for(float i = 0; i < 10000000.0f; i++){
        val.f = i;
        val.i -= 1 << 23;	/* Subtract 2^m. */
        val.i >>= 1;		/* Divide by 2. */
        val.i += 1 << 29;	/* Add ((b + 1) / 2) * 2^m. */
        printf("%f\n", val.f);

        val.f = i;
        val.i >>= 1;
        val.i += 0b1111111 << 22; //(((1 << 23) * 127) / 2);
        printf("%f\n", val.f);
    }
	return 1;		
}