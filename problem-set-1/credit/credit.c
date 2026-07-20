#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get your credit card number from the user
    long number = get_long("Number: ");
    long cc = number;

    int sum = 0;
    int position = 0;
    int digit;

    // Variables to check the first digits of the card
    int first_two = 0;
    int first_digit = 0;

    // A loop that analyzes the digits of the card number from the end
    while (cc > 0)
    {
        digit = cc % 10;

        // Every second digit from the end (even position - 0, 2, 4...) added without change
        if (position % 2 == 0)
        {
            sum += digit;
        }
        // The remaining digits are multiplied by 2, and their digits are added to the total
        else
        {
            int product = digit * 2;
            sum += product / 10 + product % 10;
        }

        // Keep the first two digits
        if (cc < 100 && cc >= 10)
        {
            first_two = cc;
        }

        // Keep the first digit (for VISA)
        if (cc < 10)
        {
            first_digit = cc;
        }

        cc /= 10;
        position++;
    };

    // Check if the sum according to Luhn's algorithm ends in 0
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Check the type of card by length and initial digits
    if ((position == 15) && (first_two == 34 || first_two == 37))
    {
        printf("AMEX\n");
    }
    else if ((position == 16) && (first_two >= 51 && first_two <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((position == 13 || position == 16) && (first_digit == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    };
};
