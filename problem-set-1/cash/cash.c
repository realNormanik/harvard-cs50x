#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int cents;

    // Fetch the number of cents until the user enters a value >= 0
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    int coins = 0;

    // Number of coins 25¢
    coins += cents / 25;
    cents %= 25;

    // Number of coins 10¢
    coins += cents / 10;
    cents %= 10;

    // Number of coins 5¢
    coins += cents / 5;
    cents %= 5;

    // Number of coins 1¢
    coins += cents;

    printf("%i\n", coins);
};
