#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check if one command line argument or return 1
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //open memory card and return error if it cannot be opened for reading
    char *input = argv[1];
    FILE *memcard = fopen(input, "r");

    if (memcard == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // read one 512 byte block at a time and repeat until end of memcard
    //read 512 bytes into the buffer
    BYTE buffer[512];
    int counter = 0;
    FILE *img = NULL;
    char *filename = malloc(8);

    while (fread(&buffer, 512, 1, memcard) == 1)
    {
        //check if block is the beginning of a jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //check if it is the first one, and if not, close the previously open file
            if (!(counter == 0))
            {
                fclose(img);
            }
            //name and open a new jpg and increase counter by 1
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter++;
        }
        //if block is not the beginning of jpg file, write block to currently open jpg file
        if (!(counter == 0))
        {
            fwrite(&buffer, 512, 1, img);
        }

    }

    //close any remaining open files
    fclose(img);
    free(filename);
    return 0;
}

