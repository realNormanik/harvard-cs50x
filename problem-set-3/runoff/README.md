# CS50X – Problem Set 3: Runoff

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to extend CS50-provided distribution code to implement a program that simulates an **instant runoff election**, a ranked-choice voting system. Unlike a plurality vote, voters rank candidates in order of preference. If a candidate receives a majority (more than 50%) of first-preference votes, they win immediately. Otherwise, the candidate (or candidates) with the fewest votes is eliminated, and every voter who ranked that candidate first has their vote transferred to their next non-eliminated preference. This process repeats until a candidate achieves a majority, or the election ends in a tie among all remaining candidates.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading, understanding, and extending existing (distribution) code across multiple interconnected functions,
- working with **structs** in C to group related candidate data (name, vote count, and elimination status),
- working with **two-dimensional arrays** to model each voter's full ranked list of preferences,
- iterating through nested data structures to tabulate results based on evolving state (eliminated candidates),
- designing a multi-step, iterative algorithm involving repeated rounds of counting, checking for a winner, and eliminating candidates,
- handling edge cases such as invalid votes, single winners, and full ties among all remaining candidates,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/3/runoff.zip
   ```
2. Extracted the downloaded archive to create a folder called `runoff`:
   ```bash
   unzip runoff.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm runoff.zip
   ```
4. Navigated into the `runoff` folder:
   ```bash
   cd runoff
   ```
5. Reviewed the existing code in `runoff.c` to understand the provided structure, including the `candidate` struct (with `name`, `votes`, and `eliminated` fields), the global `candidates` array, the two-dimensional `preferences` array, and the overall control flow in `main` that repeatedly tabulates votes, checks for a winner, and eliminates candidates until the election is decided.
6. Implemented the `vote` function, validating that a given candidate name matches a candidate on the ballot and, if so, recording that candidate's index at the appropriate rank in the given voter's row of the `preferences` array.
7. Implemented the `tabulate` function, iterating over every voter's ranked preferences to find and credit a vote to their highest-ranked candidate who had not yet been eliminated, breaking out of the inner loop once that candidate was found.
8. Implemented the `print_winner` function, checking whether any candidate's vote count exceeded half of the total voter count and, if so, printing that candidate's name and returning `true`.
9. Implemented the `find_min` function, looping through all non-eliminated candidates to determine the smallest current vote count among them.
10. Implemented the `is_tie` function, checking whether every non-eliminated candidate's vote count matched the given minimum, indicating a full tie.
11. Implemented the `eliminate` function, marking every non-eliminated candidate whose vote count matched the given minimum as eliminated.
12. Compiled the program using the command:
    ```bash
    make runoff
    ```
13. Ran the compiled program with a list of candidates provided as command-line arguments, for example:
    ```bash
    ./runoff Alice Bob Charlie
    ```
14. Manually tested the program with various numbers of candidates and voters, invalid votes for candidates not on the ballot, scenarios with a clear single winner, and scenarios ending in a full tie among the remaining candidates.
15. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/runoff
    ```
16. Checked the code style using the `style50` tool:
    ```bash
    style50 runoff.c
    ```
17. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/runoff
    ```

## 💻 Program Code

The distribution code provided the overall program structure, including the `candidate` struct, the `preferences` array, and the runoff control flow in `main`. My work focused on implementing the six functions left incomplete in the distribution code:

```c
#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(void)
{
    // Prompt for number of candidates
    candidate_count = get_int("Number of candidates: ");
    // Prompt for number of voters
    voter_count = get_int("Number of voters: ");

    // Get the names of the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = get_string("Candidate %i: ", i + 1);
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    };

    // Get the votes for each voter
    for (int i = 0; i < voter_count; i++)
    {
        // Prompt for each voter's preferences
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 1;
            };
        };
    };

    // Run the election
    while (true)
    {
        // Tabulate the votes for the current round
        tabulate();

        // Check if someone has won
        if (print_winner())
        {
            break;
        };

        // Find the minimum number of votes any candidate has
        int min = find_min();

        // Check if there is a tie
        if (is_tie(min))
        {
            printf("It's a tie!\n");
            break;
        };

        // Eliminate the candidate(s) with the fewest votes
        eliminate(min);
    };

    return 0;
};

// Record a voter's vote for a candidate
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        };
    };
    return false;
};

// Tabulate the votes for the current round
void tabulate(void)
{
    // Reset vote count for each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }

    // Count the votes based on the current preferences
    for (int i = 0; i < voter_count; i++)
    {
        // Find the first non-eliminated candidate for each voter
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_index = preferences[i][j];
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                break; // Stop once a vote is cast for the first non-eliminated candidate
            };
        };
    };
};

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int majority = voter_count / 2;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > majority)
        {
            printf("Winner: %s\n", candidates[i].name);
            return true;
        };
    };
    return false;
};

// Return the minimum vote count among remaining candidates
int find_min(void)
{
    int min = MAX_VOTERS; // Start with a high number
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        };
    };
    return min;
};

// Check if there is a tie among all remaining candidates
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        };
    };
    return true;
};

// Eliminate the candidate(s) with the fewest votes
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        };
    };
};
```

## 📤 Expected Output

After compiling and running the program with a list of candidates, the program prompts for the number of voters and each voter's ranked preferences, then simulates the runoff process and prints the winner once a majority is reached, for example:

```
$ ./runoff Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

Rank 1: Bob
Rank 2: Alice
Rank 3: Charlie

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Alice
Rank 3: Charlie

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob
Alice
```

If, after eliminating candidates, all remaining candidates end up with the same number of votes, the program declares a tie instead of eliminating anyone further.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Extending Multi-Function Distribution Code** – I practiced reading and understanding a larger, more complex codebase spread across several interdependent functions before implementing my own logic within it, reinforcing good habits for working on existing projects.
- **Two-Dimensional Arrays** – I learned how to model and work with a two-dimensional array (`preferences`) to represent each voter's complete ranked list of candidates, and how to index into it correctly using voter and rank indices.
- **Structs with Multiple Fields and Mutable State** – I deepened my understanding of structs by working with a `candidate` struct that tracked not just static data (`name`) but also mutable state (`votes` and `eliminated`) that changed across multiple rounds of the election.
- **Iterative, Multi-Round Algorithms** – I gained experience designing and implementing an algorithm that runs in repeated rounds (tabulate, check for a winner, find the minimum, check for a tie, eliminate) until a stopping condition is met, a pattern common in simulations and iterative optimization problems.
- **Early Loop Termination** – I practiced using `break` to stop counting a voter's ballot once their highest-ranked, non-eliminated candidate was found, avoiding unnecessary and incorrect vote counting further down their ranked list.
- **Threshold-Based Decision Making** – I learned how to calculate and check a majority threshold (`voter_count / 2`) to determine whether a candidate had definitively won the election.
- **Handling Ties and Multi-Candidate Elimination** – I practiced writing logic that correctly identifies and eliminates all candidates tied for last place simultaneously, and that recognizes when a tie exists among every remaining candidate, requiring the election to be declared undecided rather than eliminating everyone.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 3: Runoff](https://cs50.harvard.edu/x/psets/3/runoff/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
