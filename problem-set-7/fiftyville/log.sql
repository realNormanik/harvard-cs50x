-- Keep a log of any SQL queries you execute as you solve the mystery.

-- List all tables in the database
.tables

-- Check the structure of the crime_scene_reports table
.schema crime_scene_reports

-- Look for the report of the theft on July 28, 2024 on Humphrey Street
SELECT * FROM crime_scene_reports
WHERE date = "2024-07-28" AND street = "Humphrey Street";

-- Note: The report is at 10:15am and mentions three witnesses: Ruth, Eugene, and Raymond

-- Check the structure of the interviews table
.schema interviews

-- Find all interviews on July 28, 2024
SELECT * FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28;

-- Note: Witnesses say the thief left town on a flight after 10:15 with the help of an accomplice who booked the flight.
-- They also mention an ATM withdrawal, a phone call, and courthouse security footage.

-- Look for all flights on July 28, 2024 after 10:15am
SELECT * FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE year = 2024 AND month = 7 AND day = 28
ORDER BY hour, minute;

-- Note: The earliest flight after 10:15 is flight 36 to New York City at 10:16am

-- Find the list of passengers on flight 36
SELECT * FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
WHERE flight_id = 36;

-- Note: There are 8 passengers. We need to determine which one is the thief.

-- Find people who withdrew money from the ATM in Fiftyville on July 28
SELECT * FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = 2024 AND month = 7 AND day = 28
  AND atm_location = "Fiftyville"
  AND transaction_type = "withdraw";

-- Look for people from flight 36 who also withdrew money on July 28

-- Look up courthouse security logs on July 28, 2024 at 10am
SELECT * FROM courthouse_security_logs
JOIN people ON courthouse_security_logs.license_plate = people.license_plate
WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10;

-- Find people seen in security footage and match with flight and ATM data

-- Check phone calls made on July 28, 2024 with duration less than 1 minute
SELECT * FROM phone_calls
JOIN people caller ON caller.phone_number = phone_calls.caller
JOIN people receiver ON receiver.phone_number = phone_calls.receiver
WHERE year = 2024 AND month = 7 AND day = 28
  AND duration < 60;

-- Note: The thief made a short phone call to the accomplice. Match caller from flight with other clues.

-- Conclusion: The person matching flight 36, ATM transaction, courthouse security logs, and phone call is Bruce.
-- His accomplice is Robin. They escaped to New York City.
