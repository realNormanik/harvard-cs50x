# CS50X – Problem Set 4: Volume

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to extend CS50-provided distribution code to implement a program that modifies the volume of a WAV audio file. WAV files store audio as a 44-byte header followed by a sequence of 16-bit samples representing the audio signal over time. The program accepts an input file, an output file, and a scaling factor as command-line arguments, then produces a new WAV file with every sample scaled by that factor — for example, multiplying by `2.0` doubles the volume, while multiplying by `0.5` cuts it in half.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading from and writing to binary files in C using `fopen`, `fread`, `fwrite`, and `fclose`,
- understanding and working with fixed-width integer types from `stdint.h` (`uint8_t` and `int16_t`) to precisely represent bytes and audio samples,
- copying a fixed-size binary header from one file to another,
- processing a file's contents sample by sample using a buffer and a loop, relying on `fread`'s return value to detect the end of the file,
- performing arithmetic directly on binary sample data to alter an audio signal,
- practicing safe file handling to avoid resource leaks (always pairing `fopen` with `fclose`),
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/4/volume.zip
   ```
2. Extracted the downloaded archive to create a folder called `volume`:
   ```bash
   unzip volume.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm volume.zip
   ```
4. Navigated into the `volume` folder:
   ```bash
   cd volume
   ```
5. Reviewed the existing code in `volume.c` to understand the provided structure, including the command-line argument validation, the `fopen` calls for the input and output files, the `HEADER_SIZE` constant, and the conversion of the scaling factor from a string to a `float` using `atof`.
6. Implemented the header-copying logic, reading the 44-byte WAV header from the input file into a `uint8_t` array using `fread`, and writing it unchanged to the output file using `fwrite`.
7. Implemented the sample-processing logic, using an `int16_t` buffer to read one sample at a time from the input file, scaling it by the given `factor`, and writing the updated sample to the output file, repeating this process in a loop until `fread` indicated no more samples remained to be read.
8. Compiled the program using the command:
   ```bash
   make volume
   ```
9. Ran the compiled program with a sample WAV file, for example:
   ```bash
   ./volume input.wav output.wav 2.0
   ```
10. Manually verified the results by downloading and listening to the generated output files, confirming that a factor of `2.0` doubled the perceived volume and a factor of `0.5` halved it.
11. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/volume
    ```
12. Checked the code style using the `style50` tool:
    ```bash
    style50 volume.c
    ```
13. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/volume
    ```

## 💻 Program Code

The distribution code provided the overall program structure, including command-line argument handling, file opening/closing, and the `factor` conversion. My work focused on completing the two `TODO` sections left incomplete in the distribution code:

```c
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    };

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    };

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        fclose(input); // Zamknij wcześniej otwarty plik
        printf("Could not open output file.\n");
        return 1;
    };

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // Read samples from input file and write updated data to output file
    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, input))
    {
        sample *= factor;
        fwrite(&sample, sizeof(int16_t), 1, output);
    };

    // Close files
    fclose(input);
    fclose(output);
    return 0;
};
```

## 📤 Expected Output

After compiling and running the program with an input WAV file, an output filename, and a scaling factor, a new WAV file is generated with every sample scaled accordingly. No output is printed to the terminal on success:

```
$ ./volume input.wav output.wav 2.0
$ ./volume input.wav output.wav 0.5
```

Listening to `output.wav` in each case confirms the volume was doubled or halved, respectively, compared to the original `input.wav`.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Binary File I/O** – I learned how to read from and write to binary files in C using `fopen`, `fread`, `fwrite`, and `fclose`, rather than working with plain text, which required careful attention to exact byte counts and data types.
- **Fixed-Width Integer Types** – I gained a practical understanding of the fixed-width types declared in `stdint.h`, specifically `uint8_t` for representing raw header bytes and `int16_t` for representing signed 16-bit audio samples, and why precision in size and signedness matters when working with binary file formats.
- **Working with File Headers** – I learned how to treat a portion of a binary file (the 44-byte WAV header) as an opaque block of data to be copied verbatim, without needing to interpret its internal structure for this task.
- **Buffered, Sample-by-Sample Processing** – I practiced using a single-sample buffer inside a loop to process a potentially large file incrementally, rather than loading the entire file into memory at once — an approach that scales well to files of any size.
- **Using `fread`'s Return Value for Loop Control** – I understood how `fread` returns the number of items successfully read, and how this value can be used directly as a loop condition to detect the end of a file cleanly, without needing to know the file's length in advance.
- **In-Place Data Transformation** – I practiced modifying binary data directly (scaling each sample by a floating-point factor) before writing it back out, reinforcing how simple arithmetic operations can meaningfully alter real-world binary content like audio.
- **Resource Management** – I reinforced the importance of always pairing `fopen` with a corresponding `fclose`, and of checking the result of `fopen` for `NULL` to handle cases where a file cannot be opened, both important habits for avoiding resource leaks and crashes.
- **Testing with Real Audio Files** – I practiced validating program correctness not just through automated checks but by actually listening to the generated output, reinforcing the value of end-to-end, real-world verification.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 4: Volume](https://cs50.harvard.edu/x/psets/4/volume/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
