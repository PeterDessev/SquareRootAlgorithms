#include <stdio.h>

void regular();
void inverse();

int main(){
    
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
    
}