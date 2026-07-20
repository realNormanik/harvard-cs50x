from cs50 import get_int

# Repeatedly prompt until user provides a valid height
while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# Generate two half-pyramids with a gap of 2 spaces
for i in range(1, height + 1):
    spaces = " " * (height - i)
    hashes = "#" * i
    print(f"{spaces}{hashes}  {hashes}")
