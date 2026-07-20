#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Scrabble scoring for A-Z
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// A function that counts points for a word
int compute_score(string word);

int main(void)
{
    // Get words from players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Calculate the points
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Compare and write out the result
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    };
};

int compute_score(string word)
{
    int score = 0;

    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isalpha(word[i]))
        {
            // Replace letter with index 0-25 (regardless of size)
            int index = toupper(word[i]) - 'A';
            score += POINTS[index];
        };
    };

    return score;
};
