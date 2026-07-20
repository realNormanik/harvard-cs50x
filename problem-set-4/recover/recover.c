#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

// Define the JPEG signature
const uint8_t JPEG_SIGNATURE[] = {0xff, 0xd8, 0xff};

int main(int argc, char *argv[])
{
    // Check for correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    };

    // Open the forensic image
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    };

    // Buffer to store 512 bytes at a time
    uint8_t buffer[BLOCK_SIZE];

    // Counter for the number of JPEGs found
    int jpeg_count = 0;

    // File pointer for the output JPEGs
    FILE *outfile = NULL;

    // Read 512 bytes at a time from the input file
    while (fread(buffer, 1, BLOCK_SIZE, infile) == BLOCK_SIZE)
    {
        // Check if the first three bytes match the JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            // Check if the fourth byte matches the JPEG criteria
            if ((buffer[3] & 0xf0) == 0xe0)
            {
                // If we are already writing a JPEG, close the current file
                if (outfile != NULL)
                {
                    fclose(outfile);
                }

                // Create a new file for the new JPEG
                char filename[8];
                sprintf(filename, "%03d.jpg", jpeg_count);
                outfile = fopen(filename, "w");

                // If the file could not be opened, print an error and return 1
                if (outfile == NULL)
                {
                    printf("Could not create file.\n");
                    fclose(infile);
                    return 1;
                }

                // Increment the JPEG counter
                jpeg_count++;
            };
        };

        // If we have an open JPEG file, write the current block to it
        if (outfile != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, outfile);
        };
    };

    // Close the last file and the input file
    if (outfile != NULL)
    {
        fclose(outfile);
    };

    fclose(infile);

    return 0;
};
