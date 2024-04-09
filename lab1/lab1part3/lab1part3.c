#include <stdio.h>
#include <math.h>

int main(void)
{
    double circumference;
    double acceleration;
    double radius;
    double mass;
    double massf;
    double evelocity;
    const double G = 6.6726 * pow(10.0, -11.0) / pow(1000.0, 3.0);
    const double PI = M_PI;

    printf("Enter the circumference (km) of the planet: ");
    scanf("%lf", &circumference);

    printf("Enter the acceleration due to gravity (m/s^2) on the planet: ");
    scanf("%lf", &acceleration);

    printf("\nCalculating the escape velocity...");

    radius = circumference / (2.0 * PI);
    mass = ((acceleration / 1000.0) * pow(radius, 2.0)) / G;
    massf = mass * pow(10, -21);
    evelocity = sqrt(2.0 * G * mass / radius);

    printf("\nPlanet radius: %.1lf km", radius);
    printf("\nPlanet mass: %.1lf x 10^21 kg", massf);
    printf("\nEscape velocity: %.1lf km/s\n", evelocity);

    return 0;
}