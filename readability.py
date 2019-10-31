from cs50 import get_string

letters = 0
words = 1
sentences = 0

text = get_string("Text: ");

for i in range(len(text)):
    if str.isalpha(text[i]) != 0:
        letters += 1 #counts number of alphabetic characters in the string text

    if text[i] == " " and text[i + 1] != " ":
        words += 1
#counts number of spaces in the string, since there is one fewer space than #words words=1
#checks that the next char after space is an alphabetic letter

    if text[i] == "." or text[i] == "!" or text[i] == "?":
        sentences += 1

L = (letters * 100.0 / words);
S = (sentences * 100.0 / words)
index = round((0.0588 * L) - (0.296 * S) - 15.8)

if index < 16 and index >= 1:
    print(f"Grade {index}")

elif index >= 16:
    print("Grade 16+")

elif index < 1:
    print("Before Grade 1")