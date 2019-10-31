from cs50 import get_string, SQL
import sys
import csv

if len(sys.argv) != 3:
    sys.exit("Incorrect argument count")

db = SQL("sqlite:///students.db")

reader = csv.DictReader(open(sys.argv[2]))

for x in reader:
    y = x["name"].split()
    if len(y) == 3:
        first = db.execute("INSERT INTO students (first) VALUES (?)", y[0])
        middle = db.execute("INSERT INTO students (middle) VALUES (?)", y[1])
        last = db.execute("INSERT INTO students (last) VALUES (?)", y[2])
    if len(y) == 2:
        first = db.execute("INSERT INTO students (first) VALUES (?)", y[0])
        middle = db.execute("INSERT INTO students (middle) VALUES (?)", None)
        last = db.execute("INSERT INTO students (last) VALUES (?)", y[2])

# Add new person
#name = get_string("Name: ")
#student_id = db.execute("INSERT INTO people (name) VALUES (?)", name)

# Prompt for courses to enroll in
while True:
    code = get_string("Course Code: ")

    # If no input, then stop adding courses
    if not code:
        break

    # Query for course
    results = db.execute("SELECT id FROM courses WHERE code = ?", code)

    # Check to make sure course exists
    if len(results) == 0:
        print(f"No course with code {code}.")
        continue

    # Enroll student
    db.execute("INSERT INTO students (person_id, course_id) VALUES (?, ?)", student_id, results[0]["id"])
    print(f"Added {name} to {code}")