# CS50X – Problem Set 6: Cash

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. It revisits the change-making exercise from Problem Set 1, this time implemented in **Python**, with the added twist that the user now enters the amount of change owed in **dollars** (e.g., `9.75`) rather than in cents. The program prompts the user for a non-negative dollar amount and prints the minimum number of coins (quarters, dimes, nickels, and pennies) needed to make that amount of change, for example:

```
Change owed: 4.2
18
```

The user is re-prompted, again and again, until a valid, non-negative numeric amount is entered.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading and validating floating-point input in Python using the `get_float` function from the `cs50` library,
- using `while` loops in Python to repeatedly prompt the user until valid input is provided,
- converting a dollar amount to an integer number of cents, while accounting for the inherent imprecision of floating-point arithmetic in computer systems,
- implementing a **greedy algorithm** in Python to compute the minimum number of coins, mirroring the same logic used in the original C solution but expressed with Python's simpler syntax,
- using integer division (`//`) and the modulo operator (`%`) in Python to repeatedly extract coin counts from a running total,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `sentimental-cash` using the command:
   ```bash
   mkdir sentimental-cash
   ```
2. Navigated into the newly created folder:
   ```bash
   cd sentimental-cash
   ```
3. Created a file called `cash.py` and wrote the program's source code in it.
4. Implemented input validation using a `while True` loop combined with `get_float`, repeatedly prompting the user until a non-negative dollar amount was entered.
5. Converted the validated dollar amount into an integer number of cents, using `round` to guard against floating-point precision issues (e.g., ensuring `4.20` dollars was reliably treated as exactly `420` cents rather than something like `419.999999`).
6. Implemented the greedy coin-counting algorithm, using integer division and the modulo operator to determine how many quarters, dimes, nickels, and pennies were needed, working from the largest denomination down to the smallest.
7. Ran the program using the command:
   ```bash
   python cash.py
   ```
8. Manually tested the program against the full set of provided example inputs (`0.41`, `0.01`, `0.15`, `1.60`, `23`, `4.2`), as well as invalid inputs like `-1`, non-numeric text, and empty input, confirming the program's output and re-prompting behavior matched expectations in every case.
9. Checked the correctness of the program using the `check50` tool:
   ```bash
   check50 cs50/problems/2026/x/sentimental/cash
   ```
10. Checked the code style using the `style50` tool:
    ```bash
    style50 cash.py
    ```
11. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/sentimental/cash
    ```

## 💻 Program Code

```python
from cs50 import get_float;

# Ask for a value until the user provides a non-negative number
while True:
    change = get_float("Change owed: ")
    if change >= 0:
        break

# Converting dollars to cents (we round up to avoid float problems)
cents = round(change * 100)

coins = 0

# We use the largest coins sequentially: 25, 10, 5, 1
for coin_value in [25, 10, 5, 1]:
    coins += cents // coin_value
    cents %= coin_value

print(coins)
```

## 📤 Expected Output

After running the program in the terminal, the user is prompted for the change owed in dollars, and the program then prints the minimum number of coins needed, for example:

```
Change owed: 23
92
```

If the user enters an invalid value (a non-numeric input or a negative number), the program keeps re-prompting until a valid amount is provided.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Handling Floating-Point Input** – I learned how to use `get_float` to accept dollar-and-cents input directly from the user, and understood why converting that value to an integer number of cents (using `round`) was essential to avoid subtle bugs caused by floating-point representation errors, which could otherwise cause an amount like `4.20` to be stored internally as something like `4.199999999999999`.
- **Reusing a Greedy Algorithm Across Languages** – I practiced re-implementing the same greedy coin-counting algorithm from Problem Set 1's "Cash" exercise, this time in Python, and saw firsthand how Python's built-in integer division (`//`) and modulo (`%`) operators allowed me to condense what previously required a `while` loop per denomination in C into a single, compact `for` loop over a list of coin values.
- **Iterating Over a List of Values** – I learned how to iterate over a list of denominations (`[25, 10, 5, 1]`) in a single loop, applying the same logic to each value in turn rather than writing separate, repetitive code for each coin type.
- **Combining Input Validation and Unit Conversion** – I practiced structuring a program so that a value is first validated (ensuring it's non-negative), and only afterward converted into the units actually needed for computation (cents instead of dollars), keeping each concern in its own clearly named function.
- **Function Decomposition in Python** – I reinforced the practice of separating a program into small, single-purpose functions (`get_change`, `dollars_to_cents`, `calculate_coins`), which made the program easier to read, test, and reason about compared to placing all logic directly inside `main`.
- **Comparing Python and C Implementations** – I gained a clearer appreciation for how the same underlying algorithm can be expressed far more concisely in Python, thanks to built-in operators and simpler iteration constructs, while still requiring the same careful attention to correctness (particularly around floating-point precision) as the original C solution.
- **Testing Against a Comprehensive Set of Examples** – I practiced validating my implementation against a full range of provided test cases, which helped confirm that both the coin-counting logic and the dollar-to-cents conversion behaved correctly across a variety of realistic inputs.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 6: Cash](https://cs50.harvard.edu/x/psets/6/cash/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
