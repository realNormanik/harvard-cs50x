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
