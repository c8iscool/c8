#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    //user inputs monetary value in dollars
    float money;
    do
    {
        money = get_float("How much money? ($) \n");
    }
    //ensures that the float is a nonnegative value
    while (money < 0);
    
    //converts dollars to cents
    money = round(money * 100);
    int coins = 0;
    //counter for the number of coins needed, from quarters (25) to pennies (1)
    coins = round(money / 25);
    money = money - 25 * round(money / 25);
    coins = coins + round(coins / 10);
    money = money - 10 * round(money / 10);
    coins = coins + round(money / 5);
    money = money - 5 * round(money / 5);
    coins = coins + round(coins / 1);
    printf("%i\n", coins);
}
