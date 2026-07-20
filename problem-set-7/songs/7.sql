-- 7. Return the average energy of songs that are by Drake (no assumption about artist_id).
SELECT AVG(energy)
FROM songs
JOIN artists ON songs.artist_id = artists.id
WHERE artists.name = "Drake";
