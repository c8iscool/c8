from cs50 import get_string, SQL
import sys
import csv

if len(sys.argv) != 2:
    sys.exit("Incorrect argument count")

db = SQL("sqlite:///students.db")

people = db.execute("SELECT * FROM students WHERE house = (?) ORDER BY last, first", sys.argv[1])

for person in people:
    f = person["first"]
    m = person["middle"]
    l = person["last"]
    b = person["birth"]
    if person["middle"] != None:
        print(f"{f} {m} {l}, born {b}")
    else:
        print(f"{f} {l}, born {b}")

