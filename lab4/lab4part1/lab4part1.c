#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double randDouble(void) {
    return (double)rand() / ((double)RAND_MAX);
}

bool inBounds(double x, double y){
    if (x*x + y*y <= 1){
        return true;
    }
    else{
        return false;
    }

}

int main(void){
    srand(42);
    int iterations, check = 0, num = 0;
    double ePi, randx, randy;
    printf("Number of monte carlo iterations: ");
    scanf("%d", &iterations);

    for (int i = 1; i <= iterations; i++){
        randx = randDouble();
        randy = randDouble();
        check = inBounds(randx, randy);
        if (check == true){
            num++;
        }
    }
    ePi = 4 * (num / (double) iterations);
    printf("\nPi: %.4lf\n", ePi);
    return 0;
}
