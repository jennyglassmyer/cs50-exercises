#include <cs50.h>
#include <stdio.h>

int main(void)
{
int height;
//get user input
  do
  {
      height = get_int("Height of Pyramid: ");
  }
  while (height > 8 || height < 1);

//loop for the rows
for (int row = 1; row <= height; row++)
    {
        //loop for spaces
        for (int spaces = (height - row) ; spaces > 0; spaces--)
        {
            printf(" ");
        }
        //loop for hashes
        for (int hashes = 1; hashes <= row; hashes++)
        {
            printf("#");
        }
        printf("\n");
    }
}