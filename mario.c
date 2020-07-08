#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //defines Integer H, in our case the height of the pyramid, using a Do/While loop to ask the user the same question until they meet the condition in while, ie a positive integer between 1 and 8.

    int h;
    do
    {
        h = get_int("How tall would you like the pyramid to be?");
    }
    while (h < 1 || (h > 8));
    
//I originally attempted this by using Char = "#" but looking at it from a mathematical perspective it became clear that a certain number of HASH's were require and a certain number of SPACE's were required on each row. 

    int HASH;
    int SPACE;
    int LAYER;

//The lines below sets the number of layer to match with the height chosen at line 11. The number of layers is initially set at 0, so long as the condition (LAYER <= h) is true, another layer is added with LAYER ++.
//For each layer it is then a question of calculating how many SPACE there should be, and how many HASH. The number of SPACES at the top of the pyramid is MAX and therefore SPACE should be printed first, using the 'for' functionality. The initial condition is that the number of SPACE should equal the height of the pyramid minus the number of HASH there should be on the LAYER, and as the LAYER number increases (ie we move down the pyramid) the number of SPACE should decrease. NOTE, no use of \n to print new line after printing SPACE to ensure HASH follow in same line. Process repeated for HASH, addition of a '  ' and then reversed calculations for the mirrored side of the pyramid. After each LAYER is printed, \n is utilised via printf("\n") to loop to create the next LAYER below.

    for (LAYER=1;LAYER<=h;LAYER++)
    {  
        for (SPACE=(h-LAYER);SPACE>0;SPACE--) 
        {
            printf(" ");
        }
        for (HASH=1;HASH<=(LAYER + 0);HASH++)
        {
            printf("#");
        }
        printf("  ");
        for (HASH=1;HASH<=(LAYER+0);HASH++)
        {
            printf("#");
        }
        for (SPACE=(h-LAYER);SPACE>0;SPACE--)
        {
            printf(" ");
        }
    printf("\n");
    }
}
