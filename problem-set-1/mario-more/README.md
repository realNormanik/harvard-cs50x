# CS50X – Problem Set 1: Mario (More)

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to write a program in C that recreates the pair of adjacent pyramids of blocks that Mario hops over toward the beginning of World 1-1 in Nintendo's *Super Mario Brothers*. The program prompts the user for the pyramids' height (a positive integer between 1 and 8, inclusive) and then prints two right-aligned/left-aligned pyramids side by side, separated by a two-character gap, built out of hashes (`#`), for example:

```
   #  #
  ##  ##
 ###  ###
####  ####
```

The user is re-prompted, again and again, until they enter a valid integer between 1 and 8, inclusive.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading and validating user input within a specific numeric range using the `get_int` function from the CS50 library (`cs50.h`),
- using loops (`do while` and `for`) to repeat actions and build patterned output,
- decomposing a more complex visual pattern (two mirrored pyramids) into smaller, manageable sub-problems,
- writing and calling custom functions with multiple parameters,
- printing precisely formatted output row by row, combining spaces, bricks, and a fixed-width gap using `printf`,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `mario-more` using the command:
   ```bash
   mkdir mario-more
   ```
2. Navigated into the newly created folder:
   ```bash
   cd mario-more
   ```
3. Created a file called `mario.c` and wrote the program's source code in it.
4. Implemented input validation using a `do while` loop to repeatedly prompt the user until a valid height (an integer between 1 and 8, inclusive) was entered.
5. Implemented a `print_row` function responsible for printing a single row of the two pyramids, consisting of leading spaces, the left pyramid's bricks, a fixed-width gap, and the right pyramid's bricks.
6. Compiled the program using the command:
   ```bash
   make mario
   ```
7. Ran the compiled program:
   ```bash
   ./mario
   ```
8. Checked the correctness of the program using the `check50` tool:
   ```bash
   check50 cs50/problems/2026/x/mario/more
   ```
9. Checked the code style using the `style50` tool:
   ```bash
   style50 mario.c
   ```
10. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/mario/more
    ```

## 💻 Program Code

```c
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
```

## 📤 Expected Output

After running the compiled program in the terminal, the user is prompted for the pyramids' height and, once a valid value between 1 and 8 is entered, the program prints two mirrored pyramids side by side, for example:

```
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####
```

If the user enters an invalid value (a non-integer, a number less than 1, or a number greater than 8), the program keeps re-prompting until a valid height is provided.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Range-Based Input Validation** – I learned how to validate user input against both a lower and an upper bound (1 to 8, inclusive) using a `do while` loop combined with a compound logical condition.
- **Extending Existing Logic** – I practiced building on the single-pyramid pattern from an earlier exercise and extended it to print two mirrored pyramids with a fixed gap between them, reinforcing how small, well-designed functions can be reused and adapted.
- **Precise Formatted Output** – I strengthened my understanding of combining multiple `printf` calls within a single function to produce exact, consistently aligned console output, including a constant-width gap regardless of pyramid height.
- **Function Design with Multiple Responsibilities** – I learned how to structure a function so that it handles several related printing tasks (spaces, left pyramid, gap, right pyramid) in a clear and readable order.
- **Loop Control** – I deepened my understanding of how a single loop variable can be reused to calculate both the number of spaces and the number of bricks needed on each row.
- **Testing Edge Cases** – I practiced testing the program against a wide range of inputs, including negative numbers, zero, values outside the valid range, non-numeric input, and empty input, to ensure robust input handling.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 1: Mario (More)](https://cs50.harvard.edu/x/psets/1/mario/more/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
