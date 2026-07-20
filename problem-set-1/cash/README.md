# CS50X – Problem Set 1: Cash

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to write a program in C that calculates the minimum number of coins needed to give a customer their change, given an amount of change owed in cents. The program prompts the user for an integer greater than or equal to 0, representing the change owed, and then prints the fewest number of coins (quarters, dimes, nickels, and pennies) required to make that amount, for example:

```
Change owed: 25
1
```

```
Change owed: 70
4
```

The user is re-prompted, again and again, if their input is not a valid non-negative integer.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading and validating user input using the `get_int` function from the CS50 library (`cs50.h`),
- implementing and understanding a **greedy algorithm** to solve an optimization problem,
- writing custom functions that take parameters and return values,
- decomposing a multi-step problem into smaller, independently solvable sub-problems (pseudocode-first approach),
- using `while` loops to repeatedly subtract coin values from a remaining balance,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `cash` using the command:
   ```bash
   mkdir cash
   ```
2. Navigated into the newly created folder:
   ```bash
   cd cash
   ```
3. Created a file called `cash.c` and wrote the program's source code in it.
4. Started with minimal, compilable code and gradually built up the solution using pseudocode comments as a guide.
5. Implemented input validation using a `do while` loop to repeatedly prompt the user until a valid, non-negative integer was entered.
6. Implemented a greedy algorithm to calculate the minimum number of coins, working from the largest denomination (quarters) down to the smallest (pennies), using dedicated functions for each coin type.
7. Compiled the program using the command:
   ```bash
   make cash
   ```
8. Ran the compiled program:
   ```bash
   ./cash
   ```
9. Manually tested the program with a range of inputs (negative numbers, `0`, `1`, `4`, `5`, `24`, `25`, `26`, `99`) to confirm the coin counts matched expectations.
10. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/cash
    ```
11. Checked the code style using the `style50` tool:
    ```bash
    style50 cash.c
    ```
12. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/cash
    ```

## 💻 Program Code

```c
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
```

## 📤 Expected Output

After running the compiled program in the terminal, the user is prompted for the change owed in cents, and the program then prints the minimum number of coins needed, for example:

```
Change owed: 99
9
```

If the user enters an invalid value (a non-integer or a negative number), the program keeps re-prompting until a valid amount is provided.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Greedy Algorithms** – I learned what a greedy algorithm is and how, at each step, choosing the locally optimal solution (the largest coin denomination that still fits) leads to a globally optimal result for U.S. currency.
- **Function Design and Return Values** – I practiced writing functions that accept a parameter (`cents`) and return a calculated value (the number of coins of a given denomination), reinforcing how functions can encapsulate and simplify complex logic.
- **Problem Decomposition** – I understood the value of breaking a larger problem (minimizing total coins) into smaller, repeatable sub-problems (calculating quarters, then dimes, then nickels, then pennies), each solved with a similar pattern.
- **Loop-Based Calculations** – I deepened my understanding of `while` loops used to repeatedly subtract a value from a running total while incrementing a counter, a pattern that recurs across several denomination-calculating functions.
- **Input Validation** – I reinforced my skills in validating user input with a `do while` loop, ensuring the program only proceeds once a valid non-negative integer is entered.
- **Manual and Automated Testing** – I practiced manually testing edge cases (such as `0`, `1`, `24`, `25`, `99`, and negative numbers) in addition to using CS50's automated tools, which strengthened my understanding of how to verify a program's correctness thoroughly.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 1: Cash](https://cs50.harvard.edu/x/psets/1/cash/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
