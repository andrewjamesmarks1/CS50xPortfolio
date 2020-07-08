#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // Declare integer for each colour channel
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            // Take an average of the three integers for each pixel
            int average = round(((float) red + (float) blue + (float) green) / 3);
            // Asign the average to each colour channel
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int l = width - 1;
        int m = (width / 2);
        for (int j = 0; j < m; j++)
        {
            // Create temporary RGBTRIPLE and SWAP horizontally.
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][l - j];
            image [i][l - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image0[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Declare integers for each colour channel at 0 for each pixel as the function loops over all pixels
            int red = 0;
            int blue = 0;
            int green = 0;
            // Declare float to count number of pixels considered to allow average to be taken at 76 - 78
            float counter = 0.00;
            // Integer h represents horizontal movement across the image.
            for (int h = -1; h < 2; h++)
            {
                // If j + h is less than zero, j must be 0 and therefore there is no possibility of movement further left (and vice versa). Determines left and right edges.
                if (j + h < 0 || j + h > width - 1)
                {
                    // If at an edge in the j dimension, does not continue with function thus preventing movement outside of the size of the [i][j] image array.
                    continue;
                }
                // As per h, but for vertical movement.
                for (int v = -1; v < 2; v++)
                {
                    if (i + v < 0 || i + v > height - 1)
                    {
                        // If at an edge in the i dimension, does not continue with function.
                        // If an edge is reached in both the i and the j dimensions, it is a corner.
                        continue;
                    }
                    // Adds invidual colour channel integers for each individual adjacent pixel, and with the integers declared in the loop, is added to as per the number of pixels surrounding the pixel being filtered.
                    // A corner will only see the loop run a total of 4 times.
                    // A middle pixel will see the loop run a total of 9 times.
                    red += image[i + v][j + h].rgbtRed;
                    blue += image[i + v][j + h].rgbtBlue;
                    green += image[i + v][j + h].rgbtGreen;
                    // Counter is increased to calculate the number of pixels adjacent.
                    counter++;
                }
            }
            // Assigns the averaged colour channel integers to a COPY of the image, so that the entire loop over i and j for original pixels is not impacted by the pixels already filtered.
            image0[i][j].rgbtRed = round(red / counter);
            image0[i][j].rgbtBlue = round(blue / counter);
            image0[i][j].rgbtGreen = round(green / counter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Once all filtered pixels are generated, copies the temporary image back to the original for output.
            image[i][j].rgbtRed = image0[i][j].rgbtRed;
            image[i][j].rgbtBlue = image0[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image0[i][j].rgbtGreen;
        }
    }
    return;
}

// Detect edges
// Uses fundamentally the same structure as above, with modifications to perform the correct calculations for the Sobel
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image0[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Floats used throughout to maintain accuracy through the calculation until the last stage.
            // Calculates redX, blueX and greenX per the Gx matrix.
            // Calculates redY, blueY and greenY per the Gy matrix.
            float redX = 0.00;
            float blueX = 0.00;
            float greenX = 0.00;
            float redY = 0.00;
            float blueY = 0.00;
            float greenY = 0.00;
            for (int h = -1; h < 2; h++)
            {
                if (j + h < 0 || j + h > width - 1)
                {
                    continue;
                }
                for (int v = -1; v < 2; v++)
                {
                    if (i + v < 0 || i + v > height - 1)
                    {
                        continue;
                    }
                    if (i + v == i - 1 && j + h == j - 1)
                    {
                        // Deals with the pixel - 1 in the i dimension and - 1 in the j dimension, and each colour channel for that pixel is multiplied by the relevant value in either the Gy or Gx matrix.
                        redX += (image[i + v][j + h].rgbtRed * -1);
                        blueX += (image[i + v][j + h].rgbtBlue * -1);
                        greenX += (image[i + v][j + h].rgbtGreen * -1);
                        redY += (image[i + v][j + h].rgbtRed * -1);
                        blueY += (image[i + v][j + h].rgbtBlue * -1);
                        greenY += (image[i + v][j + h].rgbtGreen * -1);
                    }
    
                    if (i + v == i - 1 && j + h == j)
                    {
                        // Process continues for each adjacent pixel.
                        redX += (image[i + v][j + h].rgbtRed * 0);
                        blueX += (image[i + v][j + h].rgbtBlue * 0);
                        greenX += (image[i + v][j + h].rgbtGreen * 0);
                        redY += (image[i + v][j + h].rgbtRed * -2);
                        blueY += (image[i + v][j + h].rgbtBlue * -2);
                        greenY += (image[i + v][j + h].rgbtGreen * -2);
                    }
                    if (i + v == i - 1 && j + h == j + 1)
                    {
                        redX += (image[i + v][j + h].rgbtRed * 1);
                        blueX += (image[i + v][j + h].rgbtBlue * 1);
                        greenX += (image[i + v][j + h].rgbtGreen * 1);
                        redY += (image[i + v][j + h].rgbtRed * -1);
                        blueY += (image[i + v][j + h].rgbtBlue * -1);
                        greenY += (image[i + v][j + h].rgbtGreen * -1);
                    }
                    if (i + v == i && j + h == j - 1)
                    {
                        redX += (image[i + v][j + h].rgbtRed * -2);
                        blueX += (image[i + v][j + h].rgbtBlue * -2);
                        greenX += (image[i + v][j + h].rgbtGreen * -2);
                        redY += (image[i + v][j + h].rgbtRed * 0);
                        blueY += (image[i + v][j + h].rgbtBlue * 0);
                        greenY += (image[i + v][j + h].rgbtGreen * 0);
                    }
                    if (i + v == i && j + h == j)
                    {
                        redX += (image[i + v][j + h].rgbtRed * 0);
                        blueX += (image[i + v][j + h].rgbtBlue * 0);
                        greenX += (image[i + v][j + h].rgbtGreen * 0);
                        redY += (image[i + v][j + h].rgbtRed * 0);
                        blueY += (image[i + v][j + h].rgbtBlue * 0);
                        greenY += (image[i + v][j + h].rgbtGreen * 0);
                    }
                    if (i + v == i && j + h == j + 1)
                    {
                        redX += (image[i + v][j + h].rgbtRed * 2);
                        blueX += (image[i + v][j + h].rgbtBlue * 2);
                        greenX += (image[i + v][j + h].rgbtGreen * 2);
                        redY += (image[i + v][j + h].rgbtRed * 0);
                        blueY += (image[i + v][j + h].rgbtBlue * 0);
                        greenY += (image[i + v][j + h].rgbtGreen * 0);
                    }
                    if (i + v == i + 1 && j + h == j - 1)
                    {
                        redX += (image[i + v][j + h].rgbtRed * -1);
                        blueX += (image[i + v][j + h].rgbtBlue * -1);
                        greenX += (image[i + v][j + h].rgbtGreen * -1);
                        redY += (image[i + v][j + h].rgbtRed * 1);
                        blueY += (image[i + v][j + h].rgbtBlue * 1);
                        greenY += (image[i + v][j + h].rgbtGreen * 1);
                    }
                    if (i + v == i + 1 && j + h == j)
                    {
                        redX += (image[i + v][j + h].rgbtRed * 0);
                        blueX += (image[i + v][j + h].rgbtBlue * 0);
                        greenX += (image[i + v][j + h].rgbtGreen * 0);
                        redY += (image[i + v][j + h].rgbtRed * 2);
                        blueY += (image[i + v][j + h].rgbtBlue * 2);
                        greenY += (image[i + v][j + h].rgbtGreen * 2);
                    }
                    if (i + v == i + 1 && j + h == j + 1)
                    {
                        redX += (image[i + v][j + h].rgbtRed * 1);
                        blueX += (image[i + v][j + h].rgbtBlue * 1);
                        greenX += (image[i + v][j + h].rgbtGreen * 1);
                        redY += (image[i + v][j + h].rgbtRed * 1);
                        blueY += (image[i + v][j + h].rgbtBlue * 1);
                        greenY += (image[i + v][j + h].rgbtGreen * 1);
                    }
                }
            }
            // powf (x, y) raises x to the power y.
            float redX_2 = powf(redX, 2);
            float blueX_2 = powf(blueX, 2);
            float greenX_2 = powf(greenX, 2);
            float redY_2 = powf(redY, 2);
            float blueY_2 = powf(blueY, 2);
            float greenY_2 = powf(greenY, 2);
            // sqrt (x) takes the square root of x.
            float SobelRed = round(sqrt(redX_2 + redY_2));
            float SobelBlue = round(sqrt(blueX_2 + blueY_2));
            float SobelGreen = round(sqrt(greenX_2 + greenY_2));
            // Sobel(Colour) now represents the calculated Sobel value for each colour channel for the pixel.
            // The next round of IF statements set maximum and minimum values for each colour channel for the filtered pixel.
            if (SobelRed > 255)
            {
                image0[i][j].rgbtRed = 255;
            }
            else if (SobelRed < 0)
            {
                image0[i][j].rgbtRed = 0;
            }
            else
            {
                image0[i][j].rgbtRed = SobelRed;
            }
            if (SobelBlue > 255)
            {
                image0[i][j].rgbtBlue = 255;
            }
            else if (SobelBlue < 0)
            {
                image0[i][j].rgbtBlue = 0;
            }
            else
            {
                image0[i][j].rgbtBlue = SobelBlue;
            }
            if (SobelGreen > 255)
            {
                image0[i][j].rgbtGreen = 255;
            }
            else if (SobelGreen < 0)
            {
                image0[i][j].rgbtGreen = 0;
            }
            else
            {
                image0[i][j].rgbtGreen = SobelGreen;
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image0[i][j].rgbtRed;
            image[i][j].rgbtBlue = image0[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image0[i][j].rgbtGreen;
        }
    }
    return;
}
