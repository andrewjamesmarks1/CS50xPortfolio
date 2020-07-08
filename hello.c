#include <stdio.h>

//to incorporate cs50 specific options.

#include <cs50.h>

//string name at 13 creates a variable called name in the form of a string.
//get_string is a <cs50.h> specific function allowing the user to enter their name.
//%s is a space filler, which fills in the name entered by the user when producing the hello, X output.

int main(void)
{
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}

