# CS50X – Problem Set 1: Mario (Less)

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to write a program in C that recreates the right-aligned pyramid of bricks that Mario climbs toward the end of World 1-1 in Nintendo's *Super Mario Bros.* The program prompts the user for the pyramid's height and then prints a right-aligned pyramid built out of hashes (`#`) accordingly, for example:

```
       #
      ##
     ###
    ####
   #####
  ######
 #######
########
```

The user is re-prompted, again and again, if their input is not a valid integer or not greater than 0.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading and validating user input using the `get_int` function from the CS50 library (`cs50.h`),
- using loops (`do while` and `for`) to repeat actions and build patterned output,
- decomposing a problem into smaller, manageable sub-problems (pseudocode-first approach),
- writing and calling custom functions, including passing parameters and using function prototypes,
- printing formatted output row by row using `printf`,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `mario-less` using the command:
   ```bash
   mkdir mario-less
   ```
2. Navigated into the newly created folder:
   ```bash
   cd mario-less
   ```
3. Created a file called `mario.c` and wrote the program's source code in it.
4. Started with minimal, compilable code and gradually built up the solution using pseudocode comments as a guide.
5. Implemented input validation using a `do while` loop to repeatedly prompt the user until a valid height (an integer greater than 0) was entered.
6. Implemented a `print_row` function responsible for printing a single row of the pyramid, consisting of the correct number of spaces followed by the correct number of bricks.
7. Compiled the program using the command:
   ```bash
   make mario
   ```
8. Ran the compiled program:
   ```bash
   ./mario
   ```
9. Checked the correctness of the program using the `check50` tool:
   ```bash
   check50 cs50/problems/2026/x/mario/less
   ```
10. Checked the code style using the `style50` tool:
    ```bash
    style50 mario.c
    ```
11. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/mario/less
    ```

## 💻 Program Code

```c
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
```

## 📤 Expected Output

After running the compiled program in the terminal, the user is prompted for the pyramid's height and, once a valid value is entered, the program prints a right-aligned pyramid of that height, for example:

```
Height: 4
   #
  ##
 ###
####
```

If the user enters an invalid value (a non-integer, a negative number, or 0), the program keeps re-prompting until a valid height is provided.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Input Validation** – I learned how to use a `do while` loop together with `get_int` to repeatedly prompt the user until valid input (an integer greater than 0) is provided.
- **Loop Control** – I practiced using `for` loops to control repetitive tasks, such as printing a specific number of characters, and understood the relationship between loop counters and the number of rows or characters printed.
- **Function Design** – I learned how to declare a function prototype, define a function with parameters, and call it from `main`, which helped me break the problem down into smaller, reusable pieces of logic.
- **Problem Decomposition** – I understood the value of writing pseudocode comments first to break a complex problem (printing a right-aligned pyramid) into smaller, solvable sub-problems (getting valid input, printing spaces, printing bricks).
- **Formatted Output** – I learned how to combine spaces and hash characters using `printf` to produce precisely aligned, patterned console output.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code, including testing edge cases such as negative numbers, zero, letters, and empty input.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 1: Mario (Less)](https://cs50.harvard.edu/x/psets/1/mario/less/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
