import cs50
import sys
import csv

open("students.db", "w").close()

db = cs50.SQL("sqlite:///students.db")

db.execute("CREATE TABLE Students (first TEXT, middle TEXT, last TEXT, birth NUMERIC, house TEXT)")

if len(sys.argv) != 2:
    print("Usage: python import.py characters.csv")
    exit

with open(sys.argv[1], "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        names = row["name"].split()
        if len(names) == 2:
            names.insert(1, None)
        first = names[0]
        middle = names[1]
        last = names[2]
        birth = row["birth"]
        house = row["house"]

        db.execute("INSERT INTO students (first, middle, last, birth, house) VALUES(?, ?, ?, ?, ?)",
                   first, middle, last, birth, house)

