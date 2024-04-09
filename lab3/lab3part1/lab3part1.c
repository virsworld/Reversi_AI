#include <stdio.h>

int main(void) {
    char userSign;
    int userNum;
    int sum = 0;

    printf("Enter sequence of numbers to add:");
    scanf("%c%d", &userSign, &userNum);
    if (userSign == '-'){
        userNum *= -1;
    }
    else{
        sum += userNum;
    }

    do {
        printf("Sum is updated to %d\n", sum);
        scanf("%c%d", &userSign, &userNum);
        if (userSign == '-'){
            userNum *= -1;
        }
        else{
            sum += userNum;
        }
    } while (sum >= 0);
    printf("Sum is updated to %d\n", sum);
    printf("Sum fell below zero.\n");

    return 0;
}
