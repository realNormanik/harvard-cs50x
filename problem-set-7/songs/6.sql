-- 6. List the names of songs that are by Post Malone (no assumption about artist_id).
SELECT name
FROM songs
WHERE artist_id = (
    SELECT id
    FROM artists
    WHERE name = "Post Malone"
);
