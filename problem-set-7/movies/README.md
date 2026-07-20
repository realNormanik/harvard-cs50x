# CS50X – Problem Set 7: Movies

## 📋 Task Description

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course offered by Harvard University. The goal was to write thirteen individual SQL queries against a provided SQLite database (`movies.db`) containing real IMDb data on movies, the people who directed and starred in them, and their ratings. The queries range from simple filtering and sorting to more advanced aggregation, multi-table joins, and deeply nested subqueries, ultimately answering increasingly complex questions such as identifying every actor who has appeared in a movie alongside a specific person (a "Six Degrees of Kevin Bacon"–style query).

## 🎯 Objective

The main objectives of this task were to get familiar with:
- exploring a multi-table relational database's schema using SQLite's `.schema` command, including understanding foreign key relationships between tables,
- writing `SELECT` queries with `WHERE` clauses using a variety of comparison operators (`=`, `>=`, `LIKE`),
- sorting results with `ORDER BY` (ascending, descending, and alphabetically), and limiting results with `LIMIT`,
- using aggregate functions (`COUNT`, `AVG`) to summarize data across many rows,
- combining data from multiple related tables using both `JOIN` clauses and deeply **nested subqueries**,
- using `IN` to check whether a column's value exists within the result set of a subquery,
- carefully avoiding duplicate results when a person could otherwise appear in a result set more than once (e.g., due to starring in multiple qualifying movies),
- handling ambiguous data, such as multiple people sharing the same name, by filtering on additional distinguishing attributes (e.g., birth year),
- the tools provided by CS50 for verifying the correctness (`check50`) of the written queries, as well as submitting the solution (`submit50`).

## 🛠️ Steps Taken

1. Downloaded the distribution code from CS50's servers using the command:
   ```bash
   wget https://cdn.cs50.net/2026/x/psets/7/movies.zip
   ```
2. Extracted the downloaded archive to create a folder called `movies`:
   ```bash
   unzip movies.zip
   ```
3. Removed the now-unnecessary ZIP file:
   ```bash
   rm movies.zip
   ```
4. Navigated into the `movies` folder:
   ```bash
   cd movies
   ```
5. Opened the provided database in an interactive SQLite session and inspected its structure using `.schema`, to understand the `movies`, `people`, `ratings`, `stars`, and `directors` tables and how they relate to one another via foreign keys:
   ```bash
   sqlite3 movies.db
   ```
6. Wrote `1.sql` through `4.sql`, covering basic filtering (movies released in 2008), string-based filtering (Emma Stone's birth year), range filtering with alphabetical sorting (movies from 2018 onward), and aggregation with `COUNT` (movies rated exactly 10.0).
7. Wrote `5.sql`, using `LIKE` with the `%` wildcard to identify all Harry Potter movies by their shared title prefix, sorted chronologically.
8. Wrote `6.sql` and `7.sql`, using `AVG` and a `JOIN` between `movies` and `ratings` to compute an average rating and to list movies with their ratings sorted in descending order (with a secondary alphabetical sort for ties).
9. Wrote `8.sql`, using a nested subquery to first find Toy Story's `id` in the `movies` table, then find matching `person_id` values in the `stars` table, and finally match those against the `people` table using `IN`.
10. Wrote `9.sql`, nesting subqueries across `movies`, `stars`, and `people` to find the ID and name of every person who starred in a movie released in 2004, ordered by birth year, taking care to avoid duplicate entries for people who starred in multiple 2004 movies.
11. Wrote `10.sql`, using nested subqueries across `ratings`, `directors`, and `people` to find the names of directors of movies rated at least 9.0, ensuring each director appeared only once even if they directed multiple qualifying movies.
12. Wrote `11.sql`, chaining subqueries to find Chadwick Boseman's movies, joining with `ratings`, sorting by rating in descending order, and using `LIMIT 5` to retrieve his five highest-rated movies.
13. Wrote `12.sql`, using two separate subqueries (one for each actor's movie IDs) combined with `INTERSECT` to find movies in which both Bradley Cooper and Jennifer Lawrence starred.
14. Wrote `13.sql`, the most complex query, finding the specific Kevin Bacon born in 1958, identifying his movies, finding every other person who starred in those same movies, and explicitly excluding Kevin Bacon himself from the final results.
15. Tested each query using the command-line pattern:
    ```bash
    cat 1.sql | sqlite3 movies.db
    ```
16. Verified the exact expected row and column counts for each query against the specification (e.g., confirming `1.sql` returned 10,647 rows, `5.sql` returned 18 rows, `13.sql` returned 550 rows), redirecting output to text files where useful for counting:
    ```bash
    cat 3.sql | sqlite3 movies.db > output.txt
    ```
17. Checked the correctness of all queries using the `check50` tool:
    ```bash
    check50 cs50/problems/2026/x/movies
    ```
18. Submitted the completed solution using the `submit50` tool:
    ```bash
    submit50 cs50/problems/2026/x/movies
    ```

## 💻 Query Code

```sql
-- 1. Titles of all movies from 2008
SELECT title
FROM movies
WHERE year = 2008;
```

```sql
-- 2. Birth year of Emma Stone
SELECT birth
FROM people
WHERE name = "Emma Stone";
```

```sql
-- 3. Titles of all movies since 2018, in alphabetical order
SELECT title
FROM movies
WHERE year >= 2018
ORDER BY title;
```

```sql
-- 4. Number of movies with a 10.0 rating
SELECT COUNT(*)
FROM ratings
WHERE rating = 10.0;
```

```sql
-- 5. Titles and years of all Harry Potter movies, in chronological order (title beginning with "Harry Potter and the ...")
SELECT title, year
FROM movies
WHERE title LIKE "Harry Potter%"
ORDER BY year;
```

```sql
-- 6. Average rating of movies in 2012
SELECT AVG(rating)
FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE movies.year = 2012;
```

```sql
-- 7. All movies and ratings from 2010, in decreasing order by rating (alphabetical for those with same rating)
SELECT title, rating
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE movies.year = 2010
ORDER BY rating DESC, title;
```

```sql
-- 8. Names of people who starred in Toy Story
SELECT name
FROM people
WHERE id IN
(
    SELECT person_id
    FROM stars
    WHERE movie_id = (
        SELECT id
        FROM movies
        WHERE title = "Toy Story"
    )
);
```

```sql
-- 9. Names of all people who starred in a movie released in 2004, ordered by birth year
SELECT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.year = 2004
ORDER BY people.birth
```

```sql
-- 10. Names of all directors who have directed a movie that got a rating of at least 9.0
SELECT DISTINCT p.name
FROM people p
JOIN directors d ON p.id = d.person_id
JOIN ratings r ON d.movie_id = r.movie_id
WHERE r.rating >= 9.0;
```

```sql
-- 11. Titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated
SELECT m.title
FROM movies m
JOIN stars s ON m.id = s.movie_id
JOIN people p ON s.person_id = p.id
JOIN ratings r ON m.id = r.movie_id
WHERE p.name = "Chadwick Boseman"
ORDER BY r.rating DESC
LIMIT 5;
```

```sql
-- 12. Titles of all of movies in which both Jennifer Lawrence and Bradley Cooper starred
SELECT m.title
FROM movies m
WHERE m.id IN (
    SELECT s1.movie_id
    FROM stars s1
    JOIN people p1 ON s1.person_id = p1.id
    WHERE p1.name = "Bradley Cooper"
)
AND m.id IN (
    SELECT s2.movie_id
    FROM stars s2
    JOIN people p2 ON s2.person_id = p2.id
    WHERE p2.name = "Jennifer Lawrence"
);
```

```sql
-- 13. Names of all people who starred in a movie in which Kevin Bacon also starred
SELECT distinct(name) FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title IN(
SELECT distinct(movies.title) FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name = "Kevin Bacon" AND people.birth = 1958) AND people.name != "Kevin Bacon";
```

## 📤 Expected Output

Each `.sql` file, when run against `movies.db`, returns a table matching the exact row and column counts specified for that query. For example, `5.sql` returns a two-column table (title and year) listing the 18 Harry Potter movies in chronological order, while `13.sql` returns a single column of 550 distinct names of people who co-starred with the specific Kevin Bacon born in 1958, excluding Kevin Bacon himself.

## 📚 What I Learned

By completing this task, I gained the following knowledge and skills:

- **Working with a Larger, Multi-Table Schema** – I gained experience navigating a more realistic relational database with five interrelated tables (`movies`, `people`, `ratings`, `stars`, `directors`), reinforcing the importance of understanding foreign key relationships before attempting to write queries that span multiple tables.
- **Progressive Query Complexity** – I practiced building up from simple, single-table queries to deeply nested, multi-level subqueries, learning to decompose a complex natural-language question ("who starred in a movie with Kevin Bacon?") into a sequence of smaller, answerable sub-questions before combining them into a single query.
- **Nested Subqueries vs. Joins** – I gained practical experience choosing between nested subqueries and `JOIN` clauses depending on the shape of the question being asked, and understood how both techniques can often solve the same underlying problem with different readability and structure trade-offs.
- **Using `IN` with Subquery Results** – I learned how to use the `IN` operator to filter rows based on membership in a set of values returned by a subquery, a pattern that proved essential for nearly every multi-table query in this problem set.
- **Set Operations with `INTERSECT`** – I learned how to use SQL's `INTERSECT` keyword to find the common elements between two separate query results, which provided an elegant way to identify movies shared between two specific actors' filmographies.
- **Avoiding Duplicate Results** – I practiced using `DISTINCT` to ensure that a person appearing in multiple qualifying rows (e.g., starring in several movies from the same year, or directing multiple highly rated films) was only listed once in the final results.
- **Disambiguating Similarly Named Records** – I learned the importance of filtering on additional attributes (such as birth year) when a name alone is not sufficient to uniquely identify a record, as was necessary to correctly identify the specific Kevin Bacon referenced in the final query.
- **Precise Query Verification** – I practiced verifying my queries not just by inspecting the returned rows visually, but by checking exact expected row and column counts against the specification, which helped catch subtle bugs like unintended duplicates or missing filters.
- **Testing and Code Verification** – I practiced using CS50's `check50` tool to automatically verify the correctness of each of my SQL queries.
- **Submitting Work** – I learned how to properly submit a completed assignment consisting of multiple `.sql` files using the `submit50` tool.

## 🔗 Task Source

This task is part of the [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/) course, Harvard University – [Problem Set 7: Movies](https://cs50.harvard.edu/x/psets/7/movies/). Movie data courtesy of IMDb (imdb.com), used with permission.

---

*This project is part of my learning journey through the basics of programming as part of the CS50 course.*
