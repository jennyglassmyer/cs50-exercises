#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text:");
    //printf("%s\n", text);

    int num_of_letters = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
        if (isalpha(text[i]))
        {
            num_of_letters++;
        }
    printf("%i letter(s)\n", num_of_letters);

    int num_of_words = 1;

    for (int i = 0, len = strlen(text); i < len; i++)
        if (isspace(text[i]))
        {
            num_of_words++;
        }
    printf("%i word(s)\n", num_of_words);

    int num_of_sentences = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
        if (text[i] == '.')
        {
            num_of_sentences++;
        }
        else if (text[i] == '!')
        {
            num_of_sentences++;
        }
        else if (text[i] == '?')
        {
            num_of_sentences++;
        }

    printf("%i sentence(s)\n", num_of_sentences);

    float letters_per_100words = ((num_of_letters * 1.0) / (num_of_words * 1.0)) * 100;
    printf("%f\n", letters_per_100words);
    float sentences_per_100words = ((num_of_sentences * 1.0) / (num_of_words * 1.0)) * 100;
    printf("%f\n", sentences_per_100words);

    float index = 0.0588 * letters_per_100words - 0.296 * sentences_per_100words - 15.8;
    printf("%f", index);
    int grade_level = round(index);
    printf("%i", grade_level);

    if (grade_level >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade_level < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade_level);
    }
}