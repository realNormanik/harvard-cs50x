# CS50X – Problem Set 7: Fiftyville

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. Unlike the previous SQL problem sets, this task presented an open-ended **detective mystery**: the CS50 Duck had been stolen from Humphrey Street on July 28, 2025, and the thief was believed to have fled town on a flight shortly afterward with the help of an accomplice. Using only SQL `SELECT` queries against a provided database, `fiftyville.db`, the goal was to investigate a variety of town records — crime scene reports, witness interviews, phone records, bank transactions, and flight data — to identify **who the thief was**, **what city they escaped to**, and **who their accomplice was**.

## 🎯 Objective

The main objectives of this task were to get familiar with:
- exploring an unfamiliar, multi-table relational database from scratch using `.tables` and `.schema` in SQLite,
- formulating a step-by-step investigative strategy, using the results of one query to inform the next,
- writing progressively more targeted `SELECT` queries with `WHERE`, `JOIN`, and nested subqueries to narrow down a large dataset to a small set of relevant records,
- cross-referencing data across multiple, seemingly unrelated tables (crime reports, interviews, phone calls, financial transactions, and travel records) to piece together a coherent narrative,
- documenting an investigative process clearly and legibly, using SQL comments to explain the purpose and reasoning behind each query,
- applying critical thinking and deductive reasoning to distinguish relevant clues from irrelevant "noise" in witness statements and records,
- the tools provided by CS50 for verifying the correctness (`check50`) of the final answers, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/7/fiftyville.zip
   ```
2. Extracted the downloaded archive to create a folder called `fiftyville`:
   ```bash
   unzip fiftyville.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm fiftyville.zip
   ```
4. Navigated into the `fiftyville` folder:
   ```bash
   cd fiftyville
   ```
5. Opened the provided database in an interactive SQLite session and explored its structure:
   ```bash
   sqlite3 fiftyville.db
   ```
   ```sql
   .tables
   .schema TABLE_NAME
   ```
6. Began the investigation with the `crime_scene_reports` table, searching for a report matching the known date (July 28, 2025) and location (Humphrey Street) of the theft, to identify the initial pool of witnesses and clues.
7. Followed leads from the crime scene report into the `interviews` table, reading witness statements for details such as approximate times, vehicle descriptions, or mentions of phone calls and travel plans.
8. Cross-referenced timing and location clues from witness interviews against the `phone_calls` table to identify short, suspicious calls made around the time of the theft.
9. Investigated the `bank_accounts`, `atm_transactions`, and related financial tables to look for suspicious withdrawals or transactions around the time of the crime that might corroborate a suspect's movements.
10. Queried the `flights`, `airports`, and `passengers` tables to identify flights departing shortly after the theft, cross-referencing passenger names against the pool of suspects identified from earlier clues.
11. Iteratively narrowed down the list of suspects by combining evidence from multiple sources (interviews, phone records, financial records, and flight manifests) until a single consistent narrative emerged identifying the thief, their destination city, and their accomplice.
12. Logged every query executed during the investigation into `log.sql`, preceding each with a comment explaining its purpose and what it was intended to reveal, so the file served as a complete, readable record of the investigative process.
13. Completed `answers.txt` with the name of the thief, the city they escaped to, and the name of their accomplice, without modifying any of the file's existing structure.
14. Checked the correctness of the final answers using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/fiftyville
    ```
15. Submitted the completed solution (both `log.sql` and `answers.txt`) using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/fiftyville
    ```

## 📝 Investigative Approach

Since this problem has no single "correct" set of queries — every clue had to be uncovered through iterative exploration rather than following a fixed specification — the investigation followed a general pattern of narrowing down from broad to specific:

1. **Anchor the investigation in a known fact.** The date and location of the crime provided a starting point to filter the `crime_scene_reports` table down to a single relevant report.
2. **Follow every lead from that anchor.** Witness names mentioned in the crime scene report were cross-referenced against the `interviews` table to gather firsthand (and sometimes contradictory or irrelevant) accounts of the event.
3. **Corroborate testimony with hard data.** Details mentioned by witnesses (such as approximate times or a getaway plan) were checked against more objective records like phone logs, bank transactions, and flight passenger lists.
4. **Triangulate across independent sources.** Rather than trusting any single record in isolation, the strongest suspects were those whose names appeared consistently across multiple independent pieces of evidence (e.g., a suspicious phone call, a same-day ATM withdrawal, and a flight booked shortly after the crime).
5. **Eliminate false leads.** Not every witness statement or record was relevant; part of the challenge was recognizing which clues were red herrings and which pointed toward a consistent, internally coherent story.

## 📄 `log.sql` Structure

Each query in `log.sql` was preceded by a comment explaining its purpose, following a pattern similar to the example below:

```sql
-- Find the crime scene report matching the date and location of the theft
SELECT description
FROM crime_scene_reports
WHERE street = "Humphrey Street" AND year = 2025 AND month = 7 AND day = 28;

-- Find interviews given around the time of the theft, to gather witness accounts
SELECT name, transcript
FROM interviews
JOIN people ON interviews.person_id = people.id
WHERE year = 2025 AND month = 7 AND day = 28;

-- (Additional queries follow, each investigating a new lead
--  suggested by the results of the previous query.)
```

## 📄 `answers.txt` Structure

The `answers.txt` file was completed in the format below, without altering any of its existing structure:

```
The THIEF is: [name].
The city the thief ESCAPED TO: [city].
The ACCOMPLICE is: [name].
```

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Exploratory Database Investigation** – I learned how to approach an unfamiliar database with no fixed set of questions to answer, instead using `.tables` and `.schema` to build up an understanding of the data model piece by piece as the investigation unfolded.
- **Iterative Query Refinement** – I practiced using the results of one query to directly shape the next, a fundamentally different workflow from earlier SQL problem sets where each query answered a single, independent, pre-defined question.
- **Cross-Referencing Disparate Data Sources** – I gained experience combining information from tables that, on the surface, seemed unrelated (crime reports, phone logs, financial transactions, and flight records), and learned how real investigative and analytical work often requires synthesizing evidence from multiple independent sources rather than relying on any single dataset.
- **Distinguishing Signal from Noise** – I practiced critically evaluating witness statements and records to separate genuinely relevant clues from irrelevant details or red herrings, an important skill in any data analysis context involving messy, real-world-style data.
- **Documenting an Investigative Process** – I learned the value of maintaining a clear, well-commented log of every query executed and the reasoning behind it, both to keep my own thinking organized and to produce a transparent, auditable record of how a conclusion was reached.
- **Applying SQL to Open-Ended Problems** – I deepened my practical SQL skills (filtering, joining, and nesting subqueries) by applying them to a genuinely open-ended problem, rather than a problem with a single specified query and expected output, reinforcing how the same technical tools can be applied flexibly to very different kinds of problems.
- **Testing and Code Verification** – I practiced using CS50's `check50` tool to automatically verify the correctness of my final conclusions.
- **Submitting Work** – I learned how to properly submit a completed assignment consisting of both an investigative query log (`log.sql`) and a final set of conclusions (`answers.txt`) using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 7: Fiftyville](https://cs50.harvard.edu/x/psets/7/fiftyville/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
