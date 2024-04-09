#include <stdio.h>
#include <math.h>

int main(void){

    const double K = 8.9875 * pow(10, 9);
    double eForce;
    double lfQ1;
    char sQ1[100];
    double lfQ2;
    char sQ2[100];
    double r;

    printf("Enter the value of the two charges separated by a space: ");
    scanf("%lf", &lfQ1);
    scanf("%s", sQ1);
    scanf("%lf", &lfQ2);
    scanf("%s", sQ2);
    printf("Enter distance between charges in metres: ");
    scanf("%lf", &r);
    
    if (lfQ1 < 0){
        lfQ1 *= -1;
    }

    if (lfQ2 < 0){
        lfQ2 *= -1;
    }

    if (sQ1[0] == 'u' && sQ2[0] == 'u'){
        lfQ1 *= pow(10, -6);
        lfQ2 *= pow(10, -6);
    }
    else if (sQ1[0] == 'n' && sQ2[0] == 'n'){
        lfQ1 *= pow(10, -9);
        lfQ2 *= pow(10, -9);
    }
    else if (sQ1[0] == 'n'){
        lfQ1 *= pow(10, -9);
        lfQ2 *= pow(10, -6);
    }
    else{
        lfQ1 *= pow(10, -6);
        lfQ2 *= pow(10, -9);
    }

    eForce = K * lfQ1 * lfQ2 / pow(r, 2);

    if (eForce < pow(10, -6)){
        eForce *= pow(10, 9);
        printf("The force between charges is %.2lfnN (less than 1 uN)\n", eForce);
    }
    else if (eForce < pow(10, -3)){
        eForce *= pow(10, 6);
        printf("The force between charges is %.2lfuN (less than 1 mN)\n", eForce);
    }
    else if (eForce < 1){
        eForce *= pow(10, 3);
        printf("The force between charges is %.2lfmN (less than 1 N)\n", eForce);
    }
    else{
        printf("The force between charges is %.2lfN (1N or greater)\n", eForce);
    }

    return 0;
}
