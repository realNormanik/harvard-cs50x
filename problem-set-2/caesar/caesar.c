#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);   // Checks whether the string contains only digits
char rotate(char c, int key); // Returns the encrypted character using the key

int main(int argc, string argv[])
{
    // Check if the user has given exactly one argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    };

    // Check if the argument contains only digits
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    };

    // Replace the argument with an integer
    int key = atoi(argv[1]);

    // Ask the user for the text to encrypt
    string plaintext = get_string("plaintext:  ");

    // Write out the ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Encrypt each character and write it out
        printf("%c", rotate(plaintext[i], key));
    }
    // Add a new line after the ciphertext
    printf("\n");
    return 0;
};

// Checks if the string contains only digits
bool only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        // If any character is not a digit, return false
        if (!isdigit(s[i]))
        {
            return false;
        }
    };
    // If all characters are digits, return true
    return true;
};

// Encrypts the c character using the key key
char rotate(char c, int key)
{
    // If the character is an uppercase letter
    if (isupper(c))
    {
        return (c - 'A' + key) % 26 + 'A';
    }
    // If the character is a lowercase letter
    else if (islower(c))
    {
        return (c - 'a' + key) % 26 + 'a';
    }
    else
    // If it's not a letter, don't change
    {
        return c;
    };
};
