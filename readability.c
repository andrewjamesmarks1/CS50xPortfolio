#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

//Declare Count_Letters, Count_Words and Count_Sentences Functions

float Count_Letters(string);
float Count_Words(string);
float Count_Sentences(string);

int main(void)
{
//Ask use for text input and then call the functions Count_Letters, Count_Words and Count_Sentences to apply to the input. 
    string INPUT = get_string("Text:  ");
    float LETTER = Count_Letters(INPUT);
    float WORD = Count_Words(INPUT);
    float SENTENCE = Count_Sentences(INPUT);

//define variable L, variable S and input into variable Grade which contains the Coleman-liau Index calculation.
    float L = (LETTER / WORD) * 100;
    float S = (SENTENCE / WORD) * 100;
    float GRADE = 0.0588 * L - 0.296 * S - 15.8;
//if, else if, else prints the required output based on the result of the calculation of GRADE.
    if (GRADE < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (GRADE >= 1 && GRADE < 17)
    {
        printf("Grade %.0f\n", GRADE);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

//Write Count_Letters Code
//Using a For loop for the entire length of a given string, if an element of that string is alphanumeric, then letter variable increases by 1.

float Count_Letters(string A)
{
    float LENGTH = strlen(A);
    float letter = 0;
    for (int i = 0; i < LENGTH; i++)
    {
        if (isalnum(A[i]))
        {
            letter++;
        }
    }
    return letter;
}

//Write Count_Words Code
//Using a For loop for the entire length of a given string, if an element of that string is a space, and the next element is a graphical character, then the word variable increase by 1.
//float word set to 1 initially as the first word would otherwise not be counted, as it is not preceded by a space. 

float Count_Words(string B)
{
    float LENGTHB = strlen(B);
    float word = 1;
    for (int i = 0; i < LENGTHB; i++)
    {
//Look for [i] is a space and what the nature of [i+1] is. Alice got me on this one hard! I changed to isgraph from is alnum to allow for quotations which finally brought Alice back to reality.              
        if (isspace(B[i]) && isgraph(B[i + 1]))
        {
            word++;
        }
    }
    return word;
}

//Write Count_Sentences Code

float Count_Sentences(string C)
{
    float LENGTHC = strlen(C);
    float sentence = 0;
    for (int i = 0; i < LENGTHC; i++)
    {
        if (C[i] == '!' || C[i] == '.' || C[i] == '?')
        {
            sentence++;
        }
    }
    return sentence;
}
