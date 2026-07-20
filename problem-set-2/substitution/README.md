# CS50X – Problem Set 2: Substitution

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to write a program in C that encrypts messages using a **substitution cipher**, a technique in which each letter of the alphabet is replaced by another letter according to a fixed key. The program accepts a single command-line argument — a 26-character key — validates it, prompts the user for plaintext, and prints the resulting ciphertext, for example:

```
$ ./substitution NQXPOMAFTRHLZGECYJIUWSKDVB
plaintext: HELLO
ciphertext: FOLLE
```

If the program is run without exactly one command-line argument, or if the provided key is invalid, the program prints an error message and exits with a return value of 1.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- working with **command-line arguments** (`argc` and `argv`) in a C program,
- validating a key against multiple criteria: correct length, exclusively alphabetic characters, and no repeated letters,
- mapping each letter of the alphabet to a corresponding cipher letter using array indexing,
- using functions from `ctype.h` (such as `isalpha`, `isupper`, and `islower`) to classify and transform characters,
- preserving letter casing while substituting characters,
- writing modular code using custom functions with clear, single responsibilities,
- returning specific exit codes from `main` to signal success or failure,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, debugging with `debug50`, and submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `substitution` using the command:
   ```bash
   mkdir substitution
   ```
2. Navigated into the newly created folder:
   ```bash
   cd substitution
   ```
3. Created a file called `substitution.c` and wrote the program's source code in it.
4. Implemented validation to ensure the program was run with exactly one command-line argument, printing an error message and returning `1` otherwise.
5. Implemented a `valid_key` function to verify that the key was exactly 26 characters long, consisted solely of alphabetic characters, and contained each letter of the alphabet exactly once (case-insensitively).
6. Implemented a `substitute` function that maps a single plaintext character to its corresponding ciphertext character using the key, preserving the original letter's case and leaving non-alphabetical characters unchanged.
7. Combined all the pieces in `main`: prompting the user for plaintext, iterating over each character, applying `substitute`, and printing the resulting ciphertext.
8. Compiled the program using the command:
   ```bash
   make substitution
   ```
9. Ran the compiled program:
   ```bash
   ./substitution NQXPOMAFTRHLZGECYJIUWSKDVB
   ```
10. Manually tested the program with a range of inputs, including no arguments, multiple arguments, keys shorter or longer than 26 characters, keys containing repeated letters or non-alphabetic characters, and plaintext containing mixed-case letters and non-alphabetical characters.
11. Used `debug50` to step through the program's execution and verify its behavior:
    ```bash
    debug50 ./substitution NQXPOMAFTRHLZGECYJIUWSKDVB
    ```
12. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/substitution
    ```
13. Checked the code style using the `style50` tool:
    ```bash
    style50 substitution.c
    ```
14. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/substitution
    ```

## 💻 Program Code

```c
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Function to check whether the key is valid
bool is_valid_key(string key);

// Helper function that substitutes a character using the key
char substitute(char c, string key);

int main(int argc, string argv[])
{
    // Check for exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    };

    string key = argv[1];

    // Validate the key
    if (!is_valid_key(key))
    {
        printf("Key must contain 26 unique alphabetical characters.\n");
        return 1;
    };

    // Prompt the user for plaintext
    string plaintext = get_string("plaintext:  ");

    // Print the ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", substitute(plaintext[i], key));
    };

    printf("\n");
    return 0;
};

// Function to check if the key is 26 unique alphabetical characters
bool is_valid_key(string key)
{
    if (strlen(key) != 26)
    {
        return false;
    };

    int letters[26] = {0};

    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        int index = toupper(key[i]) - 'A';

        // Check for duplicate characters
        if (letters[index] > 0)
        {
            return false;
        }
        letters[index]++;
    };

    return true;
};

// Function to substitute a character using the key, preserving case
char substitute(char c, string key)
{
    if (isupper(c))
    {
        return toupper(key[c - 'A']);
    }
    else if (islower(c))
    {
        return tolower(key[c - 'a']);
    }
    else
    {
        return c; // Non-alphabetical characters are unchanged
    };
};
```

## 📤 Expected Output

After compiling and running the program with a valid key, the user is prompted for plaintext, and the program then prints the corresponding ciphertext, for example:

```
$ ./substitution NQXPOMAFTRHLZGECYJIUWSKDVB
plaintext: HELLO
ciphertext: FOLLE
```

If the program is run incorrectly or with an invalid key, it prints an error message instead:

```
$ ./substitution
Usage: ./substitution key
```

```
$ ./substitution abcdefghijklmnopqrstuvwx
Key must contain 26 characters, each letter exactly once.
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Command-Line Arguments** – I reinforced how to access and validate command-line arguments in C using `argc` and `argv`, and how to handle cases where the program is run with an incorrect number of arguments.
- **Multi-Criteria Key Validation** – I learned how to validate a more complex input than a single numeric value, checking a key against several conditions at once: correct length, exclusively alphabetic characters, and no duplicate letters.
- **Tracking Seen Values with a Boolean Array** – I practiced using a boolean array (`seen`) indexed by letter position to efficiently detect duplicate characters in the key, a pattern broadly useful for uniqueness checks.
- **Character-to-Character Mapping** – I deepened my understanding of how to use a character's position in the alphabet as an index into another array (in this case, the key itself) to perform a direct substitution.
- **ASCII Arithmetic and Case Preservation** – I practiced using ASCII arithmetic (subtracting a base character like `'A'` or `'a'`) to convert a letter into a usable index, and functions like `toupper` and `tolower` from `ctype.h` to ensure the output matched the case of the original letter.
- **Selective Character Transformation** – I reinforced how to apply a transformation only to alphabetical characters while leaving punctuation, digits, and spaces in the input unchanged.
- **Program Exit Codes** – I practiced returning specific values from `main` (`0` for success, `1` for an error) to signal a program's execution status, a widely used convention in command-line tools.
- **Debugging Tools** – I gained further hands-on experience using `debug50` to step through the program's execution and inspect variable values, which helped me verify the key validation and substitution logic.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 2: Substitution](https://cs50.harvard.edu/x/psets/2/substitution/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
