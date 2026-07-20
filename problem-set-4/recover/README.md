# CS50X – Problem Set 4: Recover

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to write a forensic data-recovery program in C that recovers deleted JPEG photos from a raw forensic image of a digital camera's memory card. JPEG files begin with a distinctive four-byte "signature" (`0xff 0xd8 0xff` followed by a byte whose upper four bits are `1110`), and digital cameras typically store photos contiguously in 512-byte blocks. The program scans through the memory card image block by block, detects the start of each new JPEG by its signature, and writes each recovered photo to its own numbered output file, for example:

```
$ ./recover card.raw
$ ls
000.jpg  001.jpg  002.jpg  ...  049.jpg
```

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading binary data from a file in fixed-size chunks using `fopen`, `fread`, and a buffer,
- recognizing a binary file signature (a specific sequence of bytes) to identify the boundaries between distinct files within a larger raw data stream,
- working with the `uint8_t` fixed-width type from `stdint.h` to represent raw bytes precisely,
- dynamically generating filenames using `sprintf`, including correctly sizing a buffer to hold a formatted string (accounting for the terminating NUL character),
- opening, writing to, and closing multiple output files in sequence within a single program run,
- validating command-line arguments and gracefully handling file-opening failures,
- practicing safe file handling to avoid resource and memory leaks,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/4/recover.zip
   ```
2. Extracted the downloaded archive to create a folder called `recover`:
   ```bash
   unzip recover.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm recover.zip
   ```
4. Navigated into the `recover` folder:
   ```bash
   cd recover
   ```
5. Reviewed the provided distribution files, confirming the presence of `recover.c` (to be completed) and `card.raw` (the forensic image to recover JPEGs from).
6. Started with pseudocode outlining the main steps of the program before writing actual code: accept a command-line argument, open the memory card, and read through it block by block, creating JPEG files along the way.
7. Implemented validation to ensure the program was run with exactly one command-line argument, printing a usage message and returning `1` otherwise.
8. Implemented file-opening logic for the forensic image, checking that `fopen` did not return `NULL` and informing the user if the file could not be opened.
9. Implemented a 512-byte buffer (using `uint8_t`) and a loop using `fread` to read the memory card block by block until no more data remained.
10. Implemented JPEG signature detection, checking the first four bytes of each block against the known JPEG header pattern (`0xff 0xd8 0xff` followed by a byte with `1110` as its upper nibble).
11. Implemented logic to open a new, sequentially numbered output file (`000.jpg`, `001.jpg`, and so on) using `sprintf` to build each filename, closing the previous output file (if one was open) whenever a new JPEG signature was found, and continuing to write subsequent blocks to whichever output file was currently open.
12. Compiled the program using the command:
    ```bash
    make recover
    ```
13. Ran the compiled program against the provided forensic image:
    ```bash
    ./recover card.raw
    ```
14. Verified the results by listing the generated files and opening several of them to confirm they were viewable, intact JPEG images, and by cleaning up test output between iterations using:
    ```bash
    rm -f *.jpg
    ```
15. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/recover
    ```
16. Checked the code style using the `style50` tool:
    ```bash
    style50 recover.c
    ```
17. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/recover
    ```

## 💻 Program Code

```c
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
```

## 📤 Expected Output

After compiling and running the program against the forensic image, the program produces no terminal output on success but generates 50 sequentially numbered JPEG files in the current working directory:

```
$ ./recover card.raw
$ ls
000.jpg  001.jpg  002.jpg  ...  049.jpg  card.raw  Makefile  recover  recover.c
```

Opening each generated file confirms it is a viewable, intact photograph recovered from the memory card image.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Binary File Signatures** – I learned how many file formats, including JPEG, begin with a distinctive sequence of bytes (a "magic number" or signature), and how this pattern can be used to programmatically detect the boundaries between concatenated files within a single larger binary stream.
- **Block-Based File Reading** – I practiced reading a large binary file in fixed-size chunks (512-byte blocks) using a buffer, rather than loading the entire file into memory at once, reinforcing an efficient and scalable approach to processing large files.
- **Bitwise Operations for Pattern Matching** – I used the bitwise AND operator (`&`) together with a mask (`0xf0`) to check only the relevant upper four bits of a byte, which was necessary to correctly detect the fourth byte of a JPEG signature, since it varies across a specific range of values.
- **Managing Multiple Output Files Sequentially** – I learned how to open, write to, and close a series of separate output files within a single pass over the input data, correctly closing each JPEG file only once the next one's signature was detected.
- **Dynamic Filename Generation** – I practiced using `sprintf` to build a formatted filename string (`###.jpg`) at runtime, and learned to size the destination buffer correctly to account for the three digits, the file extension, and the terminating NUL character.
- **Fixed-Width Integer Types** – I reinforced my understanding of the `uint8_t` type from `stdint.h` for representing raw, unsigned single-byte values, which was essential for accurately comparing buffer contents against the expected JPEG signature bytes.
- **Robust File Handling** – I practiced validating that files were opened successfully before use, and ensured every file opened with `fopen` was properly closed with `fclose`, including handling the edge cases of the very first and very last JPEG in the sequence.
- **Real-World Forensic Data Recovery** – I gained an appreciation for how "deleted" data often persists on storage media until overwritten, and how understanding a file format's structure can enable meaningful data recovery even without a file system's cooperation.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 4: Recover](https://cs50.harvard.edu/x/psets/4/recover/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
