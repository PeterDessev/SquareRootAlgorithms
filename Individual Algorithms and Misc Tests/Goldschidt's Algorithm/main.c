#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main(){
    double S, Y, R, G, H;
    int J = 0;

    for(double i = 1E-10; i < 1E10; i *= 10){
        S = i;
        Y = S >= 1 ? 1 / (2 * S) : 2 * S;
        G = S * Y;
        H = Y / 2;
        J = 0;

        while(((G * G) / S) < 0.9999){
            R = 0.5 - G * H;
            G = G + G * R;
            H = H + H * R;
            J++;
        }

        printf("%lf: %d\n", S, J);

        //if(((G * G) / S) < 0.9999)
            //printf("G * G: %lf, / S: %lf\n", G * G, (G * G) / S);
        //printf("i: %llf, G ^ 2: %llf, 2H: %llf\n", i, G * G, 2 * H);
    }

    return 0;
}