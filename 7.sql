SELECT DISTINCT title, rating FROM
people JOIN stars ON people.id = stars.person_id JOIN
movies ON stars.movie_id = movies.id JOIN
ratings ON stars.movie_id = ratings.movie_id 
WHERE year = 2010
ORDER BY rating DESC, title
