# CS50X – Problem Set 1: Hello, World

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to write my very first program in the C programming language, which prints the text `hello, world` to the screen — the traditional first program written by beginner programmers.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- the basic structure of a program written in C,
- the process of compiling source code into an executable file,
- working in a terminal environment and using basic system commands,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code.

## 🛠️ Steps Taken

1. Created a folder called `world` using the command:
   ```bash
   mkdir world
   ```
2. Navigated into the newly created folder:
   ```bash
   cd world
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
   check50 cs50/problems/2026/x/world
   ```
7. Checked the code style using the `style50` tool:
   ```bash
   style50 hello.c
   ```

## 💻 Program Code

```c
#include <stdio.h> // Library for input/output handling

// Main function of the program
int main(void)
{
    // Print “hello, world” and go to a new line
    printf("hello, world\n");
};
```

## 📤 Expected Output

After running the compiled program in the terminal, the following text should be displayed:

```
hello, world
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **C Language Basics** – I learned the structure of a simple C program, including the role of the `#include` directive, the `main()` function, and the `printf()` library function used to print text to standard output.
- **Compilation Process** – I understood the difference between source code (`hello.c`) and an executable file (`hello`) produced as a result of compilation using the `make` command.
- **Terminal Usage** – I became more proficient with basic system commands such as `mkdir`, `cd`, and `ls`, which are essential for working efficiently in a development environment.
- **Testing and Code Verification** – I got familiar with CS50's tools (`check50` and `style50`), which automate the process of checking the correctness of a program's behavior as well as the quality and style of the written code according to good programming practices.
- **Debugging** – I learned to use the `help50` command, which helps interpret error messages that appear during compilation.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 1: Hello, World](https://cs50.harvard.edu/x/psets/1/world/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
