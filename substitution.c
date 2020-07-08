#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

//Declare functions for use in Main

int Count_Letters(string);
bool UNIQUE(string);

int main(int argc, string argv[])
{
//I kept getting 'Segmentation Fault' returned when no key was entered so I create an infinite while loop to prevent the program from running any further until argc == 2
    while (argc != 2)
    {
        printf("NO KEY\n)");
        return 1;
    }
    int key_length = Count_Letters(argv[1]);
    bool unique = UNIQUE(argv[1]);
//If a 26 alphabetic code is entered into the command line following ./substitution (hence == 2) and each letter appears only once then User is prompted to enter plain text.
    if (argc == 2 && key_length == 26 && unique == true)
    {
        string pt = get_string("plaintext: ");
        string ct = argv[1];
        int n = strlen(pt);
        printf("ciphertext: ");
        for (int i = 0; i < n; i++)
        {
//Check whether character at [i] is lowercase.
            if (islower(pt[i]))
            {
//Match letter in KEY.
                int j = pt[i] - 97;
//Convert letter in ct to lowercase in ct.
                printf("%c", tolower(ct[j]));
            }
//Check whether character at [i] in pt is uppercase.
            else if (isupper(pt[i]))
            {
//Match letter in KEY.
                int y = pt[i] - 65;
//Convert letter in ct to uppercase in ct and print.
                printf("%c", toupper(ct[y]));
            }
//If neither an uppercase nor lowercase alpabetical character, leave unchanged.
            else
            {
//Print character unchanged.
                printf("%c", pt[i]);
            }
        }
//No new lines printed until all characters are encrypted.
        printf("\n");
        return 0;
    }
    else
    {
        printf("ERROR\n");
        return 1;
    }
}

//Write Count_Letters Code
//Using a For loop for the entire length of a given string, if an element of that string is alpha, then letter variable increases by 1.

int Count_Letters(string A)
{
    int LENGTH = strlen(A);
    int letter = 0;
    for (int i = 0; i < LENGTH; i++)
    {
        if (isalpha(A[i]))
        {
            letter++;
        }
    }
    return letter;
}

//Write Each_Letter_Once Code to ensure each letter is included once and only once.

bool UNIQUE(string B)
{
    float LENGTHB = strlen(B);
    for (int i = 0; i < LENGTHB; i++)
    {
        for (int x = i + 1; x < LENGTHB; x++)
        {
            if (B[i] == B[x])
            {
                return false;
            }
        }
    }
    return true;
}




