Select name from people where people.id in
(select person_id from stars where stars.movie_id in
(select movie_id from stars where stars.person_id in
(select id from people where people.name = "Kevin Bacon" and people.birth = 1958)))