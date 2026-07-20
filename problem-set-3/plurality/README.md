# CS50X – Problem Set 3: Plurality

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to extend CS50-provided distribution code to implement a program that runs a **plurality election** (also known as "first-past-the-post" or "winner-take-all"), in which every voter votes for one candidate and the candidate with the most votes wins. Candidates are provided as command-line arguments, voters cast their votes by typing a candidate's name, and the program then determines and prints the winner — or, in the event of a tie, all tied winners.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading, understanding, and extending existing (distribution) code rather than writing a program entirely from scratch,
- working with **structs** in C to group related data together (a candidate's name and vote count),
- working with **global arrays and variables** shared across multiple functions,
- iterating over an array of structs to search for a match and update a field,
- designing an efficient algorithm to find a maximum value (and all elements matching it) without resorting to sorting,
- handling edge cases such as invalid votes and multi-way ties,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/3/plurality.zip
   ```
2. Extracted the downloaded archive to create a folder called `plurality`:
   ```bash
   unzip plurality.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm plurality.zip
   ```
4. Navigated into the `plurality` folder:
   ```bash
   cd plurality
   ```
5. Reviewed the existing code in `plurality.c` to understand the provided structure, including the `candidate` struct, the global `candidates` array, the `MAX` constant, and how command-line arguments were used to populate the list of candidates.
6. Implemented the `vote` function, iterating over the array of candidates to find a name match, incrementing that candidate's vote count and returning `true` if a match was found, or returning `false` if the given name did not match any candidate on the ballot.
7. Implemented the `print_winner` function using an efficient two-pass approach: first determining the maximum number of votes received by any candidate, then printing the name of every candidate whose vote count matched that maximum (handling both single-winner and tied-winner scenarios without using a sorting algorithm).
8. Compiled the program using the command:
   ```bash
   make plurality
   ```
9. Ran the compiled program with a list of candidates provided as command-line arguments, for example:
   ```bash
   ./plurality Alice Bob Charlie
   ```
10. Manually tested the program with various numbers of candidates (up to the maximum of 9), valid and invalid votes, and scenarios producing a single winner as well as scenarios producing multiple tied winners.
11. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/plurality
    ```
12. Checked the code style using the `style50` tool:
    ```bash
    style50 plurality.c
    ```
13. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/plurality
    ```

## 💻 Program Code

The distribution code provided the overall program structure, including the `candidate` struct, the global `candidates` array, and the logic for reading candidates and votes in `main`. My work focused on implementing the two functions left incomplete in the distribution code:

```c
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    };

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    };

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        };
    };

    // Display winner of election
    print_winner();
};

// Update vote totals given a new vote
bool vote(string name)
{
    // Iterate through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidate's name matches the given name
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Increment the candidate's vote count
            candidates[i].votes++;
            return true;
        };
    };
    return false; // No match found, return false
};

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max_votes = 0;

    // Find the maximum number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    };

    // Print all candidates with the maximum number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        };
    };
};
```

## 📤 Expected Output

After compiling and running the program with a list of candidates, the program prompts for the number of voters and each voter's chosen candidate, then prints the winner (or winners) of the election, for example:

```
$ ./plurality Alice Bob Charlie
Number of voters: 5
Vote: Alice
Vote: Bob
Vote: Alice
Vote: Charlie
Vote: Alice
Alice
```

In the event of a tie, all winning candidates are printed, each on their own line:

```
$ ./plurality Alice Bob
Number of voters: 2
Vote: Alice
Vote: Bob
Alice
Bob
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Reading and Extending Existing Code** – I practiced the skill of reading unfamiliar, pre-written code and understanding its structure, control flow, and data model before adding new functionality, a common real-world scenario when working on existing codebases.
- **Structs in C** – I learned how to work with a `struct` (`candidate`) that groups related fields (`name` and `votes`) together, and how to access and modify those fields for elements stored in an array of structs.
- **Global State Management** – I understood how global variables and arrays (`candidates`, `candidate_count`) can be shared and modified across multiple functions within a single program, and the responsibility that comes with mutating shared state correctly.
- **String Comparison** – I reinforced how to compare strings in C using `strcmp`, since strings cannot be compared directly with `==`, and applied this to match a voter's input against a list of candidate names.
- **Efficient Maximum-Finding Algorithm** – I learned how to find a maximum value (and all elements sharing that maximum) using two simple linear passes over an array, avoiding the unnecessary overhead of a full sort — reinforcing the importance of choosing an algorithm proportional to the actual problem at hand.
- **Handling Ties and Edge Cases** – I practiced designing logic that correctly handles multiple winners in the event of a tie, as well as gracefully rejecting invalid votes for candidates not on the ballot.
- **Function Contracts** – I deepened my understanding of function signatures and return values, particularly how a `bool` return value (`vote`) can communicate success or failure back to the caller, allowing `main` to react accordingly (e.g., reporting an invalid vote).
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 3: Plurality](https://cs50.harvard.edu/x/psets/3/plurality/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
