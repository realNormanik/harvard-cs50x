from cs50 import get_float;

# Ask for a value until the user provides a non-negative number
while True:
    change = get_float("Change owed: ")
    if change >= 0:
        break

# Converting dollars to cents (we round up to avoid float problems)
cents = round(change * 100)

coins = 0

# We use the largest coins sequentially: 25, 10, 5, 1
for coin_value in [25, 10, 5, 1]:
    coins += cents // coin_value
    cents %= coin_value

print(coins)
