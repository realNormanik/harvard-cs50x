# CS50X – Problem Set 6: DNA

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to extend CS50-provided distribution code to implement a simplified **DNA profiling** program in Python. The program identifies to whom a given DNA sequence belongs by counting the longest run of consecutive repeats of several **Short Tandem Repeats (STRs)** within that sequence, and comparing those counts against a CSV database of known individuals' STR profiles. If the computed STR counts exactly match an individual in the database, that person's name is printed; otherwise, the program reports no match, for example:

```
$ python dna.py databases/small.csv sequences/1.txt
Bob
```

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading and parsing CSV files in Python using the `csv` module, specifically `csv.DictReader`,
- reading a text file's full contents into memory using `open` and `read`,
- working with **lists of dictionaries** to represent tabular data loaded from a CSV file,
- using a provided helper function (`longest_match`) to compute the longest run of consecutive repeats of a given substring within a larger sequence,
- comparing computed values against database records to find an exact match, and handling the case where no match exists,
- validating command-line arguments in Python using `sys.argv`,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/6/dna.zip
   ```
2. Extracted the downloaded archive to create a folder called `dna`:
   ```bash
   unzip dna.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm dna.zip
   ```
4. Navigated into the `dna` folder:
   ```bash
   cd dna
   ```
5. Reviewed the provided distribution files (`dna.py`, along with the `databases/` and `sequences/` folders), noting the already-implemented `longest_match` helper function that computes the longest run of consecutive repeats of a given STR within a DNA sequence.
6. Implemented command-line argument validation, checking that the program was run with exactly two arguments (the CSV database filename and the DNA sequence filename), and printing an error message otherwise.
7. Implemented CSV reading logic using `csv.DictReader`, capturing the STR column names from the header row and loading each individual's row into a list of dictionaries for later comparison.
8. Implemented DNA sequence reading logic using `open` and `read` to load the full contents of the sequence file into a single string.
9. Implemented the core matching logic, calling `longest_match` for each STR against the DNA sequence to build a dictionary of computed STR counts, then iterating over the loaded database rows to find an individual whose STR counts matched exactly.
10. Implemented the final output logic, printing the matching individual's name if found, or `No match` otherwise.
11. Ran the program using the command:
    ```bash
    python dna.py databases/small.csv sequences/1.txt
    ```
12. Manually tested the program against every provided sequence file for both the small and large databases, confirming the output matched the expected name (or `No match`) in every case.
13. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/dna
    ```
14. Checked the code style using the `style50` tool:
    ```bash
    style50 dna.py
    ```
15. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/dna
    ```

## 💻 Program Code

The distribution code provided the `longest_match` helper function (used to compute the longest run of consecutive STR repeats). My work focused on implementing the `main` function and the surrounding program logic:

```python
import csv;
import sys;

def main():
    # Check for correct number of command-line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    database_file = sys.argv[1]
    sequence_file = sys.argv[2]

    # Read DNA database CSV into a list of dictionaries
    with open(database_file) as db:
        reader = csv.DictReader(db)
        # Extract STR names from the CSV header (excluding 'name')
        strs = reader.fieldnames[1:]
        # Read all rows (each is a dictionary)
        database = list(reader)

    # Read the DNA sequence to identify
    with open(sequence_file) as f:
        dna_sequence = f.read()

    # Find longest match of each STR in the DNA sequence
    str_counts = {}
    for STR in strs:
        str_counts[STR] = longest_match(dna_sequence, STR)

    # Check database for matching profiles
    for person in database:
        match = True
        for STR in strs:
            # Compare database STR count (string) with computed count (int)
            if int(person[STR]) != str_counts[STR]:
                match = False
                break
        if match:
            print(person["name"])
            return

    # If no match found
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    longest_run = 0
    sub_len = len(subsequence)
    seq_len = len(sequence)

    for i in range(seq_len):
        count = 0

        while True:
            start = i + count * sub_len
            end = start + sub_len

            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        if count > longest_run:
            longest_run = count

    return longest_run


if __name__ == "__main__":
    main()
```

## 📤 Expected Output

After compiling and running the program with a database and a DNA sequence file, the program prints the name of the matching individual, or reports that no match was found:

```
$ python dna.py databases/small.csv sequences/1.txt
Bob
```

```
$ python dna.py databases/small.csv sequences/2.txt
No match
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Reading CSV Files in Python** – I learned how to use `csv.DictReader` to conveniently read a CSV file's rows as dictionaries keyed by column name, eliminating the need to manually track column indices as would be required with a simpler CSV-parsing approach.
- **Extracting Header Information** – I practiced using `reader.fieldnames` to retrieve the CSV's column headers directly, and used slicing (`[1:]`) to isolate the STR names, skipping the leading `name` column.
- **Reading Text Files into Memory** – I reinforced the use of `open` and `read` to load an entire file's contents into a single string variable, a pattern applicable whenever a file's content needs to be processed as a whole rather than line by line.
- **Working with Lists of Dictionaries** – I practiced storing tabular data as a list of dictionaries (one dictionary per row), and iterating over that list to compare each record's values against computed results, a common and flexible pattern for handling small-to-medium datasets in Python without needing a full database.
- **Applying a Provided Helper Function** – I learned how to effectively make use of a pre-written function (`longest_match`) within my own logic, focusing my implementation effort on orchestrating the overall program flow rather than reimplementing string-matching logic from scratch.
- **Building and Comparing Result Dictionaries** – I practiced constructing a dictionary of computed STR counts and then using Python's `all` function combined with a generator expression to concisely check whether every STR count in a database row matched the corresponding computed count.
- **Command-Line Argument Validation** – I learned how to access and validate command-line arguments in Python using `sys.argv`, checking the argument count and printing a usage message with `sys.exit(1)` when the program was invoked incorrectly, mirroring similar patterns used in earlier C-based problem sets.
- **Applying Domain Knowledge to Code** – I gained a concrete understanding of how DNA profiling using Short Tandem Repeats works in practice, and how a real forensic technique can be modeled with relatively simple data structures and string-matching logic.
- **Testing Against a Comprehensive Set of Examples** – I practiced validating my implementation against every sequence file provided for both the small and large databases, which helped confirm the matching logic behaved correctly across a wide range of realistic scenarios, including cases with no match.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 6: DNA](https://cs50.harvard.edu/x/psets/6/dna/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
