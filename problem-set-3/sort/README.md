# CS50X – Problem Set 3: Sort

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. Unlike previous problem sets, this task did not require writing a program from scratch. Instead, three pre-compiled C programs (`sort1`, `sort2`, and `sort3`) were provided, each implementing one of three sorting algorithms discussed in lecture: **selection sort**, **bubble sort**, and **merge sort** (in no particular order). The goal was to determine, through experimentation and observation, which algorithm each program implements, and to record the answers along with supporting explanations in a file called `answers.txt` in a folder called `sort`.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- the theoretical behavior and time complexity of three classic sorting algorithms: selection sort, bubble sort, and merge sort,
- how each algorithm's performance is affected by the initial ordering of the input data (already sorted, reversed, or randomly shuffled),
- using the `time` command in a Unix-like terminal to empirically measure a program's execution time,
- working with pre-compiled distribution code and downloading/extracting a ZIP archive using `wget` and `unzip`,
- drawing conclusions from experimental data rather than from reading source code directly, since the programs' source was not provided.

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/3/sort.zip
   ```
2. Extracted the downloaded archive to create a folder called `sort`:
   ```bash
   unzip sort.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm sort.zip
   ```
4. Navigated into the `sort` folder:
   ```bash
   cd sort
   ```
5. Explored the provided `.txt` input files to understand the different data sets available (already sorted, reversed, and randomly shuffled lists of varying sizes, such as `sorted10000.txt`, `reversed10000.txt`, and `random50000.txt`).
6. Ran each of the three programs (`sort1`, `sort2`, `sort3`) against these different input files, for example:
   ```bash
   ./sort1 reversed10000.txt
   ```
7. Timed each run using the `time` command to measure the actual elapsed execution time for each combination of program and input type:
   ```bash
   time ./sort1 reversed10000.txt
   time ./sort2 reversed10000.txt
   time ./sort3 reversed10000.txt
   ```
8. Repeated the timing tests across sorted, reversed, and randomly shuffled files of various sizes to observe consistent performance patterns for each program.
9. Compared the measured execution times against the theoretical best-case, average-case, and worst-case time complexities of selection sort (O(n²) in all cases), bubble sort (O(n) best case on sorted data, O(n²) otherwise), and merge sort (O(n log n) in all cases).
10. Recorded the conclusions for each program, along with supporting reasoning based on the timing observations, in `answers.txt`.
11. Checked the correctness of the submitted answers using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/sort
    ```
12. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/sort
    ```

## 📝 Analysis Approach

Since no source code was provided for `sort1`, `sort2`, and `sort3`, identifying each algorithm relied entirely on **empirical testing** rather than code inspection. The key insight used was that each of the three algorithms behaves differently depending on how "close to sorted" the input already is:

- **Bubble sort** performs very well (close to O(n)) on data that is already sorted or nearly sorted, since few or no swaps are needed, but performs poorly (O(n²)) on reversed or randomly shuffled data.
- **Selection sort** performs consistently poorly (O(n²)) regardless of the input's initial order, since it always scans the remaining unsorted portion of the list to find the minimum element.
- **Merge sort** performs consistently well (O(n log n)) regardless of the input's initial order, since it always divides and merges the list the same way.

By running each program against sorted, reversed, and randomly shuffled input files of the same size and comparing the measured execution times, it becomes possible to match each program to its underlying algorithm based on these characteristic performance patterns.

## 📄 `answers.txt` Structure

The `answers.txt` file follows the format below, filling in each `TODO` with the identified algorithm and a justification based on the timing observations:

```
sort1 uses: Bubble Sort

How do you know?: Has a fast runtime for the sorted datasets, but it performes poorer on bigger datasets of reversed and random numbers.

sort2 uses: Merge Sort

How do you know?: It's efficient in all the datasets.

sort3 uses: Selection Sort

How do you know?: It performs poorly on all three .txt files which contains larger datasets(50000) and it's faster while going through the smaller datasets(5000).
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Algorithmic Behavior in Practice** – I deepened my understanding of how the theoretical time complexity of selection sort, bubble sort, and merge sort translates into observable, measurable differences in real program execution time.
- **Empirical Analysis Without Source Code** – I learned how to reason about a program's underlying algorithm purely through experimentation and observation, a skill relevant to reverse engineering, performance profiling, and black-box testing.
- **Using `time` for Performance Measurement** – I practiced using the Unix `time` command to measure the real elapsed execution time of a program, and learned to interpret the `real`, `user`, and `sys` output values.
- **Impact of Input Ordering on Performance** – I gained a concrete, hands-on understanding of best-case, average-case, and worst-case scenarios for sorting algorithms, and how the initial order of input data (sorted, reversed, or shuffled) can dramatically affect an algorithm's runtime.
- **Working with Distribution Code** – I practiced downloading and extracting course-provided distribution code using `wget` and `unzip`, a common workflow when working with pre-existing codebases or datasets.
- **Structured Technical Reasoning** – I practiced clearly documenting my conclusions and the reasoning behind them in a written format (`answers.txt`), a skill valuable for technical writing and justifying engineering decisions.
- **Testing and Code Verification** – I practiced using CS50's `check50` tool to automatically verify the correctness of my submitted answers.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 3: Sort](https://cs50.harvard.edu/x/psets/3/sort/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
