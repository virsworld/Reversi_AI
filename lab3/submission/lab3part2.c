#include <stdio.h>
#include <math.h>

int main(void){
    const double G = 9.81;
    const double l = 2;
    const double v = 20;
    const double PI = M_PI;

    double d, h, t, y, vx, vy;
    double dAlpha = 0;
    double rAlpha = 0;
    int check = 0;

    do{
        printf("Please enter the horizontal distance from the wall between 3 and 30 m:\n");
        scanf("%lf", &d);
    } while(d < 3 || d > 30);

    do{
        printf("Please enter the target height between 3 and 6 m:\n");
        scanf("%lf", &h);
    } while(h < 3 || h > 6);

    do{
        if (check){
            dAlpha++;
            rAlpha = dAlpha * PI / 180;
        }
        vx = v * cos(rAlpha);
        vy = v * sin(rAlpha);
        t = d / vx;
        
        y = l + vy * t - 0.5 * G * pow(t, 2);
        check = 1;
    } while(fabs(y - h) > 0.3);
    
    printf("The angle should be %.2lf\n", dAlpha);

    return 0;
}
