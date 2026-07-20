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
