#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main(void)
{   float change = 0.0;
    do
    { 
        change = get_float("How much change is owed?\n");
    }
    while (change <= 0);

    printf("Change Owed: %f\n", change);

    int total_coins = 0;
    int cents = round(change * 100);


   do
   {
        while ((cents / 25) >= 1)
        { cents = cents - 25;
        total_coins++;
        }

        while ((cents / 10) >= 1)
        { cents = cents - 10;
        total_coins++;
        }

        while ((cents / 5) >= 1)
        { cents = cents - 5;
        total_coins++;
        }

        while ((cents / 1) >= 1)
        { cents = cents - 1;
        total_coins++;
        }
    }
    while (cents > 0);
    printf("%i\n", total_coins);
}