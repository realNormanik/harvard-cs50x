# CS50X – Problem Set 5: Inheritance

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to extend CS50-provided distribution code to simulate the **inheritance of blood type alleles** across a family tree of a specified number of generations. Each person has two blood type alleles (`A`, `B`, or `O`). The oldest generation in the simulated family has alleles assigned randomly, while every younger generation inherits one randomly chosen allele from each of their two parents. The program then prints out the resulting family tree, showing each person's blood type alongside their generation, for example:

```
$ ./inheritance
Child (Generation 0): blood type OO
    Parent (Generation 1): blood type AO
        Grandparent (Generation 2): blood type OA
        Grandparent (Generation 2): blood type BO
    Parent (Generation 1): blood type OB
        Grandparent (Generation 2): blood type AO
        Grandparent (Generation 2): blood type BO
```

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading, understanding, and extending existing (distribution) code that defines a recursive data structure,
- working with **structs containing self-referential pointers**, used here to model a family tree where each `person` points to their two `parents`,
- **dynamic memory allocation** using `malloc` to build a tree-like structure at runtime, sized according to a variable number of generations,
- writing **recursive functions** to construct and later tear down a linked, tree-shaped structure,
- generating pseudo-random values to simulate allele inheritance,
- ensuring a program that uses `malloc` does not leak memory, by pairing every allocation with a corresponding `free`,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/5/inheritance.zip
   ```
2. Extracted the downloaded archive to create a folder called `inheritance`:
   ```bash
   unzip inheritance.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm inheritance.zip
   ```
4. Navigated into the `inheritance` folder:
   ```bash
   cd inheritance
   ```
5. Reviewed the existing code in `inheritance.c` to understand the provided structure, including the `person` struct (containing a `parents` array of two pointers and an `alleles` array of two characters), the `random_allele` helper function, and how `main` calls `create_family` and later `free_family`.
6. Implemented the `create_family` function recursively: for the base case (the oldest generation, when only one generation remains), a person is allocated with both parent pointers set to `NULL` and both alleles chosen via `random_allele`; for younger generations, a person is allocated whose two parents are themselves built by recursive calls to `create_family` with one fewer generation, and whose two alleles are each chosen at random from one of the corresponding parent's two alleles.
7. Implemented the `free_family` function recursively, freeing a person's two parents (if they exist) via recursive calls before freeing the person themselves, ensuring every block allocated by `create_family` was eventually released.
8. Compiled the program using the command:
   ```bash
   make inheritance
   ```
9. Ran the compiled program:
   ```bash
   ./inheritance
   ```
10. Manually verified across multiple runs that each child's two alleles matched one allele from each parent, and that each parent's two alleles in turn matched one allele from each grandparent, confirming the inheritance logic was correctly implemented at every generation.
11. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/inheritance
    ```
12. Checked the code style using the `style50` tool:
    ```bash
    style50 inheritance.c
    ```
13. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/inheritance
    ```

## 💻 Program Code

The distribution code provided the overall program structure, including the `person` struct definition, the `random_allele` helper function, and the logic in `main` for printing the resulting family tree. My work focused on implementing the two functions left incomplete in the distribution code:

```c
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

const int GENERATIONS = 3;

// Function prototypes
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele(void);

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
};

person *create_family(int generations)
{
    // Allocate memory for new person
    person *new_person = malloc(sizeof(person));
    if (new_person == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    };

    // If there are more generations
    if (generations > 1)
    {
        // Create two new parents
        new_person->parents[0] = create_family(generations - 1);
        new_person->parents[1] = create_family(generations - 1);

        // Randomly assign alleles based on parents
        new_person->alleles[0] = new_person->parents[0]->alleles[rand() % 2];
        new_person->alleles[1] = new_person->parents[1]->alleles[rand() % 2];
    }
    else
    {
        // No parents in this generation
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;

        // Randomly assign alleles
        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();
    };

    return new_person;
};

void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    };

    // Indentation for visualization
    for (int i = 0; i < generation * 4; i++)
    {
        printf(" ");
    };

    // Print generation and blood type
    printf("Generation %i: blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);

    // Recurse on parents
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
};

void free_family(person *p)
{
    if (p == NULL)
    {
        return;
    };

    // Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Free this person
    free(p);
};

char random_allele(void)
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    };
};
```

## 📤 Expected Output

After compiling and running the program, a family tree of the default number of generations is generated and printed, showing each person's blood type based on the alleles they inherited from their parents (or, for the oldest generation, alleles chosen at random), for example:

```
$ ./inheritance
Child (Generation 0): blood type OO
    Parent (Generation 1): blood type AO
        Grandparent (Generation 2): blood type OA
        Grandparent (Generation 2): blood type BO
    Parent (Generation 1): blood type OB
        Grandparent (Generation 2): blood type AO
        Grandparent (Generation 2): blood type BO
```

Since alleles are chosen randomly, running the program multiple times produces different, valid blood type combinations each time, while always respecting the rule that each person's alleles come from their parents (except in the oldest generation).

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Recursive Data Structures** – I gained hands-on experience working with a self-referential struct (`person`), where each instance points to two other instances of the same type, forming a tree-shaped structure that naturally lends itself to recursive processing.
- **Dynamic Memory Allocation for Tree Structures** – I practiced using `malloc` to allocate memory for each node of a tree at runtime, based on a variable number of generations determined by the caller, rather than relying on a fixed-size, statically declared structure.
- **Recursive Construction** – I learned how to design a recursive function (`create_family`) with a clear base case (the oldest generation, with no further parents to create) and a recursive case (younger generations, whose parents are themselves built via recursive calls), a pattern broadly applicable to tree and graph construction problems.
- **Recursive Deallocation** – I understood the importance of freeing a recursively built structure in the correct order — first freeing all descendants (in this case, ancestors, since the recursion travels toward older generations) before freeing the current node — to avoid losing access to memory that still needs to be released.
- **Avoiding Memory Leaks** – I reinforced the discipline of pairing every `malloc` call with an eventual `free` call, and verified this by tracing through the recursive calls to confirm that every allocated `person` was eventually freed by `free_family`.
- **Simulating Randomness with Constraints** – I practiced using `rand()` to simulate a real-world random process (allele inheritance) while still respecting the biological constraint that a child's allele must come from one of their parent's two alleles, rather than being entirely unconstrained.
- **Verifying Correctness Across Recursive Output** – I practiced testing a recursive program by tracing its printed output across multiple generations, confirming that the inheritance relationship held consistently not just between a child and their immediate parents, but between parents and grandparents as well.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 5: Inheritance](https://cs50.harvard.edu/x/psets/5/inheritance/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
