import csv

with open("file name", "r") as file:
    reader = csv.DictReader(file)

    for row in reader:

        title = row["title"].lower()

        if title in counts:
            counts[title] += 1
        else:
            counts[title] = 1

#def f(item):   REPLACED by lambda
    #return item[1]

for title, count in sorted(counts.items(), key=lambda item: item[1], reverse=True):
    print(title, count, sep="|")