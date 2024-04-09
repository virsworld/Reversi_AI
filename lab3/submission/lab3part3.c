#include <stdio.h>
#include <math.h>

double efunc(double x){
    double val;
    double exponent;

    exponent = -pow(x, 2);
    val = pow(M_E, exponent);
    return val;
}

int main(void){
    int n = 1;
    double a;
    double b;
    double sum = 0;
    double deltaX;
    
    while (n >= 1){
        printf("\nPlease enter the number of rectangles (n): ");
        scanf("%d", &n);
        if (n < 1){
            break;
        }

        do{
            printf("Please enter the interval of integration (a b): ");
            scanf("%lf %lf", &a, &b);
            if (a > b){
                printf("Invalid interval!\n\n");
            }
        } while(a > b);

        deltaX = (b - a) / n;

        for (int i = 1; i <= n; i++){
            sum += efunc((a + i * deltaX) - (deltaX / 2)) * deltaX;
        }
        printf("The integral of e^-x^2 on [%.5lf, %.5lf] with n = %d is: %.5lf\n", a, b, n, sum);
        sum = 0;
    }
    printf("Exiting.\n");
    return 0;
}
