#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Function to check whether the key is valid
bool is_valid_key(string key);

// Helper function that substitutes a character using the key
char substitute(char c, string key);

int main(int argc, string argv[])
{
    // Check for exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    };

    string key = argv[1];

    // Validate the key
    if (!is_valid_key(key))
    {
        printf("Key must contain 26 unique alphabetical characters.\n");
        return 1;
    };

    // Prompt the user for plaintext
    string plaintext = get_string("plaintext:  ");

    // Print the ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", substitute(plaintext[i], key));
    };

    printf("\n");
    return 0;
};

// Function to check if the key is 26 unique alphabetical characters
bool is_valid_key(string key)
{
    if (strlen(key) != 26)
    {
        return false;
    };

    int letters[26] = {0};

    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        int index = toupper(key[i]) - 'A';

        // Check for duplicate characters
        if (letters[index] > 0)
        {
            return false;
        }
        letters[index]++;
    };

    return true;
};

// Function to substitute a character using the key, preserving case
char substitute(char c, string key)
{
    if (isupper(c))
    {
        return toupper(key[c - 'A']);
    }
    else if (islower(c))
    {
        return tolower(key[c - 'a']);
    }
    else
    {
        return c; // Non-alphabetical characters are unchanged
    };
};
