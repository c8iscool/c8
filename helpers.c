#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg_value = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg_value;
            image[i][j].rgbtRed = avg_value;
            image[i][j].rgbtGreen = avg_value;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round((0.393 * originalRed) + (0.769 * originalGreen) + (0.189 * originalBlue));
            int sepiaGreen = round((0.349 * originalRed) + (0.686 * originalGreen) + (0.168 * originalBlue));
            int sepiaBlue = round((0.272 * originalRed) + (0.534 * originalGreen) + (0.131 * originalBlue));

            if (sepiaBlue > 255) // ensures if rgb level is over, makes it to the max
            {
                image[i][j].rgbtBlue = 255;
            }

            else if (sepiaBlue <= 255)
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }

            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }

            else if (sepiaRed <= 255)
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }

            else if (sepiaGreen <= 255)
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE tempLeft = image[i][j];
            RGBTRIPLE tempRight = image[i][width - 1 - j];
            image[i][width - 1 - j] = tempLeft;
            image[i][j] = tempRight;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred[height][width];
    int avgRed = 0;
    int avgBlue = 0;
    int avgGreen = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalRed = 0;
            float totalBlue = 0;
            float totalGreen = 0;

            int pixelnumber = 0;

            if (i != 0 && j != 0) // top left corner
            {
                totalRed += image[i - 1][j - 1].rgbtRed;
                totalBlue += image[i - 1][j - 1].rgbtBlue;
                totalGreen += image[i - 1][j - 1].rgbtGreen;
                pixelnumber++;
            }

            if (i != 0 && j != width - 1) // top right corner
            {
                totalRed += image[i - 1][j + 1].rgbtRed;
                totalBlue += image[i - 1][j + 1].rgbtBlue;
                totalGreen += image[i - 1][j + 1].rgbtGreen;
                pixelnumber++;
            }

            if (i != height - 1 && j != 0) // bottom left corner
            {
                totalRed += image[i + 1][j - 1].rgbtRed;
                totalBlue += image[i + 1][j - 1].rgbtBlue;
                totalGreen += image[i + 1][j - 1].rgbtGreen;
                pixelnumber++;
            }

            if (i != height - 1 && j != width - 1) // bottom right corner
            {
                totalRed += image[i + 1][j + 1].rgbtRed;
                totalBlue += image[i + 1][j + 1].rgbtBlue;
                totalGreen += image[i + 1][j + 1].rgbtGreen;
                pixelnumber++;
            }

            if (i != 0) // top edge
            {
                totalRed += image[i - 1][j].rgbtRed;
                totalBlue += image[i - 1][j].rgbtBlue;
                totalGreen += image[i - 1][j].rgbtGreen;
                pixelnumber++;
            }

            if (j != 0) // left edge
            {
                totalRed += image[i][j - 1].rgbtRed;
                totalBlue += image[i][j - 1].rgbtBlue;
                totalGreen += image[i][j - 1].rgbtGreen;
                pixelnumber++;
            }

            if (i != height - 1) // bottom edge
            {
                totalRed += image[i + 1][j].rgbtRed;
                totalBlue += image[i + 1][j].rgbtBlue;
                totalGreen += image[i + 1][j].rgbtGreen;
                pixelnumber++;
            }

            if (j != width - 1) // right edge
            {
                totalRed += image[i][j + 1].rgbtRed;
                totalBlue += image[i][j + 1].rgbtBlue;
                totalGreen += image[i][j + 1].rgbtGreen;
                pixelnumber++;
            }

            totalRed += image[i][j].rgbtRed;
            totalBlue += image[i][j].rgbtBlue;
            totalGreen += image[i][j].rgbtGreen;
            pixelnumber++;

            avgRed = round(totalRed / pixelnumber);
            avgBlue = round(totalBlue / pixelnumber);
            avgGreen = round(totalGreen / pixelnumber);

            blurred[i][j].rgbtRed = avgRed;
            blurred[i][j].rgbtGreen = avgBlue;
            blurred[i][j].rgbtBlue = avgGreen;
        }

    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blurred[i][j].rgbtRed;
            image[i][j].rgbtBlue = blurred[i][j].rgbtBlue;
            image[i][j].rgbtGreen = blurred[i][j].rgbtGreen;
        }
    }
    return;
}
