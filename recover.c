#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    //Ensures function only accepts one command line argument.
    if (argc != 2)
    {
        printf("Usage: Please enter filename only.\n");
        return 1;
    }
    //Opens file inputted in the command line argument.
    FILE *file = fopen(argv[1], "r");
    //Checks file opens.
    if (!file)
    {
        return 1;
    }
    //initialise variable 'counter' to 0 to allow for naming of jpgs as they are found.
    int counter = 0;
    //Boolean operator to signal when a new jpg is found.
    bool new_jpeg = false;
    //Create a file pointer, pointing to a file img that is NULL.
    FILE *img = NULL;
    unsigned char buffer[512];
    char filename[8];
    //Reads across file in blocks of 512 bytes until a block is found which is less than 512 bytes, signifying the end of the memory card.
    while (fread(buffer, 512, 1, file) == 1)
    {
        //Finds the signature first 4 bytes of a jpg.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {   
            //Iteration of the nested if/else only occures if the signature is detected. 
            //In the first iteration, new_jpeg = false, so when the first jpg is found there is no img file to close.
            //Once the function finds a new jpg, new_jpeg is set to true. 
            if (new_jpeg == true)
            {
                //closes img if new jpg signature is found.
                fclose(img);
            }
            else
            {
                //Once the function finds a new jpg, new_jpeg is set to true.
                new_jpeg = true;
            }
            //The new jpg is opened, and writeable, 
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            //Counter increases so that each new jpg is named incrementally.
            counter++;
        }
        //In the instance that no new jpg signature is found in a 512 byte block the data is written the img file still open.
        if (new_jpeg == true)
        {
            fwrite(&buffer, 512, 1, img);
        }
    }
    //Once fread at 29 returns a value other than 1, files are closed and main returns 0.
    fclose(file);
    fclose(img);
    
    return 0;
}