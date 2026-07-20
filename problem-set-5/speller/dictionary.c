// Implements a dictionary's functionality

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
