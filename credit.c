#include <cs50.h>
#include <stdio.h>

int main(void)
// Obtain Credit Card Number from User, repeating using a while loop until the number provider is an integer between 1 and 16 digits.
{
    long NUMBER = get_long("What is your Credit Card Number?\n");
    while (NUMBER < 1 || NUMBER > 9999999999999999)
    {
        NUMBER = get_long("What is your Credit Card Number?\n");
    }
// Assign NUMBER to a new LONG variable a V (for variable) to allow manipulation of the NUMBER.
    long V = NUMBER;
// Using INT rather than FLOAT means dividing by ten takes off the last digit in each iteration of the loop.
// INT variable assigned as 0. COUNT is the number of digits in the NUMBER
// COUNT++ increments COUNT by 1 whilst V (or the CARD NUMBER) is greater than 0. It will only reach 0 once all the possible divisions by 10 have been carried out, the COUNT at the end of the while loop providing the number of digits in the NUMBER.
    int COUNT = 0;

    while (V > 0)
    {
        V = V / 10;
        COUNT++;
    }
// per the Problem Set, the Visa/Amex/Mastercard card numbers could only be of lenghts 13, 15 or 16 and so by using a conditional statement as at 25, to find that if the condition were not met the result of the progrm would be that the card number is INVALID.
    if (COUNT != 13 && COUNT != 15 && COUNT != 16)
    {
        printf("INVALID\n");
        return 0;
    }
// The next stage is to run Luhn's algorithm. 
    {
        int SUM = 0;
// At 32, I have created and declared the INT variable SUM, and set its initial value to 0.
// I have again assigned another LONG variable 'TEMP' to allow manipulation on NUMBER.
        long TEMP = NUMBER;
// Using the 'for' loop, I have created an INT variable i, set to 1. As per the 'Short' lecture on EdX, the 'for' loop is useful when you need to loop for a specific number of times, but you do not know that number whilst compiling the programme. In this case, to quote (painfully) Donald Rumsfeld, the known unknown is COUNT, which was determined earlier, and is the number of digits in the card number. The 'for' loop will continue to run until i <= number of digits on the card, and will increment i after each iteration.
        for (int i = 1; i <= COUNT; i++)
        {
            int DIGIT = (TEMP % 10);
// By taking the remainder of TEMP divided through 10, we are provided with the last digit of the card numebr. I have created a new INT variable called DIGIT, and assigned its value as the remainder of the card number divided through 10, to give the last digit.
// I then use a conditional, such that if the INT i, when divided by 2 has a remainder of 0, it is an EVEN number, counting backwards from the last digit of the card, i.e, in the first iteration it will not be, and therefore therefore it is not multiplied by 2, it is added to the SUM and the TEMP is divided through 10 to "cut off" the last digit, and i is incremented by 1. Now therefore, the 'new' value of TEMP runs through the loop. i is now 2, so has a remainder zero at line 42 and so the mutliplication by 2 is carried out. This continues for as long as i is less than or equal to the number of digits in the card number. 
            if (i % 2 == 0)
            {
                DIGIT *= 2;
                if (DIGIT >= 10)
                {
                    DIGIT += 1;
                }
            }

            SUM += DIGIT;
            TEMP /= 10;
        }    
//Once the iteration is completed, we have multiplied the necessary numbers by 2, added the products of those together to give, say SUM(A), and then added that SUM(A) to all of the numbers that were not multiplied by two. This is carried out specifically at Line 51.
        if (SUM % 10 != 0)
//The final stage of the algorithm is to determine whether the last digit of the sum calculated ends in a zero. If the remainder when the SUM is divided by 10 is NOT zero, then the card is invalid, and 58 would print out the message "INVALID"
        {
            printf("INVALID\n");
            return 0;
        }
//If the card is valid at this point, then the ELSE at line 62 is executed. I have again created an INT variable, V2, to manipulate instead of directly manipulating NUMBER. The reason for this is that several different manipulations have had to be run on NUMBER throughout the validation process. 
        else
        {
            long V2 = NUMBER;

            while (V2 > 100)
            {
                V2 = (V2 / 10);
            }
// At 66-69, the while loop cuts the card number dow by a single digit until there are only 2 digits remaining.
// Here I have created an INT variable valled CREDIT_PROVIDER, an integer as the card provider can be determined by the first two digits of the card number. 
            int CREDIT_PROVIDER = V2;

            if (CREDIT_PROVIDER > 50 && CREDIT_PROVIDER < 56 && COUNT == 16)
            {
                printf("MASTERCARD\n");
            }
            else if ((CREDIT_PROVIDER > 39 && CREDIT_PROVIDER < 50) && (COUNT == 13 || COUNT == 16))
            {
                printf("VISA\n");
            }
            else if ((CREDIT_PROVIDER == 34 || CREDIT_PROVIDER == 37) && (COUNT == 15))
            {
                printf("AMEX\n");
            }
            else
            {   
                printf("INVALID\n");
            }
            return 0;
// The above IF/ELSE loop at 74 to 90 provides the output as to the card provider, using BOOLEAN expressions to define what the parameters of each card provider are. By way of example, at 82, and courtesy of the information in the Problem, we know that AMEX cards begin with either 34 OR 37, AND have 15 digits. if the expression is true, the card is an AMEX, and the print out reads AMEX.
        }
    }
}





