# CS50X – Problem Set 4: Filter (More)

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. It builds on the earlier "Filter (Less)" problem by extending CS50-provided distribution code to implement four **image filters** for 24-bit BMP files: grayscale, reflection, box blur, and **edge detection** using the Sobel operator. Each pixel in a BMP image is represented by an `RGBTRIPLE` struct storing its red, green, and blue color values, and the program manipulates a two-dimensional array of these pixel values to apply the chosen visual effect, saving the result as a new BMP file, for example:

```
$ ./filter -e images/yard.bmp out.bmp
```

## 🎯 Objective

The main objectives of this task were to get familiar with:
- reading, understanding, and extending existing (distribution) code spread across multiple files (`filter.c`, `helpers.c`, `helpers.h`, `bmp.h`),
- working with **structs** (`RGBTRIPLE`) to represent grouped pixel color data,
- working with **two-dimensional arrays** to represent and iterate over an image's grid of pixels,
- using **nested loops** to visit every pixel in an image, as well as the smaller 3x3 neighborhood surrounding each pixel,
- performing floating-point calculations and correctly rounding and capping resulting values within a valid byte range (0–255),
- copying a two-dimensional array to avoid using already-modified data when computing new values (as needed for blurring and edge detection),
- applying **convolution-style kernels** (the Sobel operator) to compute weighted sums over a pixel neighborhood, a foundational technique in image processing and computer vision,
- carefully handling edge and corner cases, including treating out-of-bounds neighboring pixels as solid black,
- the tools provided by CS50 for verifying the correctness (`check50`) and style (`style50`) of the written code, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/4/filter-more.zip
   ```
2. Extracted the downloaded archive to create a folder called `filter-more`:
   ```bash
   unzip filter-more.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm filter-more.zip
   ```
4. Navigated into the `filter-more` folder:
   ```bash
   cd filter-more
   ```
5. Reviewed the provided distribution files (`bmp.h`, `filter.c`, `helpers.h`, `helpers.c`, `Makefile`) to understand how a BMP file's headers and pixel data are read into a two-dimensional `image` array, and how `filter.c` dispatches to the appropriate filter function (`blur`, `edges`, `grayscale`, or `reflect`) based on a command-line flag.
6. Implemented the `grayscale` function, iterating over every pixel and setting its red, green, and blue values to the rounded average of the pixel's original red, green, and blue values.
7. Implemented the `reflect` function, iterating over each row and swapping pixels symmetrically from opposite ends of the row toward the center, using a temporary variable to perform each swap.
8. Implemented the `blur` function, first creating a full copy of the original image, then setting each pixel's new color values to the rounded average of all valid neighboring pixels (up to a 3x3 box) read from the copy, carefully bounding the neighbor indices for pixels along edges and corners.
9. Implemented the `edges` function, applying the horizontal (Gx) and vertical (Gy) Sobel kernels to the 3x3 neighborhood surrounding each pixel (read from a copy of the original image), treating any out-of-bounds neighbor as a solid black pixel, then combining Gx and Gy for each color channel using √(Gx² + Gy²), rounding the result and capping it at 255.
10. Compiled the program using the command:
    ```bash
    make filter
    ```
11. Ran the compiled program against the sample BMP images provided in the `images/` folder, testing each filter individually, for example:
    ```bash
    ./filter -g images/yard.bmp out.bmp
    ./filter -r images/yard.bmp out.bmp
    ./filter -b images/yard.bmp out.bmp
    ./filter -e images/yard.bmp out.bmp
    ```
12. Visually inspected the resulting output images to confirm each filter produced the expected effect, paying particular attention to the edge-detected image to verify that object boundaries were clearly highlighted.
13. Checked the correctness of the program using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/filter/more
    ```
14. Checked the code style using the `style50` tool:
    ```bash
    style50 helpers.c
    ```
15. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/filter/more
    ```

## 💻 Program Code

The distribution code provided the overall program structure, including BMP file reading/writing (`filter.c`), the header and `RGBTRIPLE` struct definitions (`bmp.h`), and the function prototypes (`helpers.h`). My work focused on implementing the four filter functions in `helpers.c`:

```c
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of the red, green, and blue values
            int avg = round((image[i][j].rgbtRed +
                             image[i][j].rgbtGreen +
                             image[i][j].rgbtBlue) / 3.0);

            // Set each color component to the average value
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        };
    };
};

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each row
    for (int i = 0; i < height; i++)
    {
        // Swap pixels horizontally using a temporary variable
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        };
    };
};

// Blur image using box blur
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the original image to avoid modifying it mid-processing
    RGBTRIPLE copy[height][width];

    // Copy original pixels into the copy array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        };
    };

    // Iterate over each pixel to compute the blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            // Iterate over the 3x3 box around the current pixel
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if neighboring pixel is within image bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumRed += copy[ni][nj].rgbtRed;
                        sumGreen += copy[ni][nj].rgbtGreen;
                        sumBlue += copy[ni][nj].rgbtBlue;
                        count++;
                    };
                };
            };

            // Calculate average color values and assign to original image
            image[i][j].rgbtRed = round(sumRed / (float) count);
            image[i][j].rgbtGreen = round(sumGreen / (float) count);
            image[i][j].rgbtBlue = round(sumBlue / (float) count);
        };
    };
};

// Detect edges using the Sobel operator
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy original image to avoid modifying it during calculations
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        };
    };

    // Define Sobel kernels for x and y direction
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    // Loop through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize gradient components for each color
            int redX = 0, redY = 0;
            int greenX = 0, greenY = 0;
            int blueX = 0, blueY = 0;

            // Loop over 3x3 grid surrounding the pixel
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if neighbor is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        RGBTRIPLE pixel = copy[ni][nj];

                        // Apply Sobel kernels
                        int gx = Gx[di + 1][dj + 1];
                        int gy = Gy[di + 1][dj + 1];

                        redX += pixel.rgbtRed * gx;
                        redY += pixel.rgbtRed * gy;

                        greenX += pixel.rgbtGreen * gx;
                        greenY += pixel.rgbtGreen * gy;

                        blueX += pixel.rgbtBlue * gx;
                        blueY += pixel.rgbtBlue * gy;
                    };
                };
            };

            // Calculate final color magnitude using the gradient formula
            int red = round(sqrt(redX * redX + redY * redY));
            int green = round(sqrt(greenX * greenX + greenY * greenY));
            int blue = round(sqrt(blueX * blueX + blueY * blueY));

            // Clamp values to max 255
            image[i][j].rgbtRed = red > 255 ? 255 : red;
            image[i][j].rgbtGreen = green > 255 ? 255 : green;
            image[i][j].rgbtBlue = blue > 255 ? 255 : blue;
        };
    };
};
```

## 📤 Expected Output

After compiling the program, each filter can be applied to a BMP image via a command-line flag, generating a new, filtered image file:

```
$ ./filter -g images/yard.bmp grayscale.bmp
$ ./filter -r images/yard.bmp reflected.bmp
$ ./filter -b images/yard.bmp blurred.bmp
$ ./filter -e images/yard.bmp edges.bmp
```

Opening each resulting file confirms the applied effect: `grayscale.bmp` appears in black-and-white, `reflected.bmp` is mirrored horizontally, `blurred.bmp` appears softened, and `edges.bmp` highlights the boundaries between distinct objects in the original image.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Representing Images as Data** – I deepened my understanding of how a 24-bit BMP image is structured on disk, and how it can be represented in memory as a two-dimensional array of `RGBTRIPLE` structs, each holding a pixel's red, green, and blue values.
- **Convolution Kernels and the Sobel Operator** – I gained hands-on experience implementing a real, widely used computer vision technique: applying fixed 3x3 kernels (Gx and Gy) to a pixel's neighborhood to detect changes in color intensity, and combining the two resulting values with `sqrt(Gx² + Gy²)` to measure the overall strength of an edge at that pixel.
- **Working with Multiple Weighted Neighborhood Sums Simultaneously** – I practiced computing several running sums (Gx and Gy for each of red, green, and blue) within a single nested loop pass, reinforcing careful bookkeeping when a single loop needs to update multiple accumulators at once.
- **Treating Out-of-Bounds Pixels as a Boundary Condition** – I learned how to handle edge and corner pixels in a convolution-based filter by treating any neighbor outside the image bounds as solid black (value 0), effectively excluding it from the weighted sum without needing special-case logic for each edge or corner.
- **Working with a Copy to Avoid Data Corruption** – I reinforced why both `blur` and `edges` required creating a full copy of the original image before modifying it, since each pixel's new value depends on its original (unmodified) neighbors, and altering `image` in place would corrupt those neighboring values for subsequent calculations.
- **Rounding and Capping Computed Values** – I practiced consistently rounding floating-point results to the nearest integer and capping them at 255, ensuring that even large computed edge-intensity values remained valid 8-bit color values.
- **Reusing Patterns Across Related Filters** – I noticed how the general structure used for `blur` (copy the image, iterate over each pixel, iterate over its 3x3 neighborhood, aggregate values) could be adapted and extended to implement the more complex `edges` filter, reinforcing the value of recognizing and reusing established patterns.
- **Visual, End-to-End Testing** – I practiced validating my implementation not just through automated tests but by visually inspecting the resulting images, which was especially useful for confirming that the edge-detection filter correctly highlighted object boundaries.
- **Testing and Code Verification** – I practiced using CS50's tools (`check50` and `style50`) to automatically verify the correctness and style of my code.
- **Submitting Work** – I learned how to properly submit a completed assignment using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 4: Filter (More)](https://cs50.harvard.edu/x/psets/4/filter/more/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
