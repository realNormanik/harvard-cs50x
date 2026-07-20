# CS50 – Problem Set 3: Tideman

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to extend CS50-provided distribution code to implement a program that simulates an election using the **Tideman voting method** (also known as "ranked pairs"), a ranked-choice voting system guaranteed to produce the **Condorcet winner** of an election if one exists — that is, the candidate who would win every possible head-to-head matchup against every other candidate. The method works by tallying head-to-head preferences between every pair of candidates, sorting those pairs by strength of victory, and "locking" them into a directed graph one at a time, skipping any pair that would create a cycle. The winner is the candidate at the "source" of the resulting graph — the one with no edges pointing toward them.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading, understanding, and extending existing (distribution) code across several interconnected functions,
- working with **structs** in C to represent pairs of candidates (winner and loser indices),
- working with **two-dimensional arrays** to represent both voter preference tallies and a graph's adjacency matrix,
- implementing a **custom sorting algorithm** to order data by a computed criterion (strength of victory),
- detecting and avoiding **cycles in a directed graph** using recursion,
- reasoning about graph theory concepts (sources, edges, adjacency matrices) and applying them in an algorithmic context,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/3/tideman.zip
   ```
2. Extracted the downloaded archive to create a folder called `tideman`:
   ```bash
   unzip tideman.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm tideman.zip
   ```
4. Navigated into the `tideman` folder:
   ```bash
   cd tideman
   ```
5. Reviewed the existing code in `tideman.c` to understand the provided structure, including the two-dimensional `preferences` and `locked` arrays, the `pair` struct, the `pairs` array, and the overall control flow in `main` that collects votes, builds and sorts the pairs, locks them into the graph, and prints the winner.
6. Implemented the `vote` function, validating that a given candidate name matches a candidate on the ballot and, if so, recording that candidate's index at the appropriate rank in the voter's `ranks` array.
7. Implemented the `record_preferences` function, updating the global `preferences` array so that `preferences[i][j]` correctly reflects, for the current voter, that candidate `i` was ranked above candidate `j`.
8. Implemented the `add_pairs` function, comparing every pair of candidates and adding a `pair` to the `pairs` array whenever one candidate was clearly preferred over another (skipping ties), while updating the global `pair_count`.
9. Implemented the `sort_pairs` function, sorting the `pairs` array in decreasing order of strength of victory (the number of voters preferring the winning candidate in that pair).
10. Implemented the `lock_pairs` function, iterating over the sorted pairs and locking each one into the `locked` graph, using a helper recursive function to detect whether adding an edge would create a cycle before committing it.
11. Implemented the `print_winner` function, identifying and printing the name of the candidate who was the source of the graph (the candidate with no incoming edges in `locked`).
12. Compiled the program using the command:
    ```bash
    make tideman
    ```
13. Ran the compiled program with a list of candidates provided as command-line arguments, for example:
    ```bash
    ./tideman Alice Bob Charlie
    ```
14. Manually tested the program with various numbers of candidates and voters, invalid votes for candidates not on the ballot, and elections designed to include cycles (to confirm the cycle-avoidance logic worked correctly), comparing the output against known Condorcet winners for hand-worked examples.
15. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/tideman
    ```
16. Checked the code style using the `style50` tool:
    ```bash
    style50 tideman.c
    ```
17. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/tideman
    ```

## 💻 Program Code

The distribution code provided the overall program structure, including the `pair` struct, the `preferences` and `locked` arrays, and the Tideman control flow in `main`. My work focused on implementing the six functions left incomplete in the distribution code:

```c
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates allowed
#define MAX 9

// preferences[i][j] is the number of voters who prefer candidate i over candidate j
int preferences[MAX][MAX];

// locked[i][j] is true if candidate i is locked in over candidate j
bool locked[MAX][MAX];

// Each pair represents a pair of candidates with a winner and a loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array to store candidate names
string candidates[MAX];

// Array to store all winning pairs
pair pairs[MAX * (MAX - 1) / 2];

// Counts for number of pairs and candidates
int pair_count;
int candidate_count;

// Function declarations
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool creates_cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Ensure at least one candidate is provided
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    };

    candidate_count = argc - 1;

    // Check for candidate limit
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    };

    // Store candidate names
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    };

    // Initialize the locked graph to false (no edges yet)
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        };
    };

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        int ranks[candidate_count]; // ranks[i] is the index of the candidate ranked i-th

        // Collect each voter's rankings
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Validate vote
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            };
        };

        // Update global preferences based on current voter's ranks
        record_preferences(ranks);
        printf("\n");
    };

    // Process all votes
    add_pairs();    // Identify all winning pairs
    sort_pairs();   // Sort pairs in decreasing order of strength
    lock_pairs();   // Lock pairs into the graph without cycles
    print_winner(); // Determine and print the winner
    return 0;
};

// Update ranks array if name is a valid candidate
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        };
    };
    return false; // Invalid candidate name
};

// Update global preferences matrix given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        };
    };
};

// Identify all pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // If candidate i is preferred over candidate j
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            };
        };
    };
};

// Sort pairs in descending order by strength of victory
void sort_pairs(void)
{
    // Simple bubble sort based on margin of victory
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int strength1 = preferences[pairs[j].winner][pairs[j].loser];
            int strength2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser];
            if (strength1 < strength2)
            {
                // Swap pairs[j] and pairs[j+1]
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            };
        };
    };
};

// Recursive function to detect if locking in a pair creates a cycle
bool creates_cycle(int winner, int loser)
{
    if (loser == winner)
    {
        return true; // Cycle detected
    };

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (creates_cycle(winner, i))
            {
                return true; // Propagate cycle detection
            };
        };
    };

    return false; // No cycle found
};

// Lock pairs into the candidate graph in order, skipping those that would create cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!creates_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        };
    };
};

// Print the winner of the election (source of the graph)
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_source = true;

        // If any candidate has an edge pointing to i, i is not the source
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_source = false;
                break;
            };
        };

        // Source found; this candidate is the winner
        if (is_source)
        {
            printf("%s\n", candidates[i]);
            return;
        };
    };
};
```

## 📤 Expected Output

After compiling and running the program with a list of candidates, the program prompts for the number of voters and each voter's ranked preferences, then computes the pairwise results, locks them into a graph while avoiding cycles, and prints the name of the candidate at the source of the graph, for example:

```
$ ./tideman Alice Bob Charlie
Number of voters: 9
Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

...

Alice
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Modeling a Graph with an Adjacency Matrix** – I learned how to represent a directed graph of candidates using a two-dimensional boolean array (`locked`), where `locked[i][j]` indicates an edge from candidate `i` to candidate `j`, and how this representation makes checking for existing edges straightforward.
- **Tallying Pairwise Preferences** – I practiced updating a two-dimensional array (`preferences`) to accumulate head-to-head preference counts across many voters, based on each voter's full ranked ballot.
- **Custom Sorting by a Computed Criterion** – I implemented a sorting algorithm (insertion sort) to order pairs of candidates by strength of victory, reinforcing how sorting criteria can be derived from other data (`preferences`) rather than stored directly on the elements being sorted.
- **Cycle Detection via Recursion** – I gained hands-on experience writing a recursive function to detect whether adding a new edge to a directed graph would create a cycle, by recursively following existing edges from the target candidate to see if they eventually lead back to the source.
- **Applying Graph Theory Concepts** – I deepened my understanding of fundamental graph theory concepts, such as edges, sources, and cycles, and saw how these abstract concepts translate directly into a working voting algorithm.
- **Working with Structs to Represent Relationships** – I practiced using a `pair` struct to represent a relationship (a preference) between two candidates, rather than a single independent value, which was essential for sorting and locking operations.
- **Multi-Step Algorithm Design** – I learned how to break the Tideman method into its three conceptual phases (tally, sort, lock) and implement each phase as its own function, making a complex algorithm easier to reason about, test, and debug incrementally.
- **Testing Against Known Outcomes** – I practiced testing the program against hand-worked examples with known Condorcet winners, including scenarios specifically designed to create cycles, to confirm the cycle-avoidance logic behaved as expected.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 3: Tideman](https://cs50.harvard.edu/x/psets/3/tideman/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
