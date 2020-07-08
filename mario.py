from cs50 import get_int
from sys import exit

while True:
    # Prompt user for input.
    h = get_int("How tall would you like the pyramid to be?")
    # Ensure input between 1 and 8.
    if h > 0 and h < 9:
        break
# Iterate over height
for i in range(h):
    # Print (h - i - 1) spaces and no new line. For user input 8 this will print (8 - 0 - 1) spaces on the first iteration, i.e 7 spaces.
    for j in range(h - i - 1):
        print(' ', end="")
    # Print (i + 1) # for each row and no new line. For user input 8 this will print (0 + 1) # on the first iteration.
    for k in range(i + 1):
        print('#', end="")
    # Print double space and no new line.
    print("  ", end="")
    # Print (i + 1) # for each row and no new line. For user input 8, this will print (0 + 1) # on the first iteration.
    for l in range(i + 1):
        print('#', end="")
    # Print new line after end of each row.
    print("")