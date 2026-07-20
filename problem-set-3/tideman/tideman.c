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
