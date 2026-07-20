#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Ask the user until he gives a number greater than or equal to 1
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    // Drawing a pyramid
    for (int row = 1; row <= height; row++)
    {
        // Spaces
        for (int space = 0; space < height - row; space++)
        {
            printf(" ");
        }

        // Hashes
        for (int hash = 0; hash < row; hash++)
        {
            printf("#");
        }

        // New line
        printf("\n");
    };
};
