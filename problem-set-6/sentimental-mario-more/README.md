# CS50X – Problem Set 6: Mario (More)

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. It revisits the two adjacent half-pyramids exercise from Problem Set 1, this time implemented in **Python**. The program prompts the user for the pyramids' height (an integer between 1 and 8, inclusive) and then prints two mirrored, right-aligned/left-aligned half-pyramids side by side, separated by a two-space gap, built out of hashes (`#`), for example:

```
       #  #
      ##  ##
     ###  ###
    ####  ####
   #####  #####
  ######  ######
 #######  #######
########  ########
```

The user is re-prompted, again and again, until a valid integer within the specified range is entered.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading and validating integer input in Python using the `get_int` function from the `cs50` library,
- using `while` loops in Python to repeatedly prompt the user until valid input is provided,
- using loops (or Python's `range` function) to generate more complex, multi-part patterned console output,
- applying string repetition and concatenation in Python (e.g., `" " * n` and `"#" * n`) to build a single formatted row combining spaces, bricks, and a fixed-width gap,
- translating a previously solved problem from C to Python, extending single-pyramid logic to handle two mirrored pyramids,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `sentimental-mario-more` using the command:
   ```bash
   mkdir sentimental-mario-more
   ```
2. Navigated into the newly created folder:
   ```bash
   cd sentimental-mario-more
   ```
3. Created a file called `mario.py` and wrote the program's source code in it.
4. Implemented input validation using a `while True` loop combined with `get_int`, repeatedly prompting the user until an integer between 1 and 8 (inclusive) was entered.
5. Implemented the two-pyramid generation logic using a loop, printing, for each row, the appropriate number of leading spaces, the left pyramid's hashes, a fixed two-space gap, and the right pyramid's hashes.
6. Ran the program using the command:
   ```bash
   python mario.py
   ```
7. Manually tested the program with a range of inputs, including negative numbers, `0`, `1`, `8`, `9`, non-numeric input (`foo`), and empty input, to confirm the program correctly rejected invalid values and produced correctly aligned, mirrored pyramids for valid heights.
8. Checked the correctness of the program using the `check50` tool:
   ```bash
   check50 cs50/problems/2026/x/sentimental/mario/more
   ```
9. Checked the code style using the `style50` tool:
   ```bash
   style50 mario.py
   ```
10. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/sentimental/mario/more
    ```

## 💻 Program Code

```python
from cs50 import get_int

# Repeatedly prompt until user provides a valid height
while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# Generate two half-pyramids with a gap of 2 spaces
for i in range(1, height + 1):
    spaces = " " * (height - i)
    hashes = "#" * i
    print(f"{spaces}{hashes}  {hashes}")
```

## 📤 Expected Output

After running the program in the terminal, the user is prompted for the pyramids' height and, once a valid value between 1 and 8 is entered, the program prints two mirrored half-pyramids side by side, for example:

```
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####
```

If the user enters an invalid value (a non-integer, a negative number, `0`, or a number greater than `8`), the program keeps re-prompting until a valid height is provided.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Extending Existing Logic** – I practiced building on the single-pyramid pattern from the earlier "Mario (Less)" exercise and extending it to print two mirrored pyramids with a fixed gap between them, reinforcing how a small, well-understood pattern can be adapted to solve a related, slightly more complex problem.
- **Combining String Building Blocks** – I learned how to compose a single row of output from multiple pieces (leading spaces, left pyramid bricks, a fixed gap, right pyramid bricks) using an f-string, which kept the row-generation logic in one clear, readable line rather than several separate `print` calls.
- **String Multiplication for Pattern Generation** – I reinforced how Python's string repetition (`"#" * i`) can replace what would otherwise require nested loops in C, making the row-building logic considerably more concise.
- **Precise Output Formatting** – I practiced ensuring exact formatting requirements were met, such as maintaining a constant two-character gap between the pyramids regardless of height, and avoiding any trailing whitespace after the final character on each line.
- **Input Validation in Python** – I reinforced the use of a `while True` loop paired with a `return` statement inside a dedicated helper function (`get_height`) to cleanly express "keep prompting until valid input is received."
- **Comparing Python and C Implementations** – I gained a clearer appreciation for how the same underlying algorithm (two mirrored, incrementally sized rows of bricks) can be expressed far more concisely in Python than in C, largely thanks to built-in string operations and f-strings.
- **Testing Edge Cases** – I practiced testing the program against a wide range of inputs, including negative numbers, zero, values outside the valid range, non-numeric input, and empty input, to ensure robust input handling.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 6: Mario (More)](https://cs50.harvard.edu/x/psets/6/mario/more/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
