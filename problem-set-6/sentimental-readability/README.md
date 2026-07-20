# CS50X – Problem Set 6: Readability

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. It revisits the readability-grading exercise from Problem Set 2, this time implemented in **Python**. The program prompts the user for a block of text, analyzes it using the **Coleman-Liau index** formula, and prints the estimated U.S. grade level required to comprehend it, for example:

```
Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
Grade 3
```

If the computed grade level is 16 or higher, the program prints `Grade 16+` instead of an exact number. If the computed grade level is below 1, the program prints `Before Grade 1`.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading string input from the user using the `get_string` function from the `cs50` library,
- iterating over characters in a string in Python to classify and count them (letters, words, and sentences),
- using Python's built-in string methods (such as `isalpha` and `split`) to simplify text analysis compared to the equivalent C implementation,
- implementing and applying a real-world mathematical formula (the Coleman-Liau index) in Python,
- using Python's built-in `round` function to round a computed value to the nearest integer, without needing to import a separate math library as required in C,
- structuring a program using multiple functions, each with a single, clear responsibility,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `sentimental-readability` using the command:
   ```bash
   mkdir sentimental-readability
   ```
2. Navigated into the newly created folder:
   ```bash
   cd sentimental-readability
   ```
3. Created a file called `readability.py` and wrote the program's source code in it.
4. Implemented a `count_letters` function that iterates over the input text and counts alphabetical characters using Python's built-in `str.isalpha` method, ignoring digits, punctuation, and spaces.
5. Implemented a `count_words` function that counts words by using Python's built-in `str.split` method, which conveniently splits a string on whitespace and handles any number of separating spaces.
6. Implemented a `count_sentences` function that counts sentences by iterating over the text and identifying sentence-terminating characters (`.`, `!`, and `?`).
7. Computed the Coleman-Liau index using the formula `index = 0.0588 * L - 0.296 * S - 15.8`, where `L` is the average number of letters per 100 words and `S` is the average number of sentences per 100 words, relying on Python's automatic handling of floating-point division.
8. Rounded the resulting index using Python's built-in `round` function and applied the required output rules (`Grade X`, `Grade 16+`, or `Before Grade 1`).
9. Ran the program using the command:
   ```bash
   python readability.py
   ```
10. Manually tested the program against the full set of provided sample texts with known expected grade levels, confirming the output matched in every case, from "Before Grade 1" up through "Grade 16+".
11. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/sentimental/readability
    ```
12. Checked the code style using the `style50` tool:
    ```bash
    style50 readability.py
    ```
13. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/sentimental/readability
    ```

## 💻 Program Code

```python
from cs50 import get_string;

def main():
    # Prompt the user to enter a text string
    text = get_string("Text: ")

    # Count the total number of letters in the input text
    letters = count_letters(text)
    # Count the total number of words in the input text
    words = count_words(text)
    # Count the total number of sentences in the input text
    sentences = count_sentences(text)

    # Calculate the average number of letters per 100 words
    L = (letters / words) * 100
    # Calculate the average number of sentences per 100 words
    S = (sentences / words) * 100

    # Compute the Coleman-Liau index using the formula:
    # index = 0.0588 * L - 0.296 * S - 15.8
    index = 0.0588 * L - 0.296 * S - 15.8
    # Round the index to the nearest whole number to get the grade level
    grade = round(index)

    # Determine the readability grade level to print
    if grade < 1:
        # If grade is less than 1, print special message
        print("Before Grade 1")
    elif grade >= 16:
        # If grade is 16 or higher, print "Grade 16+"
        print("Grade 16+")
    else:
        # Otherwise, print the grade number
        print(f"Grade {grade}")


def count_letters(text):
    count = 0
    # Iterate over every character in the text
    for char in text:
        # Check if the character is an alphabetical letter (A-Z or a-z)
        if char.isalpha():
            count += 1  # Increment letter count if true
    return count  # Return total letters counted


def count_words(text):
    # Split the text into words by spaces (assuming words are separated by spaces)
    words = text.split()
    # Return the total number of words
    return len(words)


def count_sentences(text):
    count = 0
    # Iterate over every character in the text
    for char in text:
        # Check if the character indicates end of a sentence
        if char in ['.', '!', '?']:
            count += 1  # Increment sentence count
    return count  # Return total sentences counted


if __name__ == "__main__":
    main()
```

## 📤 Expected Output

After running the program in the terminal, the user is prompted for a block of text, and the program then prints the estimated grade level required to understand it, for example:

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

- **Built-In String Methods for Text Analysis** – I learned how Python's built-in `str.isalpha` and `str.split` methods can replace much of the manual character-by-character logic that was necessary in the equivalent C solution, considerably simplifying the letter- and word-counting functions.
- **Generator Expressions with `sum`** – I practiced using a generator expression combined with `sum` (e.g., `sum(1 for char in text if char.isalpha())`) as a concise, idiomatic way to count characters matching a condition, an approach with no direct equivalent in C's explicit loop-and-counter style.
- **Applying a Mathematical Formula in Python** – I re-implemented the Coleman-Liau readability formula in Python, and noted that Python's automatic handling of floating-point division (unlike C, where dividing two integers truncates the result) removed the need for explicit type casting that was required in the original C implementation.
- **Rounding Without External Libraries** – I learned that Python's built-in `round` function made rounding the computed index straightforward, without needing to `import` a dedicated math library, as was necessary with C's `round` function from `math.h`.
- **Function Decomposition in Python** – I reinforced the practice of separating a program into small, single-purpose functions (`count_letters`, `count_words`, `count_sentences`, `grade`), making the program easier to read, test, and debug, consistent with the same approach used in the original C solution.
- **Boundary Condition Handling** – I practiced applying specific output rules for edge cases, such as printing `Grade 16+` for advanced texts and `Before Grade 1` for very simple texts, instead of an exact numeric grade.
- **Comparing Python and C Implementations** – I gained a clearer appreciation for how Python's higher-level string and iteration tools can significantly reduce the amount of code needed to solve the same text-processing problem previously solved in C, while producing identical results.
- **Testing Against Known Benchmarks** – I practiced validating my program's correctness by comparing its output against a set of texts with pre-determined expected grade levels, which helped confirm the formula was implemented accurately.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 6: Readability](https://cs50.harvard.edu/x/psets/6/readability/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
