from cs50 import get_float
import math

while True:
    cash = get_float("Changed owed: ")
    if cash >= 0:
        break

cents = round(cash * 100)

quarters = math.floor(cents / 25)
cents = cents - 25 * quarters
dimes = math.floor(cents / 10)
cents = cents - 10 * dimes
nickels = math.floor(cents / 5)
cents = cents - 5 * nickels
pennies = cents

coins = quarters + dimes + nickels + pennies
print(f"{round(coins)}")