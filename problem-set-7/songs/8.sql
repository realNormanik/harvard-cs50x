-- 8. List the names of the songs that feature other artists (contain "feat.").
SELECT name
FROM songs
WHERE name LIKE "%feat.%";
