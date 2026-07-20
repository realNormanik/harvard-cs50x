# CS50X – Problem Set 2: Scrabble

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to write a program in C that determines the winner of a short Scrabble-like game. The program prompts two players for a word each, computes each word's score by summing the point values of its letters (as defined by the official Scrabble letter values), and then announces the winner, for example:

```
Player 1: COMPUTER
Player 2: science
Player 1 wins!
```

If both words score the same number of points, the program announces a tie instead.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading string input from the user using the `get_string` function from the CS50 library (`cs50.h`),
- working with arrays to associate data (letter point values) with an index,
- using ASCII character values and pointer/character arithmetic to map letters to array indices,
- using the `isupper`, `islower`, and `strlen` functions from `ctype.h` and `string.h`,
- writing and calling custom functions that process and return computed values,
- using conditional logic (`if` / `else if` / `else`) to compare results and determine an outcome,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `scrabble` using the command:
   ```bash
   mkdir scrabble
   ```
2. Navigated into the newly created folder:
   ```bash
   cd scrabble
   ```
3. Created a file called `scrabble.c` and wrote the program's source code in it.
4. Started with minimal, compilable code and gradually built up the solution using pseudocode comments as a guide.
5. Declared a global array (`POINTS`) storing the point value of each letter of the alphabet, accessible to any function in the program.
6. Implemented a `compute_score` function that iterates over each character of a word, determines its point value (handling both uppercase and lowercase letters, and ignoring non-letter characters), and returns the total score.
7. Compiled the program using the command:
   ```bash
   make scrabble
   ```
8. Ran the compiled program:
   ```bash
   ./scrabble
   ```
9. Manually tested the program with a range of word pairs, including mixed-case words and words containing punctuation, to confirm scores and outcomes matched expectations.
10. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/scrabble
    ```
11. Checked the code style using the `style50` tool:
    ```bash
    style50 scrabble.c
    ```
12. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/scrabble
    ```

## 💻 Program Code

```c
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Scrabble scoring for A-Z
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// A function that counts points for a word
int compute_score(string word);

int main(void)
{
    // Get words from players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Calculate the points
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Compare and write out the result
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    };
};

int compute_score(string word)
{
    int score = 0;

    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isalpha(word[i]))
        {
            // Replace letter with index 0-25 (regardless of size)
            int index = toupper(word[i]) - 'A';
            score += POINTS[index];
        };
    };

    return score;
};
```

## 📤 Expected Output

After running the compiled program in the terminal, both players are prompted for a word, and the program then announces the winner based on the computed Scrabble scores, for example:

```
Player 1: Scrabble
Player 2: wiNNeR
Player 1 wins!
```

```
Player 1: Question?
Player 2: Question!
Tie!
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Arrays for Data Lookup** – I learned how to use a fixed-size array (`POINTS`) as a lookup table, mapping each letter of the alphabet to its corresponding point value by index.
- **ASCII and Character Arithmetic** – I understood how characters are represented internally using ASCII values, and how subtracting a base character (such as `'A'` or `'a'`) from a letter yields a usable array index (e.g., `word[i] - 'A'`).
- **Case-Insensitive Processing** – I practiced using the `isupper` and `islower` functions from `ctype.h` to correctly handle both uppercase and lowercase letters, while ignoring non-letter characters such as punctuation.
- **String Length and Iteration** – I reinforced my understanding of the `strlen` function from `string.h` and how to iterate safely over the characters of a string using a `for` loop.
- **Function Abstraction** – I learned how identifying repeated logic (scoring two different words using the same rules) is a strong signal for extracting that logic into a single, reusable function (`compute_score`).
- **Conditional Comparisons** – I practiced using `if` / `else if` / `else` statements to compare two computed values and determine one of three possible outcomes (Player 1 wins, Player 2 wins, or a tie).
- **Testing with Real-World Examples** – I practiced testing the program with mixed-case input and punctuation to ensure the scoring logic behaved correctly under a variety of realistic conditions.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 2: Scrabble](https://cs50.harvard.edu/x/psets/2/scrabble/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
