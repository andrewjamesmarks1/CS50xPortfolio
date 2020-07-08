from cs50 import get_int
from sys import exit
from math import floor

# Obtain Credit Card Number from User, repeating using a while loop until the number provider is an integer between 1 and 16 digits.
number = get_int("What's your Credit Card Number?\n")
while number < 0 and number > 9999999999999999:
    number = get_int("What's your Credit Card Number?\n")

# Count integers in number - cast to string and carry out len(str)
count = len(str(number))
if count != 13 and count != 15 and count != 16:
    print("INVALID")
    # Import exit to exit programme if card number invalid after printing INVALID.
    exit()

# Luhns algorithm.
S = 0
temp = number
for i in range(count, - 1):
    # Modulo 10 provides the last digit in the number.
    digit = temp % 10
    # Checks to see if the digit is an even digit.
    if i % 2 == 0:
        # If even, multiply by 2.
        digit *= 2
        if digit >= 10:
            digit += 1
    # If the digit is an odd digit, it is simply added to S and temp is divided through 10 to move to next digit.
    S += digit
    temp /= 10

if S % 10 != 0:
    print("INVALID")
    exit()

else:
    v2 = number

    while v2 > 100:
        v2 = v2 / 10

    credit_provider = floor(v2)

    if credit_provider > 50 and credit_provider < 56 and count == 16:
        print("MASTERCARD")
    elif (credit_provider > 39 and credit_provider < 50) and (count == 13 or count == 16):
        print("VISA")
    elif credit_provider == 34 or credit_provider == 37 and count == 15:
        print("AMEX")
    else:
        print("INVALID", end="")
print()