import csv
import sys

def main():
    if len(sys.argv) != 3:
        sys.exit("Incorrect argument count")

    f1 = open(sys.argv[1])
    f = csv.DictReader(f1)
    fields = f.fieldnames[1:]
    dnamem = open(sys.argv[2]).read()

    match = False

    for row in f:
        matches = 0
        for field in fields:
            maxrepeat = 0
            for cursor in range(0, len(dnamem)):
                counter = 0
                while True:
                    if dnamem[cursor : len(field) + cursor] == field:
                        counter += 1
                        cursor += len(field)
                    else:
                        break
                if counter > maxrepeat:
                    maxrepeat = counter
            if int(row[field]) == maxrepeat:
                matches += 1
        if matches == len(fields):
            match = True
            print(row['name'])

    if match == False:
        print("No match")

main()