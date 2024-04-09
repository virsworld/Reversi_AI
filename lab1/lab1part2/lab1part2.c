#include <stdio.h>

int main(void)
{
    double tempf;
    double tempc;
    double difference;

    printf("Enter the thermostata temperature: ");
    scanf("%lf", &tempf);

    tempc = (tempf - 32) * 5 / 9;
    difference = tempf - ((22 * 9 / 5.0) + 32);
    

    printf("The temperature in Celsius is: %.1lf\n", tempc);
    printf("\nYou are %.1lf degrees Farenheit away from a nice 22 degrees Celsius.\n", difference);

    return 0;
}
