from cs50 import get_int

while True:
    n = get_int("Height: ")
    if n >= 1 and n <= 8:
        break

brick = 0
for brick in range(n):
    print(" " * (n - brick - 1), end="")
    print("#" * (brick + 1))
    brick += brick
