# CS50X – Problem Set 7: Songs

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. It marks the introduction of **SQL** in the course. The goal was to write eight individual SQL queries against a provided SQLite database (`songs.db`) containing data on the 100 most-streamed songs on Spotify in 2018, answering a range of questions about the dataset — from simple listings to filtered, sorted, aggregated, and joined queries — and to reflect in writing on how similar data might be used to characterize a Spotify listener's "Audio Aura."

## 🎯 Objective

The main objectives of this task were to get familiar with:
- exploring a relational database's structure using SQLite's `.schema` command,
- writing basic `SELECT` queries to retrieve specific columns from a table,
- sorting query results using `ORDER BY`, in both ascending and descending order,
- limiting the number of rows returned using `LIMIT`,
- filtering rows using `WHERE` clauses with comparison operators and logical operators (`AND`, `OR`),
- computing aggregate values (such as averages) using SQL aggregate functions like `AVG`,
- relating data across multiple tables using both **nested subqueries** and **`JOIN`** clauses,
- performing pattern matching on text data using `LIKE` and the `%` wildcard,
- reflecting critically on how a data-driven metric (an "Audio Aura") might be calculated and where such an approach could fall short of accurately representing a person,
- the tools provided by CS50 for verifying the correctness (`check50`) of the written queries, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/7/songs.zip
   ```
2. Extracted the downloaded archive to create a folder called `songs`:
   ```bash
   unzip songs.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm songs.zip
   ```
4. Navigated into the `songs` folder:
   ```bash
   cd songs
   ```
5. Opened the provided database in an interactive SQLite session and inspected its structure using `.schema`, to understand the columns available in the `songs` and `artists` tables:
   ```bash
   sqlite3 songs.db
   ```
6. Wrote `1.sql`, a query to list the names of all songs in the database.
7. Wrote `2.sql`, a query to list the names of all songs sorted in increasing order of tempo, using `ORDER BY`.
8. Wrote `3.sql`, a query to list the names of the top 5 longest songs in descending order of duration, combining `ORDER BY ... DESC` with `LIMIT`.
9. Wrote `4.sql`, a query to list the names of songs with danceability, energy, and valence all greater than `0.75`, using a compound `WHERE` clause with `AND`.
10. Wrote `5.sql`, a query to compute the average energy across all songs using the `AVG` aggregate function.
11. Wrote `6.sql`, a query to list the names of songs by Post Malone, using a nested subquery to look up the artist's `id` by name rather than hardcoding it.
12. Wrote `7.sql`, a query to compute the average energy of songs by Drake, using a `JOIN` between the `songs` and `artists` tables.
13. Wrote `8.sql`, a query to list the names of songs featuring other artists, using `LIKE` with the `%feat.%` pattern.
14. Tested each query directly in the SQLite prompt to confirm the returned results matched what each question asked for, checking column count and row content against the specification.
15. Reflected on how a Spotify-style "Audio Aura" might be calculated from average energy, valence, and danceability, and on the limitations of that approach, recording these thoughts in `answers.txt`.
16. Checked the correctness of all queries using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/songs
    ```
17. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/songs
    ```

## 💻 Query Code

```sql
-- 1. List the names of all songs in the database.
SELECT name
FROM songs;
```

```sql
-- 2. List the names of all songs in increasing order of tempo.
SELECT name
FROM songs
ORDER BY tempo;
```

```sql
-- 3. List the names of the top 5 longest songs, in descending order of length.
SELECT name
FROM songs
ORDER BY duration_ms DESC
LIMIT 5;
```

```sql
-- 4. List the names of any songs that have danceability, energy, and valence greater than 0.75.
SELECT name
FROM songs
WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;
```

```sql
-- 5.sql: The average energy of all the songs.
SELECT AVG(energy)
FROM songs;
```

```sql
-- 6. List the names of songs that are by Post Malone (no assumption about artist_id).
SELECT name
FROM songs
WHERE artist_id = (
    SELECT id
    FROM artists
    WHERE name = "Post Malone"
);
```

```sql
-- 7. Return the average energy of songs that are by Drake (no assumption about artist_id).
SELECT AVG(energy)
FROM songs
JOIN artists ON songs.artist_id = artists.id
WHERE artists.name = "Drake";
```

```sql
-- 8. List the names of the songs that feature other artists (contain "feat.").
SELECT name
FROM songs
WHERE name LIKE "%feat.%";
```

## 📤 Expected Output

Each `.sql` file, when run against `songs.db`, returns a table with only the columns and rows relevant to its specific question. For example, running the query in `6.sql` returns a single column listing every song by Post Malone in the database, while `5.sql` returns a single value representing the average energy across all 100 songs.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Exploring Database Structure** – I learned how to use SQLite's `.schema` command to inspect a database's tables and columns before writing any queries, a foundational first step when working with unfamiliar data.
- **Basic Data Retrieval** – I practiced writing simple `SELECT ... FROM` queries to retrieve only the specific columns needed to answer a question, rather than selecting entire rows unnecessarily.
- **Sorting and Limiting Results** – I learned how to combine `ORDER BY` (in both ascending and descending order) with `LIMIT` to retrieve a specific, ranked subset of rows, such as the top 5 longest songs.
- **Filtering with Compound Conditions** – I practiced writing `WHERE` clauses combining multiple conditions with `AND`, reinforcing how SQL's comparison and logical operators parallel those used in earlier problem sets' C and Python code.
- **Aggregate Functions** – I learned how to use `AVG` to compute a single summary statistic across many rows, and understood how aggregate functions differ conceptually from row-by-row filtering.
- **Relating Data Across Tables** – I gained hands-on experience with two different techniques for combining data from related tables: nested subqueries (looking up an artist's `id` before filtering songs by it) and explicit `JOIN` clauses (combining `songs` and `artists` into a single result set), and considered the trade-offs between the two approaches.
- **Avoiding Hardcoded Assumptions** – I practiced writing queries that did not assume or hardcode any particular artist's `id`, ensuring the queries would remain correct even if the underlying data changed, a good habit for writing robust, reusable SQL.
- **Pattern Matching with `LIKE`** – I learned how to use the `LIKE` keyword together with the `%` wildcard to match rows containing a specific substring (`feat.`) anywhere within a text column.
- **Critical Reflection on Data-Driven Metrics** – I practiced thinking critically about how a real-world product feature (Spotify Wrapped's "Audio Aura") might be computed from raw data, and considered the ways a simple average across a few numeric fields might fail to meaningfully capture something as complex and personal as a listener's mood or music taste.
- **Testing and Code Verification** – I practiced using CS50's `check50` tool to automatically verify the correctness of each of my SQL queries.
- **Submitting Work** – I learned how to properly submit a completed assignment, including multiple `.sql` files and a written reflection, using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 7: Songs](https://cs50.harvard.edu/x/psets/7/songs/).

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
