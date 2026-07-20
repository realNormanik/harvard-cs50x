# CS50X – Problem Set 4: Filter (Less)

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to extend CS50-provided distribution code to implement several **image filters** for 24-bit BMP files: grayscale, sepia, reflection, and box blur. Each pixel in a BMP image is represented by an `RGBTRIPLE` struct storing its red, green, and blue color values, and the program manipulates a two-dimensional array of these pixel values to apply the chosen visual effect, saving the result as a new BMP file, for example:

```
$ ./filter -g images/yard.bmp out.bmp
```

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading, understanding, and extending existing (distribution) code spread across multiple files (`filter.c`, `helpers.c`, `helpers.h`, `bmp.h`),
- working with **structs** (`RGBTRIPLE`) to represent grouped pixel color data,
- working with **two-dimensional arrays** to represent and iterate over an image's grid of pixels,
- using **nested loops** to visit every pixel in an image, row by row and column by column,
- performing floating-point calculations and correctly rounding and capping resulting values within a valid byte range (0–255),
- copying a two-dimensional array to avoid using already-modified data when computing new values (as needed for blurring),
- carefully handling edge and corner cases when averaging values from neighboring pixels,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/4/filter-less.zip
   ```
2. Extracted the downloaded archive to create a folder called `filter-less`:
   ```bash
   unzip filter-less.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm filter-less.zip
   ```
4. Navigated into the `filter-less` folder:
   ```bash
   cd filter-less
   ```
5. Reviewed the provided distribution files (`bmp.h`, `filter.c`, `helpers.h`, `helpers.c`, `Makefile`) to understand how a BMP file's headers and pixel data are read into a two-dimensional `image` array, and how `filter.c` dispatches to the appropriate filter function (`blur`, `grayscale`, `reflect`, or `sepia`) based on a command-line flag.
6. Implemented the `grayscale` function, iterating over every pixel and setting its red, green, and blue values to the rounded average of the pixel's original red, green, and blue values.
7. Implemented the `sepia` function, iterating over every pixel and computing new red, green, and blue values using the standard sepia-tone formula, rounding each result to the nearest integer and capping any value above 255.
8. Implemented the `reflect` function, iterating over each row and swapping pixels symmetrically from opposite ends of the row toward the center, using a temporary variable to perform each swap.
9. Implemented the `blur` function, first creating a full copy of the original image, then iterating over every pixel in the original `image` array and setting each pixel's new color values to the rounded average of all valid neighboring pixels (up to a 3x3 box) read from the `copy` array, carefully bounding the neighbor indices for pixels along edges and corners.
10. Compiled the program using the command:
    ```bash
    make filter
    ```
11. Ran the compiled program against the sample BMP images provided in the `images/` folder, testing each filter individually, for example:
    ```bash
    ./filter -g images/yard.bmp out.bmp
    ./filter -s images/yard.bmp out.bmp
    ./filter -r images/yard.bmp out.bmp
    ./filter -b images/yard.bmp out.bmp
    ```
12. Visually inspected the resulting output images to confirm each filter produced the expected effect (grayscale, sepia tone, horizontal reflection, and blur).
13. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/filter/less
    ```
14. Checked the code style using the `style50` tool:
    ```bash
    style50 helpers.c
    ```
15. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/filter/less
    ```

## 💻 Program Code

The distribution code provided the overall program structure, including BMP file reading/writing (`filter.c`), the header and `RGBTRIPLE` struct definitions (`bmp.h`), and the function prototypes (`helpers.h`). My work focused on implementing the four filter functions in `helpers.c`:

```c
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of the RGB values to get the grayscale intensity
            int avg =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Assign the average value to all three color channels
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        };
    };
};

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Store original color values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Apply sepia formula to compute new color values
            int sepiaRed =
                round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen =
                round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue =
                round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            // Clamp each value to a maximum of 255
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        };
    };
};

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row of the image
    for (int i = 0; i < height; i++)
    {
        // Only iterate halfway across the row to swap pixels symmetrically
        for (int j = 0; j < width / 2; j++)
        {
            // Swap the pixel with its horizontally opposite pixel
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        };
    };
};

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary copy of the original image
    RGBTRIPLE copy[height][width];

    // Copy each pixel from the original image to the copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        };
    };

    // Iterate over each pixel to apply the blur effect
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redTotal = 0;
            int greenTotal = 0;
            int blueTotal = 0;
            int count = 0;

            // Check the pixel itself and its 8 neighboring pixels
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di; // Row offset
                    int nj = j + dj; // Column offset

                    // Check if the neighboring pixel is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // Accumulate the RGB values
                        redTotal += copy[ni][nj].rgbtRed;
                        greenTotal += copy[ni][nj].rgbtGreen;
                        blueTotal += copy[ni][nj].rgbtBlue;
                        count++;
                    };
                };
            };

            // Calculate the average of the surrounding pixels and assign to the image
            image[i][j].rgbtRed = round((float) redTotal / count);
            image[i][j].rgbtGreen = round((float) greenTotal / count);
            image[i][j].rgbtBlue = round((float) blueTotal / count);
        };
    };
};
```

## 📤 Expected Output

After compiling the program, each filter can be applied to a BMP image via a command-line flag, generating a new, filtered image file:

```
$ ./filter -g images/yard.bmp grayscale.bmp
$ ./filter -s images/yard.bmp sepia.bmp
$ ./filter -r images/yard.bmp reflected.bmp
$ ./filter -b images/yard.bmp blurred.bmp
```

Opening each resulting file confirms the applied effect: `grayscale.bmp` appears in black-and-white, `sepia.bmp` takes on a reddish-brown, old-timey tone, `reflected.bmp` is mirrored horizontally, and `blurred.bmp` appears softened.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Representing Images as Data** – I gained a concrete understanding of how a 24-bit BMP image is structured on disk, and how it can be represented in memory as a two-dimensional array of `RGBTRIPLE` structs, each holding a pixel's red, green, and blue values.
- **Nested Loops for Grid Traversal** – I strengthened my ability to use nested `for` loops to visit every pixel in a two-dimensional grid, a pattern that recurred across all four filters with different logic applied at each pixel.
- **Applying Mathematical Formulas to Pixel Data** – I practiced translating real formulas (grayscale averaging and the sepia-tone weighted sums) directly into code, while correctly rounding floating-point results to integers and capping values at the maximum allowed byte value (255).
- **In-Place Array Manipulation and Swapping** – I reinforced the classic three-step technique of swapping two values using a temporary variable, applied here to reflect an image by swapping pixels symmetrically across each row.
- **Working with a Copy to Avoid Data Corruption** – I understood why the `blur` filter required creating a full copy of the original image before modifying it, since each pixel's blurred value depends on its original (unblurred) neighbors, and modifying `image` in place would corrupt those neighboring values for subsequent calculations.
- **Boundary and Edge-Case Handling** – I practiced writing careful bounds-checking logic (`ni >= 0 && ni < height && nj >= 0 && nj < width`) to correctly handle pixels along the edges and corners of the image, which have fewer neighbors than pixels in the interior.
- **Multi-File Project Structure** – I gained experience navigating and modifying only one file (`helpers.c`) within a larger, multi-file C project, relying on shared struct and function declarations in separate header files (`bmp.h`, `helpers.h`).
- **Visual, End-to-End Testing** – I practiced validating my implementation not just through automated tests but by visually inspecting the resulting images, reinforcing the value of end-to-end verification for tasks with a visible, tangible output.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 4: Filter (Less)](https://cs50.harvard.edu/x/psets/4/filter/less/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
