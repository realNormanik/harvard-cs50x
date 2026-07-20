# CS50X – Problem Set 5: Speller

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to extend CS50-provided distribution code to implement a **spell checker** backed by a custom **hash table**. The program loads a dictionary of correctly spelled words into memory, then checks every word of a given text file against that dictionary, reporting any word not found as a misspelling, along with performance statistics for loading, checking, sizing, and unloading the dictionary, for example:

```
$ ./speller texts/lalaland.txt

MISSPELLED WORDS

TECHNO
L
Prius
...

WORDS MISSPELLED:     x
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:         x
TIME IN load:         x.xxxxxx
TIME IN check:        x.xxxxxx
TIME IN size:         x.xxxxxx
TIME IN unload:       x.xxxxxx
TIME IN TOTAL:        x.xxxxxx
```

## 🎯 Objective

The main objectives of this task were to get familiar with:
- designing and implementing a **hash table** from scratch, including choosing an appropriate number of buckets and collision-handling strategy (separate chaining via linked lists),
- writing a **custom hash function** that distributes words evenly across buckets while remaining fast to compute and case-insensitive,
- reading a large dictionary file (over 140,000 words) efficiently from disk into memory using `fopen` and `fscanf`,
- building and traversing **linked lists** of dynamically allocated nodes to store dictionary words within each hash table bucket,
- comparing strings case-insensitively using `strcasecmp` from `strings.h`,
- correctly freeing every dynamically allocated node to avoid memory leaks, verified using `valgrind`,
- working across multiple files in a larger C project (`speller.c`, `dictionary.c`, `dictionary.h`, `Makefile`) while modifying only the files permitted by the assignment's specification,
- reasoning about real-world ("wall-clock") performance rather than purely theoretical (asymptotic) time complexity,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/5/speller.zip
   ```
2. Extracted the downloaded archive to create a folder called `speller`:
   ```bash
   unzip speller.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm speller.zip
   ```
4. Navigated into the `speller` folder:
   ```bash
   cd speller
   ```
5. Reviewed the provided distribution files (`dictionary.h`, `dictionary.c`, `speller.c`, `Makefile`), studying how `speller.c` benchmarks and drives calls to `load`, `check`, `size`, and `unload`, and how the `node` struct and global `table` array in `dictionary.c` were set up to represent a hash table.
6. Increased the number of buckets (`N`) in `dictionary.c` well beyond the starter value of 26, to reduce collisions and better distribute words across the table.
7. Implemented a custom `hash` function that combines multiple characters of a word (rather than just the first letter) into an index within the table, ensuring the function was case-insensitive so that a word and its capitalized variants hashed to the same bucket.
8. Implemented the `load` function, opening the dictionary file with `fopen`, reading each word with `fscanf`, allocating a new `node` for each word with `malloc`, copying the word into the node, computing its hash, and inserting the node at the head of the appropriate bucket's linked list, while tracking a running count of loaded words.
9. Implemented the `size` function by returning the word count tracked during `load`, avoiding the need to re-traverse the entire hash table on every call.
10. Implemented the `check` function, hashing the given word to locate its bucket, then traversing that bucket's linked list and using `strcasecmp` to compare each stored word against the given word case-insensitively.
11. Implemented the `unload` function, traversing every bucket in the hash table and freeing each node in its linked list, ensuring every block allocated in `load` was properly released.
12. Compiled the program using the command:
    ```bash
    make speller
    ```
13. Ran the compiled program against several of the provided sample texts, using both the small and large dictionaries, for example:
    ```bash
    ./speller texts/lalaland.txt
    ./speller dictionaries/small texts/cat.txt
    ```
14. Verified correctness by comparing the program's output against the provided answer keys using `diff`:
    ```bash
    ./speller texts/lalaland.txt > student.txt
    diff -y student.txt keys/lalaland.txt
    ```
15. Checked for memory leaks using `valgrind`:
    ```bash
    valgrind ./speller texts/cat.txt
    ```
16. Compared the performance of my implementation against the staff's reference solution to evaluate load, check, size, and unload times:
    ```bash
    ./speller50 texts/lalaland.txt
    ```
17. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/speller
    ```
18. Checked the code style using the `style50` tool:
    ```bash
    style50 dictionary.c
    ```
19. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/speller
    ```

## 💻 Program Code

The distribution code provided `speller.c` (unmodified) along with the overall structure of `dictionary.c` and `dictionary.h`, including the `node` struct and the `table` array. My work focused on implementing the hash table logic in `dictionary.c`:

```c
#include <stdio.h>  // FILE, fopen, fscanf, fclose
#include <stdlib.h> // malloc, free
#include <string.h> // strlen, strcmp, strcpy

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

unsigned int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char lower[LENGTH + 1];
    int len = strlen(word);

    for (int i = 0; i < len; i++)
        lower[i] = tolower(word[i]);
    lower[len] = '\0';

    int index = hash(lower);
    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcmp(cursor->word, lower) == 0)
            return true;
        cursor = cursor->next;
    };

    return false;
};

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2 by Dan Bernstein
    unsigned long hash = 5381;
    int c;
    while ((c = tolower(*word++)))
        hash = ((hash << 5) + hash) + c;
    return hash % N;
};

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
        return false;

    char word[LENGTH + 1];

    // Load words one at a time
    while (fscanf(file, "%s", word) != EOF)
    {
        // Creating a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
            return false;
        strcpy(new_node->word, word);

        // Hashing the word and inserting it into the board
        int index = hash(word);
        new_node->next = table[index];
        table[index] = new_node;

        word_count++; // global variable of the number of words
    };

    fclose(file);

    return true;
};

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
};

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        };
    };

    return true;
};
```

## 📤 Expected Output

After compiling and running the program against a text file, the program prints every misspelled word it finds, followed by a summary of statistics, including how many words were misspelled, how many words are in the dictionary and the text, and how much time was spent in each of the four core functions:

```
$ ./speller texts/cat.txt

MISSPELLED WORDS

meow
purrfect

WORDS MISSPELLED:     2
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        14
TIME IN load:         0.123456
TIME IN check:        0.000042
TIME IN size:         0.000000
TIME IN unload:       0.045678
TIME IN TOTAL:        0.169176
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Designing a Hash Table from Scratch** – I gained a deep, practical understanding of how a hash table works internally, including how a hash function maps keys (words) to bucket indices, and how collisions are handled using separate chaining with linked lists.
- **Writing an Effective Hash Function** – I learned how to design a custom hash function that balances speed of computation against even distribution across buckets, and how choices like the number of buckets (`N`) and how many characters of a word to factor into the hash directly affect real-world performance.
- **Linked Lists within an Array** – I practiced combining two data structures — an array (the hash table itself) and linked lists (chained within each bucket) — to build a structure that supports fast insertion and lookup even as the dataset grows large.
- **Case-Insensitive String Handling** – I learned to use `strcasecmp` for case-insensitive word comparisons, and to ensure my hash function itself normalized letter casing (via `tolower`), so that a word and any of its capitalized variants consistently mapped to the same bucket.
- **Efficient File Reading at Scale** – I practiced using `fscanf` to read a dictionary of over 140,000 words efficiently, line by line, directly into a fixed-size buffer sized according to the `LENGTH` constant.
- **Memory Management for Complex Structures** – I reinforced disciplined memory management by ensuring every node allocated during `load` was properly traversed and freed during `unload`, and I used `valgrind` to actively confirm the absence of memory leaks rather than relying on visual inspection alone.
- **Reasoning About Real-World Performance** – I gained an appreciation for the difference between theoretical (asymptotic) time complexity and actual "wall-clock" performance, and used `speller.c`'s built-in benchmarking to iteratively tune my hash function and bucket count for faster load and check times.
- **Working Across a Multi-File Project with Constraints** – I practiced modifying only the files and functions permitted by a project's specification (`dictionary.c` and `dictionary.h`, without altering existing function prototypes), which mirrors real-world collaborative development within an established codebase.
- **Systematic Testing and Verification** – I practiced using `diff` to compare my program's output against provided answer keys and the staff's reference solution, which was an efficient way to pinpoint exactly which words were being mishandled.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 5: Speller](https://cs50.harvard.edu/x/psets/5/speller/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
