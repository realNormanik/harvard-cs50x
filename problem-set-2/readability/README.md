# CS50X – Problem Set 2: Readability

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to write a program in C that estimates the approximate U.S. grade level required to comprehend a given piece of text, using the **Coleman-Liau index**, a well-known readability formula. The program prompts the user for a block of text, analyzes it, and prints the computed grade level, for example:

```
Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
Grade 3
```

If the computed grade level is 16 or higher, the program prints `Grade 16+` instead of an exact number. If the computed grade level is below 1, the program prints `Before Grade 1`.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading string input from the user using the `get_string` function from the CS50 library (`cs50.h`),
- iterating over characters in a string to classify and count them (letters, words, and sentences),
- using functions from `ctype.h` (such as `isalpha`) to identify alphabetical characters,
- implementing and applying a real-world mathematical formula (the Coleman-Liau index) in code,
- performing floating-point arithmetic in C, including proper type casting to avoid integer truncation,
- using the `round` function from `math.h` to round a computed value to the nearest integer,
- structuring a program using multiple custom functions, each with a single, clear responsibility,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `readability` using the command:
   ```bash
   mkdir readability
   ```
2. Navigated into the newly created folder:
   ```bash
   cd readability
   ```
3. Created a file called `readability.c` and wrote the program's source code in it.
4. Started with minimal, compilable code and gradually built up the solution using pseudocode comments as a guide.
5. Implemented a `count_letters` function that iterates over the input text and counts alphabetical characters, ignoring digits, punctuation, and spaces.
6. Implemented a `count_words` function that counts words by relating the number of words to the number of spaces in the text.
7. Implemented a `count_sentences` function that counts sentences by identifying sentence-terminating characters (`.`, `!`, and `?`).
8. Computed the Coleman-Liau index using the formula `index = 0.0588 * L - 0.296 * S - 15.8`, where `L` is the average number of letters per 100 words and `S` is the average number of sentences per 100 words, taking care to cast values to `float` to avoid integer truncation during division.
9. Rounded the resulting index using the `round` function and applied the required output rules (`Grade X`, `Grade 16+`, or `Before Grade 1`).
10. Compiled the program using the command:
    ```bash
    make readability
    ```
11. Ran the compiled program:
    ```bash
    ./readability
    ```
12. Manually tested the program against a set of provided sample texts with known expected grade levels to confirm the formula was implemented correctly.
13. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/readability
    ```
14. Checked the code style using the `style50` tool:
    ```bash
    style50 readability.c
    ```
15. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/readability
    ```

## 💻 Program Code

```c
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Get the text
    string text = get_string("Text: ");

    // Counting ingredients
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Index calculations
    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Rounding up
    int grade = round(index);

    // Writing out the result
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    };
};

// Counts letters (a-z, A-Z)
int count_letters(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
};

// Word counts (separated by spaces)
int count_words(string text)
{
    int count = 1; // The first word begins without spaces
    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            count++;
        }
    }
    return count;
};

// Count sentences (ending with ., ! or ?)
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
};
```

## 📤 Expected Output

After running the compiled program in the terminal, the user is prompted for a block of text, and the program then prints the estimated grade level required to understand it, for example:

```
Text: In my younger and more vulnerable years my father gave me some advice that I've been turning over in my mind ever since.
Grade 7
```

```
Text: One fish. Two fish. Red fish. Blue fish.
Before Grade 1
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Applying a Mathematical Formula in Code** – I learned how to translate a real-world formula (the Coleman-Liau readability index) into working C code, including correctly identifying which variables needed to be computed beforehand.
- **Character Classification** – I practiced using the `isalpha` function from `ctype.h` to distinguish alphabetical characters from digits, punctuation, and whitespace when counting letters, and the `isspace` function to reliably detect word boundaries.
- **Text Analysis via Character Iteration** – I strengthened my ability to iterate over a string character by character to extract meaningful counts (letters, words, and sentences), and to reason about the relationship between delimiters (spaces, sentence-ending punctuation) and the quantities they represent.
- **Floating-Point Arithmetic and Type Casting** – I understood why dividing two `int` values in C truncates the result, and learned to explicitly cast operands to `float` to preserve precision when computing averages.
- **Rounding Values** – I learned how to use the `round` function from `math.h` to round a computed floating-point index to the nearest whole grade level.
- **Function Decomposition** – I reinforced the practice of breaking a problem into independent, single-purpose functions (`count_letters`, `count_words`, `count_sentences`), which made the program easier to write, test, and debug.
- **Boundary Condition Handling** – I practiced applying specific output rules for edge cases, such as printing `Grade 16+` for advanced texts and `Before Grade 1` for very simple texts, instead of an exact numeric grade.
- **Testing Against Known Benchmarks** – I practiced validating my program's correctness by comparing its output against a set of texts with pre-determined expected grade levels, which helped confirm the formula was implemented accurately.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 2: Readability](https://cs50.harvard.edu/x/psets/2/readability/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
