# CS50X – Problem Set 1: Credit

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to write a program in C that validates a given credit card number using **Luhn's algorithm** and determines whether it is a valid American Express, MasterCard, or Visa number based on its length and starting digits, for example:

```
Number: 4003600000000014
VISA
```

If the number does not pass the checksum validation or does not match any known card format, the program reports it as invalid:

```
Number: 6176292929
INVALID
```

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading large numeric input safely using the `get_long` function from the CS50 library (`cs50.h`), since credit card numbers do not fit in a standard `int`,
- implementing **Luhn's checksum algorithm** to validate numeric sequences,
- extracting and manipulating individual digits of a number using arithmetic operators (`%` and `/`),
- applying conditional logic to classify a number based on its length and leading digits,
- structuring a program using custom functions with clear, single responsibilities,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Created a folder called `credit` using the command:
   ```bash
   mkdir credit
   ```
2. Navigated into the newly created folder:
   ```bash
   cd credit
   ```
3. Created a file called `credit.c` and wrote the program's source code in it.
4. Implemented input reading using `get_long`, ensuring the program could handle numbers too large to fit in an `int`.
5. Implemented Luhn's algorithm by iterating over the digits of the card number, doubling every other digit (starting from the second-to-last digit), summing the digits of those products, and adding the remaining digits to compute the total checksum.
6. Implemented logic to determine the card type (AMEX, MASTERCARD, or VISA) based on the number of digits and its starting digits, only reporting a valid type if the checksum also passed.
7. Compiled the program using the command:
   ```bash
   make credit
   ```
8. Ran the compiled program:
   ```bash
   ./credit
   ```
9. Manually tested the program with a variety of valid and invalid card numbers, including test numbers recommended by PayPal, to confirm correct classification.
10. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/credit
    ```
11. Checked the code style using the `style50` tool:
    ```bash
    style50 credit.c
    ```
12. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/credit
    ```

## 💻 Program Code

```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get your credit card number from the user
    long number = get_long("Number: ");
    long cc = number;

    int sum = 0;
    int position = 0;
    int digit;

    // Variables to check the first digits of the card
    int first_two = 0;
    int first_digit = 0;

    // A loop that analyzes the digits of the card number from the end
    while (cc > 0)
    {
        digit = cc % 10;

        // Every second digit from the end (even position - 0, 2, 4...) added without change
        if (position % 2 == 0)
        {
            sum += digit;
        }
        // The remaining digits are multiplied by 2, and their digits are added to the total
        else
        {
            int product = digit * 2;
            sum += product / 10 + product % 10;
        }

        // Keep the first two digits
        if (cc < 100 && cc >= 10)
        {
            first_two = cc;
        }

        // Keep the first digit (for VISA)
        if (cc < 10)
        {
            first_digit = cc;
        }

        cc /= 10;
        position++;
    };

    // Check if the sum according to Luhn's algorithm ends in 0
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Check the type of card by length and initial digits
    if ((position == 15) && (first_two == 34 || first_two == 37))
    {
        printf("AMEX\n");
    }
    else if ((position == 16) && (first_two >= 51 && first_two <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((position == 13 || position == 16) && (first_digit == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    };
};
```

## 📤 Expected Output

After running the compiled program in the terminal, the user is prompted for a credit card number, and the program then reports its type based on Luhn's checksum and its length and starting digits, for example:

```
Number: 4003600000000014
VISA
```

```
Number: 6176292929
INVALID
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Luhn's Algorithm** – I learned how a real-world checksum algorithm works and implemented it step by step: doubling alternating digits, summing the digits of the resulting products, and combining that with the remaining digits to validate a number.
- **Digit Extraction** – I practiced extracting individual digits from a large number using the modulo (`%`) and integer division (`/`) operators, a fundamental technique for working with numeric data digit by digit.
- **Working with Large Numbers** – I understood why an `int` is insufficient for storing a 15- or 16-digit credit card number and learned to use the `long` data type along with `get_long` to read such values safely.
- **Conditional Logic for Classification** – I practiced combining multiple conditions (checksum validity, digit count, and starting digits) to correctly classify a number as AMEX, MASTERCARD, VISA, or INVALID.
- **Edge Case Handling** – I learned the importance of validating input, not only in terms of format (e.g., using `get_long` to reject non-numeric input) but also in terms of logical validity (e.g., rejecting numeric strings that are not valid card numbers, such as phone numbers).
- **Testing with Real-World Data** – I practiced testing my program against a set of known valid and invalid card numbers, which reinforced the importance of thorough testing when working with algorithms tied to real-world formats and standards.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 1: Credit](https://cs50.harvard.edu/x/psets/1/credit/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
