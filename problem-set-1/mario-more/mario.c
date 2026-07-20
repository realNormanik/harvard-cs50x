#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Ask the user about the height between 1 and 8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // For each line
    for (int row = 1; row <= height; row++)
    {
        // Spaces before the left pyramid
        for (int space = 0; space < height - row; space++)
        {
            printf(" ");
        };

        // Left pyramid
        for (int hash = 0; hash < row; hash++)
        {
            printf("#");
        };

        // Spacing
        printf("  ");

        // Right pyramid
        for (int hash = 0; hash < row; hash++)
        {
            printf("#");
        };

        // New line
        printf("\n");
    };
};
