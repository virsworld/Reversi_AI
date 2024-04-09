#include <stdio.h>
#include <math.h>

int main(void){
    const double PI = M_PI;
    // const double PI = floor(M_PI * pow(10,8)) * pow(10,-8);
    double a;
    double b;
    double c;
    double alpha;
    double beta;
    double gamma;

    printf("Enter the length of side A: ");
    scanf("%lf", &a);

    printf("Enter the length of side B: ");
    scanf("%lf", &b);

    printf("Enter the measure of angle alpha in degrees: ");
    scanf("%lf", &alpha);

    alpha *= PI / 180;
    beta = asin(b * sin(alpha) / a);
    gamma = PI - (alpha + beta);

    c = sin(gamma) * a / sin(alpha);

    alpha *= 180 / PI;
    beta *= 180 / PI;
    gamma *= 180 / PI;

    printf("\nResults:\n");
    printf("Side A: %.2lf\n", a);
    printf("Side B: %.2lf\n", b);
    printf("Side C: %.2lf\n", c);
    printf("Angle Alpha: %.2lf degrees\n", alpha);
    printf("Angle Beta: %.2lf degrees\n", beta);
    printf("Angle Gamma: %.2lf degrees\n", gamma);

    return 0;
}
