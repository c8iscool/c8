from cs50 import get_string, SQL
import sys
import csv

if len(sys.argv) != 2:
    sys.exit("Incorrect argument count")

db = SQL("sqlite:///students.db")

reader = csv.DictReader(open(sys.argv[1]))

for x in reader:
    y = x["name"].split()
    if len(y) == 3:
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?,?,?,?,?)", y[0], y[1], y[2], x["house"], x["birth"])
    if len(y) == 2:
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?,?,?,?,?)", y[0], None, y[1], x["house"], x["birth"])