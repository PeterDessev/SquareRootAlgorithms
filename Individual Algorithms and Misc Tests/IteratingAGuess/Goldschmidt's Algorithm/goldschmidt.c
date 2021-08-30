#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main(){
    double input, estimate, R, G, H;
    int count = 0;

    for(double i = 1; i < 100; i++){
        input = i * i;
        estimate = 1;
        G = input * estimate;
        H = estimate / 2;
        count = 0;

        while(((G * G) / input) < 0.9999){
            R = 0.5 - G * H;
            G = G + G * R;
            H = H + H * R;
            count++;
        }

        printf("%lf: %lf\n", input, G);

        //if(((G * G) / input) < 0.9999)
            //printf("G * G: %lf, / input: %lf\n", G * G, (G * G) / input);
        //printf("i: %llf, G ^ 2: %llf, 2H: %llf\n", i, G * G, 2 * H);
    }

    return 0;
}