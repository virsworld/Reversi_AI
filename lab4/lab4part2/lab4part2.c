#include <stdio.h>

int numDigits(int x){
    int count = 0;
    do {
        x /= 10;
        count++;
    } while (x != 0);
    return count;
}

int power(int x, int y){
    for(int i = 1; i <= y - 1; i++){
        x *= 10;
    }
    return x;
}

int main(void){
    int num = 0;
    int count = 0;
    int seven = 0;
    int temp = 0;
    int lseven = 0;
    double fseven = 0.0;

    printf("Input an integer: ");
    scanf("%d", &num);

    while(num != 0){
        count = numDigits(num);
        for (int i = 1; i <= count; i++){
            temp = num;
            if (num < 0){
                temp = num * -1;
            }
            if (i == 1){
                temp %= power(10, i);
            }
            else{
                temp %= power(10, i);
                temp /= power(10, i - 1);
            }
            if (temp == 7 || temp == -7){
                seven++;
                fseven++;
            }
        }
        if (((fseven / 3) - seven / 3) == 0 && seven == 3){
            lseven += seven / 3;        
        }
        seven = 0;
        fseven = 0;
        printf("Input an integer (0 to stop): ");
        scanf("%d", &num);
    }
    printf("You entered %d lucky number(s)!\n", lseven);

    return 0;
}
