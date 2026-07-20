import csv;
import sys;

def main():
    # Check for correct number of command-line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    database_file = sys.argv[1]
    sequence_file = sys.argv[2]

    # Read DNA database CSV into a list of dictionaries
    with open(database_file) as db:
        reader = csv.DictReader(db)
        # Extract STR names from the CSV header (excluding 'name')
        strs = reader.fieldnames[1:]
        # Read all rows (each is a dictionary)
        database = list(reader)

    # Read the DNA sequence to identify
    with open(sequence_file) as f:
        dna_sequence = f.read()

    # Find longest match of each STR in the DNA sequence
    str_counts = {}
    for STR in strs:
        str_counts[STR] = longest_match(dna_sequence, STR)

    # Check database for matching profiles
    for person in database:
        match = True
        for STR in strs:
            # Compare database STR count (string) with computed count (int)
            if int(person[STR]) != str_counts[STR]:
                match = False
                break
        if match:
            print(person["name"])
            return

    # If no match found
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    longest_run = 0
    sub_len = len(subsequence)
    seq_len = len(sequence)

    for i in range(seq_len):
        count = 0

        while True:
            start = i + count * sub_len
            end = start + sub_len

            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        if count > longest_run:
            longest_run = count

    return longest_run


if __name__ == "__main__":
    main()
