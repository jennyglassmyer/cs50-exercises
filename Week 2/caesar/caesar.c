#include <stdlib.h>
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("%s key\n", argv[0]);
        return 1;
    }
    else
    {
        printf("Success\n");
        printf("%s\n", argv[1]);
    }

    string input = argv[1];
    for (int i = 0; i <= strlen(input); i++)
    {
        if (isdigit(input[i]) == 0)
        {
            printf("%s key\n", argv[0]);
            return 1;
        }
        else
        {
            int key = atoi(argv[1]);
            string text = get_string("plaintext:");
            for (int k = 0; k <= strlen(text); k++)
            {
                if (isalpha(text[k]))
                {
                    if (isupper(text[k]))
                    {
                        text[k] = (text[k] - 65  + key) % 26 + 65;
                    }
                    else
                    {
                        text[k] = (text[k] - 97 + key) % 26 + 97;
                    }
                }
            }
            printf("ciphertext: %s\n", text);
            return 0;
        }
    }
}