# CS50X – Problem Set 6: Hello, Again

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. It revisits the very first exercise from Problem Set 1, but this time implemented in **Python** rather than C, marking the transition to Python as the course's second programming language. The goal was to write a program that prompts the user for their name and then greets them by printing `hello, <name>` to the screen. For example, if the user enters "David", the program should print `hello, David`.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- setting up and running a basic Python program for the first time in the course,
- reading user input from the command line using the `get_string` function from the `cs50` library,
- printing output to the console using Python's built-in `print` function,
- using **f-strings** to interpolate a variable's value directly into a formatted string,
- comparing Python's syntax and conventions to the C code written in earlier problem sets,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `sentimental-hello` using the command:
   ```bash
   mkdir sentimental-hello
   ```
2. Navigated into the newly created folder:
   ```bash
   cd sentimental-hello
   ```
3. Created a file called `hello.py` and wrote the program's source code in it.
4. Ran the program using the command:
   ```bash
   python hello.py
   ```
5. Manually tested the program with several different names (e.g., "David", "Inno", "Kamryn") to confirm the greeting was printed correctly in each case.
6. Checked the correctness of the program using the `check50` tool:
   ```bash
   check50 cs50/problems/2026/x/sentimental/hello
   ```
7. Checked the code style using the `style50` tool:
   ```bash
   style50 hello.py
   ```
8. Submitted the completed solution using the `submit50` tool:
   ```bash
   submit50 cs50/problems/2026/x/sentimental/hello
   ```

## 💻 Program Code

```python
from cs50 import get_string;

name = get_string("What is your name? ")
print(f"hello, {name}")
```

## 📤 Expected Output

After running the program in the terminal, the user is prompted for their name and the program then greets them accordingly, for example:

```
What is your name? David
hello, David
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Running Python Programs** – I learned how to execute a Python script from the terminal using `python hello.py`, as opposed to the compile-then-run workflow (`make` and `./program`) used for C programs in earlier problem sets.
- **Reading User Input in Python** – I learned how to use the `get_string` function from the `cs50` library to prompt the user for input, mirroring the equivalent function used in C but adapted to Python's syntax.
- **Formatted Strings (f-strings)** – I practiced using Python's f-string syntax (`f"hello, {name}"`) to interpolate a variable's value directly into a string, a more concise alternative to C's `printf` with format specifiers like `%s`.
- **Comparing C and Python** – I began to notice key differences between C and Python, such as Python's simpler syntax, lack of explicit type declarations, and lack of a separate compilation step, while recognizing that the underlying logic of the program remained conceptually identical to its C counterpart from Problem Set 1.
- **Program Structure with `main()`** – I got an early introduction to the common Python convention of defining a `main` function and guarding its execution with `if __name__ == "__main__":`, a pattern that will recur throughout future Python-based problem sets.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 6: Hello, Again](https://cs50.harvard.edu/x/psets/6/hello/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
