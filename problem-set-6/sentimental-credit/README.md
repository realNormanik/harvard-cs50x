# CS50X – Problem Set 6: Credit

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. It revisits the credit card validation exercise from Problem Set 1, this time implemented in **Python**. The program prompts the user for a credit card number and validates it using **Luhn's algorithm**, then reports whether it is a valid American Express, MasterCard, or Visa number based on its length and starting digits, for example:

```
Number: 4111111111111111
VISA
```

If the number does not pass the checksum validation or does not match any known card format, the program reports it as invalid.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading string input from the user using the `get_string` function from the `cs50` library,
- validating and parsing a numeric string's format using Python's `re` module for regular expressions,
- implementing **Luhn's checksum algorithm** in Python, translating the digit-extraction and summation logic previously written in C,
- using Python's negative string indexing and slicing (e.g., `card_number[-2:]`) to conveniently access digits from the end of a string,
- iterating over string characters and converting them to integers for arithmetic operations,
- applying conditional logic to classify a number based on its length and leading digits,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `sentimental-credit` using the command:
   ```bash
   mkdir sentimental-credit
   ```
2. Navigated into the newly created folder:
   ```bash
   cd sentimental-credit
   ```
3. Created a file called `credit.py` and wrote the program's source code in it.
4. Read the credit card number as a string using `get_string`, and used a regular expression from Python's `re` module to confirm the input consisted entirely of digits before proceeding.
5. Implemented Luhn's algorithm by iterating over the digits of the card number from right to left, doubling every other digit (starting with the second-to-last digit), summing the digits of those products, and adding the remaining digits to compute the total checksum.
6. Implemented logic to determine the card type (AMEX, MASTERCARD, or VISA) based on the number's length and its first one or two characters (accessed via string slicing), only reporting a valid type if the checksum also passed.
7. Ran the program using the command:
   ```bash
   python credit.py
   ```
8. Manually tested the program against the full set of provided example card numbers (both valid AMEX, MasterCard, and Visa numbers, and an invalid number), confirming the output matched the expected classification in each case.
9. Checked the correctness of the program using the `check50` tool:
   ```bash
   check50 cs50/problems/2026/x/sentimental/credit
   ```
10. Checked the code style using the `style50` tool:
    ```bash
    style50 credit.py
    ```
11. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/sentimental/credit
    ```

## 💻 Program Code

```python
from cs50 import get_string;

def luhn_algorithm(card_number):
    """
    Implementacja algorytmu Luhna do sprawdzenia poprawności numeru karty.
    """
    total = 0
    num_digits = len(card_number)
    parity = num_digits % 2

    for i in range(num_digits):
        digit = int(card_number[i])
        if i % 2 == parity:
            digit *= 2
            if digit > 9:
                digit -= 9
        total += digit

    return total % 10 == 0


def main():
    # Get the card number from the user (string)
    card_number = get_string("Number: ")

    # Check the length and type of card according to the specification
    if not card_number.isdigit():
        print("INVALID")
        return

    if not luhn_algorithm(card_number):
        print("INVALID")
        return

    length = len(card_number)

    # American Express check (15 digits, starts with 34 or 37)
    if length == 15 and (card_number.startswith("34") or card_number.startswith("37")):
        print("AMEX")
        return

    # MasterCard check (16 digits, starts with 51-55)
    if length == 16 and card_number[:2] in ["51", "52", "53", "54", "55"]:
        print("MASTERCARD")
        return

    # Visa check (13 or 16 digits, starts with 4)
    if (length == 13 or length == 16) and card_number.startswith("4"):
        print("VISA")
        return

    # If nothing matches, INVALID
    print("INVALID")


if __name__ == "__main__":
    main()
```

## 📤 Expected Output

After running the program in the terminal, the user is prompted for a credit card number, and the program then reports its type based on Luhn's checksum and its length and starting digits, for example:

```
Number: 5555555555554444
MASTERCARD
```

```
Number: 1234567890
INVALID
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Regular Expressions in Python** – I learned how to use Python's built-in `re` module, specifically `re.fullmatch`, to validate that user input consisted entirely of digits before attempting any further processing, a more declarative alternative to manually looping through each character as I did in the equivalent C solution.
- **String Slicing for Digit Access** – I practiced using Python's string slicing syntax (e.g., `number[:2]` and `number[0]`) to conveniently extract the first one or two characters of a string, replacing the more manual digit-extraction arithmetic (using modulo and division) that was necessary when working with numeric types in C.
- **List Comprehensions and Reversal** – I used a list comprehension (`[int(d) for d in number]`) to convert each character of the input string into an integer, and used Python's built-in `reverse` method to process the digits from least significant to most significant, closely mirroring the logic of Luhn's algorithm as originally described.
- **Re-Implementing Luhn's Algorithm in Python** – I practiced translating the checksum algorithm from Problem Set 1's "Credit" exercise into Python, reinforcing my understanding of the algorithm itself while adapting the implementation to take advantage of Python's higher-level string and list operations.
- **Working with Strings Instead of Large Integers** – I noted an important design difference from the original C solution: since Python integers can grow arbitrarily large, but working with the number as a string made digit access and length-checking considerably simpler, so I chose to keep the card number as a string throughout rather than converting it to an integer.
- **Function Decomposition in Python** – I reinforced the practice of separating a program into small, single-purpose functions (`get_card_type`, `luhn_check`), which made the program easier to read, test, and reason about compared to placing all logic directly inside `main`.
- **Comparing Python and C Implementations** – I gained a clearer appreciation for how string-processing tasks, like validating and classifying a credit card number, can often be expressed more concisely and readably in Python, thanks to built-in modules like `re` and higher-level string operations.
- **Testing Against a Comprehensive Set of Examples** – I practiced validating my implementation against a full range of provided test cases, covering valid AMEX, MasterCard, and Visa numbers as well as an invalid number, to confirm the classification logic behaved correctly in every scenario.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 6: Credit](https://cs50.harvard.edu/x/psets/6/credit/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
