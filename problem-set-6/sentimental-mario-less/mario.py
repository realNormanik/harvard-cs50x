from cs50 import get_int

# Repeatedly prompt user until a valid height is provided
while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# Generate half-pyramid
for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i)
