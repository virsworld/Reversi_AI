#include <stdio.h>

int main (void){
    double cHour;
    double cMin;
    double hourTriptime;
    int ihourTriptime;
    double minTriptime;
    int iminTriptime;
    int check = 0;

    printf("Enter current time: ");
    scanf("%lf", &cHour);
    scanf("%lf", &cMin);
    printf("Enter trip time: ");
    scanf("%lf", &hourTriptime);

    if (cHour < 10 && cMin < 10){
        printf("\nCurrent time is 0%.0lf:0%.0lf\n", cHour, cMin);
    }
    else if(cHour < 10){
        printf("\nCurrent time is 0%.0lf:%.0lf\n", cHour, cMin);
    }
    else if (cMin < 10){
        printf("\nCurrent time is %.0lf:0%.0lf\n", cHour, cMin);
    }
    else{
        printf("\nCurrent time is %.0lf:%.0lf\n", cHour, cMin);
    }

    ihourTriptime = hourTriptime;
    minTriptime = (hourTriptime - ihourTriptime) * 60;
    // minTriptime = (hourTriptime - floor(hourTriptime)) * 60;
    hourTriptime = ihourTriptime;
    // hourTriptime = floor(hourTriptime);
    iminTriptime = minTriptime;
    cHour += hourTriptime;
    cMin += iminTriptime;
    // cMin += floor(minTriptime);
    

    if (cMin >= 60){
        cMin -= 60;
        cHour++;
    }

    if (cHour >= 24){
        cHour -= 24;
        check = 1;
    }

    if (check == 0 && cHour < 10 && cMin < 10){
        printf("Arrival Time is same day 0%.0lf:0%.0lf\n", cHour, cMin);
    }
    else if(check == 0 && cHour < 10){
        printf("Arrival Time is same day 0%.0lf:%.0lf\n", cHour, cMin);
    }
    else if(check == 0 && cMin < 10){
        printf("Arrival Time is same day %.0lf:0%.0lf\n", cHour, cMin);
    }
    else if(check == 0){
        printf("Arrival Time is same day %.0lf:%.0lf\n", cHour, cMin);
    }

    if (check == 1 && cHour < 10 && cMin < 10){
        printf("Arrival Time is next day 0%.0lf:0%.0lf\n", cHour, cMin);
    }
    else if(check == 1 && cHour < 10){
        printf("Arrival Time is next day 0%.0lf:%.0lf\n", cHour, cMin);
    }
    else if(check == 1 && cMin < 10){
        printf("Arrival Time is next day %.0lf:0%.0lf\n", cHour, cMin);
    }
    else if(check == 1){
        printf("Arrival Time is next day %.0lf:%.0lf\n", cHour, cMin);
    }

    return 0;
}
