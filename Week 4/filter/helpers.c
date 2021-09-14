#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg_RGB = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            int new_RGB = round(avg_RGB);
            image[i][j].rgbtBlue = new_RGB;
            image[i][j].rgbtGreen = new_RGB;
            image[i][j].rgbtRed = new_RGB;
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
            //Calculate Sepia Hues
            int sepiaRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));

            int sepiaGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));

            int sepiaBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));

            //Set Blue
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }

            //Set Green

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            //Set Red
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate through each row
    for (int i = 0; i <= height; i++)
    {
        //find middle pixel
        int middle = round(width / 2);

        //iterate through each column until middle pixel and swap pixels
        for (int j = 0; j < middle; j++)
        {
            RGBTRIPLE buffer = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make copy of image for calculations
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

//iterate through rows
    for (int i = 0, total_red, total_green, total_blue, total_pixels; i < height; i++)
    {
        //iterate through columns
        for (int j = 0; j < width; j++)
        {
            //initialize variables
            total_red = 0;
            total_green = 0;
            total_blue = 0;
            total_pixels = 0;

//check each scenario of pixel location for surrounding pixels and add up totals
            if (i >= 0 && j >= 0)
            {
                total_red += copy[i][j].rgbtRed;
                total_green += copy[i][j].rgbtGreen;
                total_blue += copy[i][j].rgbtBlue;
                total_pixels++;
            }

            if (i >= 0 && j - 1 >= 0)
            {
                total_red += copy[i][j - 1].rgbtRed;
                total_green += copy[i][j - 1].rgbtGreen;
                total_blue += copy[i][j - 1].rgbtBlue;
                total_pixels++;
            }

            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                total_red += copy[i][j + 1].rgbtRed;
                total_green += copy[i][j + 1].rgbtGreen;
                total_blue += copy[i][j + 1].rgbtBlue;
                total_pixels++;
            }

            if (i - 1 >= 0 && j >= 0)
            {
                total_red += copy[i - 1][j].rgbtRed;
                total_green += copy[i - 1][j].rgbtGreen;
                total_blue += copy[i - 1][j].rgbtBlue;
                total_pixels++;
            }

            if (i - 1 >= 0 && j - 1 >= 0)
            {
                total_red += copy[i - 1][j - 1].rgbtRed;
                total_green += copy[i - 1][j - 1].rgbtGreen;
                total_blue += copy[i - 1][j - 1].rgbtBlue;
                total_pixels++;
            }

            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                total_red += copy[i - 1][j + 1].rgbtRed;
                total_green += copy[i - 1][j + 1].rgbtGreen;
                total_blue += copy[i - 1][j + 1].rgbtBlue;
                total_pixels++;
            }

            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                total_red += copy[i + 1][j].rgbtRed;
                total_green += copy[i + 1][j].rgbtGreen;
                total_blue += copy[i + 1][j].rgbtBlue;
                total_pixels++;
            }

            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                total_red += copy[i + 1][j - 1].rgbtRed;
                total_green += copy[i + 1][j - 1].rgbtGreen;
                total_blue += copy[i + 1][j - 1].rgbtBlue;
                total_pixels++;
            }

            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                total_red += copy[i + 1][j + 1].rgbtRed;
                total_green += copy[i + 1][j + 1].rgbtGreen;
                total_blue += copy[i + 1][j + 1].rgbtBlue;
                total_pixels++;
            }

            //calculate average of red, green, and blue and update original image with new color amounts

            image[i][j].rgbtRed = round(total_red / (total_pixels * 1.0));
            image[i][j].rgbtGreen = round(total_green / (total_pixels * 1.0));
            image[i][j].rgbtBlue = round(total_blue / (total_pixels * 1.0));
        }
    }

    return;
}