# CS50X – Problem Set 1: Me

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to write a program in C that prompts the user for their name and then greets that user by printing `hello, <name>` to the screen. For example, if the user enters "Adele", the program should print `hello, Adele`.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading user input from the command line using the `get_string` function from the CS50 library (`cs50.h`),
- formatting and printing strings using the `printf` function and the `%s` format specifier,
- basic variable declaration and usage in the C programming language,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `me` using the command:
   ```bash
   mkdir me
   ```
2. Navigated into the newly created folder:
   ```bash
   cd me
   ```
3. Created a file called `hello.c` and wrote the program's source code in it.
4. Compiled the program using the command:
   ```bash
   make hello
   ```
5. Ran the compiled program:
   ```bash
   ./hello
   ```
6. Checked the correctness of the program using the `check50` tool:
   ```bash
   check50 cs50/problems/2026/x/me
   ```
7. Checked the code style using the `style50` tool:
   ```bash
   style50 hello.c
   ```
8. Submitted the completed solution using the `submit50` tool:
   ```bash
   submit50 cs50/problems/2026/x/me
   ```

## 💻 Program Code

```c
#include <cs50.h>  // standard I/O library
#include <stdio.h> // Library for input/output handling

// Main function of the program
int main(void)
{
    // Ask a user for their name
    string name = get_string("What is your name? ");
    // Greet a user by name
    printf("hello, %s\n", name);
};
```

## 📤 Expected Output

After running the compiled program in the terminal, the user is prompted for their name and the program then greets them accordingly, for example:

```
What is your name? Adele
hello, Adele
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **User Input Handling** – I learned how to read a string entered by the user from the terminal using the `get_string` function provided by the `cs50.h` library.
- **String Formatting** – I learned how to use the `%s` format specifier with `printf` to insert a string value into printed output.
- **Working with the CS50 Library** – I got familiar with the `string` data type and other conveniences offered by the CS50 library, which simplify common tasks for beginner C programmers.
- **Program Interactivity** – I understood how to make a simple C program interactive by combining input handling with formatted output.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 1: Me](https://cs50.harvard.edu/x/psets/1/me/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
