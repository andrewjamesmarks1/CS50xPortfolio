import csv
import sys

def main():

    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit
    
    with open(sys.argv[1], "r") as database:
        database_reader = csv.reader(database)
        database_reader = list(database_reader)
        lines = len(database_reader)

    with open(sys.argv[2], "r") as sequence:
        dna_sequence = csv.reader(sequence)
        dna_sequence = list(dna_sequence)
    
    number = len(database_reader[0]) - 1
    #returns the number of STRs in the .csv, in the case of large.csv this is 8
    check_list = []
    #new list to contain the number of repeats of each STR in the dna_sequence
    for i in range(1, number + 1):
        check_list.append(max_reps(database_reader[0][i], dna_sequence))
    
    for j in range(1, lines - 1):
        matches = 0
        for k in range(1, number + 1):
            if (int(database_reader[j][k]) == int(check_list[k - 1])):
                matches += 1
        if matches == number:
            print(database_reader[j][0])
            break
    if matches != number:
        print("No Match")

def max_reps(s_t_r, seq):
    counter = 0
    start = 0
    end = 0
    s_t_r_length = len(s_t_r)
    list_max_reps = []
    while True:
        s_t_r_found = seq[0][0].find(s_t_r, start)
        if s_t_r_found == -1:
            break
        if start != s_t_r_found:
            counter = 1
            counter += 0
            start = s_t_r_found + s_t_r_length
        else:
            counter += 1
            start = s_t_r_found + s_t_r_length
        list_max_reps.append(counter)
    list_max_reps.sort()
    s_t_rs = len(list_max_reps)
    return list_max_reps[s_t_rs - 1] 
    
main()