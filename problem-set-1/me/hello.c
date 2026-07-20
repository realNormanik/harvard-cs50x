#include <cs50.h>  // standard I/O library
#include <stdio.h> // Library for input/output handling

// Main function of the program
int main(void)
{
    // Ask a user for their name
    string name = get_string("What is your name? ");
    // Greet a user by name
    printf("hello, %s\n", name);
};
