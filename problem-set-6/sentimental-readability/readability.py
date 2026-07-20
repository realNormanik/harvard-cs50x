from cs50 import get_string;

def main():
    # Prompt the user to enter a text string
    text = get_string("Text: ")

    # Count the total number of letters in the input text
    letters = count_letters(text)
    # Count the total number of words in the input text
    words = count_words(text)
    # Count the total number of sentences in the input text
    sentences = count_sentences(text)

    # Calculate the average number of letters per 100 words
    L = (letters / words) * 100
    # Calculate the average number of sentences per 100 words
    S = (sentences / words) * 100

    # Compute the Coleman-Liau index using the formula:
    # index = 0.0588 * L - 0.296 * S - 15.8
    index = 0.0588 * L - 0.296 * S - 15.8
    # Round the index to the nearest whole number to get the grade level
    grade = round(index)

    # Determine the readability grade level to print
    if grade < 1:
        # If grade is less than 1, print special message
        print("Before Grade 1")
    elif grade >= 16:
        # If grade is 16 or higher, print "Grade 16+"
        print("Grade 16+")
    else:
        # Otherwise, print the grade number
        print(f"Grade {grade}")


def count_letters(text):
    count = 0
    # Iterate over every character in the text
    for char in text:
        # Check if the character is an alphabetical letter (A-Z or a-z)
        if char.isalpha():
            count += 1  # Increment letter count if true
    return count  # Return total letters counted


def count_words(text):
    # Split the text into words by spaces (assuming words are separated by spaces)
    words = text.split()
    # Return the total number of words
    return len(words)


def count_sentences(text):
    count = 0
    # Iterate over every character in the text
    for char in text:
        # Check if the character indicates end of a sentence
        if char in ['.', '!', '?']:
            count += 1  # Increment sentence count
    return count  # Return total sentences counted


if __name__ == "__main__":
    main()
