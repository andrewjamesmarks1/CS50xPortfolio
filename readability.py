from cs50 import get_string


text = get_string("Text: ")

sentence = 0
letter = 0

# Find length of text input.
n = len(text)

# Loop over length, if ith element is an alphanumeric increment letter variable.
for i in range(n):
    if text[i].isalnum() == True:
        letter += 1

word = len(text.split())

# # Loop over length, if ith element is ?, . or ! increment sentence variable.
for i in range(n):
    if (text[i] == "?" or text[i] == "." or text[i] == "!"):
        sentence += 1

# Calculate l and s.
l = (letter / word) * 100
s = (sentence / word) * 100

# Determine g using algorithm.
g = round(0.0588 * l - 0.296 * s - 15.8)

# Print g.
if g < 1:
    print("Before Grade 1")
elif g >= 1 and g < 17:
    print(f"Grade {g}")
else:
    print("Grade 16+")