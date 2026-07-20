# CS50X – Problem Set 6: Mario (Less)

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. It revisits the right-aligned half-pyramid exercise from Problem Set 1, this time implemented in **Python**. The program prompts the user for the pyramid's height (an integer between 1 and 8, inclusive) and then prints a right-aligned half-pyramid built out of hashes (`#`), for example:

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

The user is re-prompted, again and again, until a valid integer within the specified range is entered.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading and validating integer input in Python using the `get_int` function from the `cs50` library,
- using `while` loops in Python to repeatedly prompt the user until valid input is provided,
- using nested `for` loops (or Python's `range` function) to generate patterned, multi-line console output,
- applying string repetition and concatenation in Python (e.g., `" " * n` and `"#" * n`) as a concise alternative to character-by-character printing,
- translating a previously solved problem from C to Python, comparing syntax and idioms between the two languages,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `sentimental-mario-less` using the command:
   ```bash
   mkdir sentimental-mario-less
   ```
2. Navigated into the newly created folder:
   ```bash
   cd sentimental-mario-less
   ```
3. Created a file called `mario.py` and wrote the program's source code in it.
4. Implemented input validation using a `while True` loop combined with `get_int`, repeatedly prompting the user until an integer between 1 and 8 (inclusive) was entered.
5. Implemented the half-pyramid generation logic using nested loops, printing the appropriate number of leading spaces followed by the appropriate number of hashes on each row.
6. Ran the program using the command:
   ```bash
   python mario.py
   ```
7. Manually tested the program with a range of inputs, including negative numbers, `0`, `1`, `8`, `9`, non-numeric input (`foo`), and empty input, to confirm the program correctly rejected invalid values and produced correctly aligned pyramids for valid heights.
8. Checked the correctness of the program using the `check50` tool:
   ```bash
   check50 cs50/problems/2026/x/sentimental/mario/less
   ```
9. Checked the code style using the `style50` tool:
   ```bash
   style50 mario.py
   ```
10. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/sentimental/mario/less
    ```

## 💻 Program Code

```python
from cs50 import get_int

# Repeatedly prompt user until a valid height is provided
while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# Generate half-pyramid
for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i)
```

## 📤 Expected Output

After running the program in the terminal, the user is prompted for the pyramid's height and, once a valid value between 1 and 8 is entered, the program prints a right-aligned half-pyramid of that height, for example:

```
Height: 4
   #
  ##
 ###
####
```

If the user enters an invalid value (a non-integer, a negative number, `0`, or a number greater than `8`), the program keeps re-prompting until a valid height is provided.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Input Validation in Python** – I learned how to use a `while True` loop paired with a `return` statement inside a dedicated helper function (`get_height`) to cleanly express "keep prompting until valid input is received," an idiom that reads more directly in Python than the equivalent `do while` loop used in C.
- **Range-Based Validation** – I practiced validating that user input falls within an inclusive numeric range using Python's chained comparison syntax (`1 <= height <= 8`), which is more concise than the equivalent compound condition in C.
- **String Multiplication for Pattern Generation** – I learned how Python allows strings to be "multiplied" by an integer (e.g., `"#" * i`) to repeat a character a given number of times, replacing the need for an inner loop that prints one character at a time, as was necessary in C.
- **Using `range` for Loop Control** – I practiced using Python's `range` function to iterate over a sequence of row numbers, and reasoned about how to calculate the correct number of spaces and hashes for each row based on the loop variable and the total height.
- **Translating a Solved Problem to a New Language** – I gained valuable experience revisiting a problem I had already solved in C and reimplementing it in Python, which helped highlight both the similarities in underlying logic and the differences in syntax, verbosity, and available built-in tools between the two languages.
- **Function Decomposition in Python** – I reinforced good practice by separating the input-validation logic into its own function (`get_height`), keeping `main` focused on the higher-level flow of the program.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 6: Mario (Less)](https://cs50.harvard.edu/x/psets/6/mario/less/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
