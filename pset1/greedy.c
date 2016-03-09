#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) {

    float amount = 0;

    do {
        //get user input and validate it is greater than 0
        printf("How much is owed?:\n");
        amount = GetFloat();

    } while (amount < 0);

    int pennies = round(amount * 100);
    int coins = 0;
    int remainder = 0;

    coins = pennies / 25;
    remainder = pennies % 25;

    coins = coins + remainder / 10;
    remainder = remainder % 10;

    coins = coins + remainder / 5;
    remainder = remainder % 5;

    coins = coins + remainder;

    printf("%d\n", coins);
}
