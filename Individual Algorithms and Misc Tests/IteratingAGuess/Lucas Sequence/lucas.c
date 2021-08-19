#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef struct __lucasSeries{
    long double current;
    long double previous;
    long double preprevious;
} lucasSeries;

// void lucas(double P, double Q, unsigned long int n, lucasSeries* res){
//     if(n <= 1){
//         res->current = 1;
//         res->previous = 0;
//         return;
//     }   
//     lucas(P, Q, n - 1, res);
//     res->preprevious = res->previous;
//     res->previous = res->current;
//     res->current = P * res->previous - Q * res->preprevious;
//     if(res->current > 1E5){
//         res->current /= 1 << 30;
//         res->previous /= 1 << 30;
//     }
//     return;
// }

int main(){
    lucasSeries* test;
    unsigned long int count;
    double result, check, P, Q;

    for(double i = 1E-10; i < 1E10; i *= 10){
        test->current = 1;
        test->previous = 0;
        P = 2;
        Q = 1 - i;
        count = 0;
        check = 0;

        while(check < 0.9999 || check > 1.0001){
            count++;
            test->preprevious = test->previous;
            test->previous = test->current;
            test->current = P * test->previous - Q * test->preprevious;

            if(test->current > 1E5){
                test->current /= 1 << 30;
                test->previous /= 1 << 30;
            }

            result = test->current / test->previous - 1;
            check = (result * result) / i;
        }
        printf("%lf: %d\n", result * result, count);
    }

    return 0;
}