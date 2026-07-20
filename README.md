# CS50x: Introduction to Computer Science — Problem Sets

This repository contains my solutions to the problem sets from **[CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/)**, Harvard University's introductory course to the intellectual enterprises of computer science and the art of programming, taught by David J. Malan.

Over the course of this class, I moved from writing my very first "hello, world" program in C through to building a full-stack web application with Flask and SQL — along the way exploring memory management, data structures, algorithms, and several different programming languages and paradigms.

## 📚 About the Course

CS50 is Harvard University's introduction to the intellectual enterprises of computer science and the art of programming. The course teaches students how to think algorithmically and solve problems efficiently, covering topics such as abstraction, algorithms, data structures, encapsulation, resource management, security, software engineering, and web development. Languages used throughout the course include **C, Python, SQL, HTML, CSS, and JavaScript**.

## 🗂️ Repository Structure

Each folder in this repository corresponds to one problem set exercise, and includes its own `README.md` describing the specific problem, my implementation, and what I learned from it in more detail.

| Problem Set | Topic | Projects |
|---|---|---|
| Problem Set 1 | C Fundamentals | `world` (Hello, World), `me` (Hello, Name), `mario-less` / `mario-more` (loops & functions), `cash` (greedy algorithms), `credit` (Luhn's algorithm) |
| Problem Set 2 | Arrays | `scrabble` (arrays & scoring), `readability` (text analysis), `caesar` (cryptography) |
| Problem Set 3 | Algorithms | `substitution` (cryptography), `sort` (algorithm analysis), `plurality` / `runoff` / `tideman` (voting algorithms, structs, recursion) |
| Problem Set 4 | Memory | `volume` (binary file I/O), `filter-less` / `filter-more` (2D arrays, image processing), `recover` (forensic data recovery) |
| Problem Set 5 | Data Structures | `inheritance` (dynamic memory, recursion, trees), `speller` (custom hash table implementation) |
| Problem Set 6 | Python | `sentimental-hello`, `sentimental-mario-less` / `sentimental-mario-more`, `sentimental-cash`, `sentimental-credit`, `sentimental-readability` (C-to-Python translations), `dna` (DNA profiling with CSV parsing) |
| Problem Set 7 | SQL | `songs`, `movies` (relational queries, joins, subqueries), `fiftyville` (open-ended database investigation) |
| Problem Set 8 | HTML, CSS, JavaScript | `trivia` (DOM manipulation, event listeners), `homepage` (multi-page site with Bootstrap) |
| Problem Set 9 | Flask | `birthdays` (basic CRUD web app), `finance` (full-stack stock trading simulation with authentication) |

## 🎯 What I Learned

Working through CS50 gave me a broad, hands-on foundation across nearly every core area of computer science:

- **Programming fundamentals** — variables, conditionals, loops, functions, and how to break a large problem down into smaller, solvable pieces, first in C and later in Python.
- **Memory management** — how pointers, arrays, and dynamic memory allocation (`malloc`/`free`) work under the hood, and how to avoid memory leaks and undefined behavior, verified using tools like `valgrind`.
- **Data structures and algorithms** — implementing and reasoning about linked lists, trees, and hash tables from scratch, along with searching, sorting, and their real-world performance characteristics ("wall-clock" time versus theoretical complexity).
- **Recursion** — designing recursive solutions for problems like family trees, graph cycle detection, and hash table teardown, and recognizing when recursion offers a cleaner solution than iteration.
- **Algorithmic thinking applied to real problems** — greedy algorithms for making change, cryptographic ciphers (Caesar and substitution ciphers), checksum validation (Luhn's algorithm), image processing (convolution kernels and the Sobel operator), and voting theory (plurality, runoff, and ranked-pairs/Condorcet methods).
- **File I/O and binary data** — reading and writing structured binary formats (WAV audio and BMP images) byte by byte, and recovering deleted files from raw forensic disk images by recognizing file signatures.
- **Databases and SQL** — designing relational schemas, writing queries that filter, sort, aggregate, and join data across multiple tables, and using SQL to investigate and answer open-ended, real-world questions.
- **Python as a second language** — appreciating how higher-level language features (built-in string methods, list comprehensions, f-strings, and libraries like `csv` and `re`) let me express the same underlying logic I'd first written in C far more concisely.
- **Web development fundamentals** — structuring content with HTML, styling it with CSS (including using the Bootstrap framework), and adding client-side interactivity with JavaScript and the DOM.
- **Full-stack web applications** — building server-side applications with Flask, managing user sessions and authentication, securely hashing passwords, safely querying a database from application code, and validating user input on both the client and server side.
- **Software engineering habits** — reading and extending existing (distribution) codebases, writing readable and well-styled code (checked with `style50`), testing systematically and adversarially, and documenting my process clearly, whether in code comments or in write-ups like this one.
- **Security-mindedness** — consistently applying practices like parameterized SQL queries to prevent injection attacks, and never trusting client-side validation alone.

More than any single language or tool, this course shaped how I approach unfamiliar problems: breaking them into smaller pieces, writing pseudocode before code, testing deliberately (including edge cases and adversarial input), and reading documentation and existing code carefully before writing my own.

## 🎓 Certificate

Upon completing the course, I was awarded the official CS50x certificate from Harvard University (HarvardX):

**[View my CS50x Certificate](https://certificates.cs50.io/5a0d47b5-d702-41c1-955d-087b0f25129c.pdf)**

## 🔗 Course Information

- Course homepage: [https://cs50.harvard.edu/x/](https://cs50.harvard.edu/x/)
- Instructor: David J. Malan
- Institution: Harvard University

---

*Each subfolder in this repository contains a dedicated README with a detailed breakdown of that specific problem, my implementation, and the concepts it reinforced.*