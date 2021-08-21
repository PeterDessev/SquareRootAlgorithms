#include <stdio.h>
#include "include/roots.h"

int main(){
    // Array of functions for producing a guess
    int (*producing[]) (float input) = {
        floatingPoint,
        inverseSquare
    };

    // Array of functions for iterating a guess     
    int (*iterating[]) (float input, float estimate) = {
        goldschmidt,
        lucas,
        newton,
        halley
    };

    float result = (*producing[0]) (1.0f);
    return 0;
}