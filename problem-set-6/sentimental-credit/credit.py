from cs50 import get_string;

def luhn_algorithm(card_number):
    """
    Implementacja algorytmu Luhna do sprawdzenia poprawności numeru karty.
    """
    total = 0
    num_digits = len(card_number)
    parity = num_digits % 2

    for i in range(num_digits):
        digit = int(card_number[i])
        if i % 2 == parity:
            digit *= 2
            if digit > 9:
                digit -= 9
        total += digit

    return total % 10 == 0


def main():
    # Get the card number from the user (string)
    card_number = get_string("Number: ")

    # Check the length and type of card according to the specification
    if not card_number.isdigit():
        print("INVALID")
        return

    if not luhn_algorithm(card_number):
        print("INVALID")
        return

    length = len(card_number)

    # American Express check (15 digits, starts with 34 or 37)
    if length == 15 and (card_number.startswith("34") or card_number.startswith("37")):
        print("AMEX")
        return

    # MasterCard check (16 digits, starts with 51-55)
    if length == 16 and card_number[:2] in ["51", "52", "53", "54", "55"]:
        print("MASTERCARD")
        return

    # Visa check (13 or 16 digits, starts with 4)
    if (length == 13 or length == 16) and card_number.startswith("4"):
        print("VISA")
        return

    # If nothing matches, INVALID
    print("INVALID")


if __name__ == "__main__":
    main()
