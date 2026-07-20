# CS50X – Problem Set 2: Caesar

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to write a program in C that encrypts messages using **Caesar's cipher**, a classic encryption technique that shifts each letter of a message by a fixed number of positions in the alphabet. The program accepts a single command-line argument — the encryption key — validates it, prompts the user for plaintext, and prints the resulting ciphertext, for example:

```
$ ./caesar 1
plaintext:  HELLO
ciphertext: IFMMP
```

If the program is run without exactly one command-line argument, or if that argument contains non-digit characters, the program prints a usage message and exits with a return value of 1.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- working with **command-line arguments** (`argc` and `argv`) in a C program,
- validating input at multiple levels: argument count, argument format, and value range,
- converting a string to an integer using the `atoi` function from `stdlib.h`,
- manipulating characters using ASCII arithmetic to implement a rotation ("shift") algorithm,
- using the modulo operator (`%`) to "wrap around" values within a fixed range (the 26 letters of the alphabet),
- preserving letter casing while transforming characters,
- writing modular code using custom functions with clear responsibilities,
- returning specific exit codes from `main` to signal success or failure,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, debugging with `debug50`, and submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `caesar` using the command:
   ```bash
   mkdir caesar
   ```
2. Navigated into the newly created folder:
   ```bash
   cd caesar
   ```
3. Created a file called `caesar.c` and wrote the program's source code in it.
4. Started with pseudocode outlining the main steps of the program before writing actual code.
5. Implemented validation to ensure the program was run with exactly one command-line argument, printing a usage message and returning `1` otherwise.
6. Implemented an `only_digits` function to verify that the command-line argument consisted solely of decimal digits, rejecting non-numeric keys.
7. Converted the validated command-line argument from a string to an integer using `atoi`.
8. Implemented a `rotate` function that shifts a single character by a given number of positions, wrapping around the alphabet as needed, while leaving non-alphabetical characters unchanged and preserving letter case.
9. Combined all the pieces in `main`: prompting the user for plaintext, iterating over each character, applying `rotate`, and printing the resulting ciphertext.
10. Compiled the program using the command:
    ```bash
    make caesar
    ```
11. Ran the compiled program:
    ```bash
    ./caesar 1
    ```
12. Manually tested the program with a range of inputs, including no arguments, multiple arguments, non-numeric keys, keys greater than 26, and plaintext containing mixed-case letters and non-alphabetical characters.
13. Used `debug50` to step through the program's execution and verify its behavior:
    ```bash
    debug50 ./caesar 1
    ```
14. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/caesar
    ```
15. Checked the code style using the `style50` tool:
    ```bash
    style50 caesar.c
    ```
16. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/caesar
    ```

## 💻 Program Code

```c
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);   // Checks whether the string contains only digits
char rotate(char c, int key); // Returns the encrypted character using the key

int main(int argc, string argv[])
{
    // Check if the user has given exactly one argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    };

    // Check if the argument contains only digits
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    };

    // Replace the argument with an integer
    int key = atoi(argv[1]);

    // Ask the user for the text to encrypt
    string plaintext = get_string("plaintext:  ");

    // Write out the ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Encrypt each character and write it out
        printf("%c", rotate(plaintext[i], key));
    }
    // Add a new line after the ciphertext
    printf("\n");
    return 0;
};

// Checks if the string contains only digits
bool only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        // If any character is not a digit, return false
        if (!isdigit(s[i]))
        {
            return false;
        }
    };
    // If all characters are digits, return true
    return true;
};

// Encrypts the c character using the key key
char rotate(char c, int key)
{
    // If the character is an uppercase letter
    if (isupper(c))
    {
        return (c - 'A' + key) % 26 + 'A';
    }
    // If the character is a lowercase letter
    else if (islower(c))
    {
        return (c - 'a' + key) % 26 + 'a';
    }
    else
    // If it's not a letter, don't change
    {
        return c;
    };
};
```

## 📤 Expected Output

After compiling and running the program with a valid key, the user is prompted for plaintext, and the program then prints the corresponding ciphertext, for example:

```
$ ./caesar 1
plaintext:  HELLO
ciphertext: IFMMP
```

If the program is run incorrectly, it prints a usage message instead:

```
$ ./caesar
Usage: ./caesar key
```

```
$ ./caesar banana
Usage: ./caesar key
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Command-Line Arguments** – I learned how to access and validate command-line arguments in C using `argc` (argument count) and `argv` (argument vector), and how to handle cases where the program is run with an incorrect number of arguments.
- **Multi-Stage Input Validation** – I practiced validating input progressively: first checking the number of arguments, then verifying that the argument contained only digits, and only then converting and using it as a numeric key.
- **String-to-Integer Conversion** – I learned how to use the `atoi` function from `stdlib.h` to safely convert a validated numeric string into an `int` for use in calculations.
- **Character Rotation with Modulo Arithmetic** – I deepened my understanding of how the modulo operator (`%`) can be used to "wrap around" values within a fixed range, which was essential for correctly rotating letters past 'Z' back to 'A' (and 'z' back to 'a'), even for keys much larger than 26.
- **ASCII Arithmetic and Case Preservation** – I practiced using ASCII arithmetic (subtracting and re-adding a base character like `'A'` or `'a'`) to perform letter rotation while ensuring uppercase letters stayed uppercase and lowercase letters stayed lowercase.
- **Selective Character Transformation** – I learned how to apply a transformation only to alphabetical characters while leaving punctuation, digits, and spaces in the input unchanged.
- **Program Exit Codes** – I understood the significance of returning specific values from `main` (`0` for success, `1` for an error), a convention widely used in command-line programs to signal their execution status.
- **Debugging Tools** – I gained hands-on experience using `debug50` to step through the program's execution and inspect variable values, which helped me better understand and troubleshoot the flow of the program.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 2: Caesar](https://cs50.harvard.edu/x/psets/2/caesar/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
