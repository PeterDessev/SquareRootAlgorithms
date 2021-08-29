#include <stdio.h>

void regular();
void inverse();

int main(){
    inverse();
    return 0;
}


void regular(){
    for(double i = 1E-10; i < 1E10; i *= 10){
        double guess = i > 1 ? i / 2 : i * 2;
        for(int c = 0; c < 50; c++){
            guess = guess - ((guess * guess - i) / (2 * guess - 1));
        }
    }
}

void inverse(){
    for(double input = 1E-10; input < 1E10; input *= 10){
        int count = 0;
        double estimate = input > 1 ? input / 2 : input * 2;
        float estimateSquared, numerator, denominator, check = 0;

        while(check < 0.9999 || check > 1.0001){
        //for(int i = 0; i < 10000; i++){
            count++;
            estimateSquared = estimate * estimate;
            numerator = -1 * estimateSquared * estimate * input - 3 * estimate;
            denominator = -3 * estimateSquared * input - 1;

            estimate = (numerator / denominator);
        
            check = (estimate * estimate) * input;
        }
        printf("%g: %d\n", estimate, count);
    }
}