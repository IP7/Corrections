/* Requête */

EXPLAIN
SELECT COUNT(*)
  FROM ratp.calendar,ratp.routes,ratp.trips,ratp.stop_times,ratp.stops
WHERE trips.trip_id = stop_times.trip_id
  AND trips.service_id = calendar.service_id
  AND trips.route_id = routes.route_id
  AND stop_times.stop_id = stops.stop_id
  AND trips.trip_id = 100872820081804;


/* Commentaire */


                                           QUERY PLAN (Requête précédente)                                           
-------------------------------------------------------------------------------------------------
 Aggregate  (cost=996290.74..996290.75 rows=1 width=0)
   ->  Hash Join  (cost=39754.54..960889.95 rows=14160316 width=0)
         Hash Cond: (stop_times.trip_id = trips.trip_id)
         ->  Hash Join  (cost=992.36..561505.23 rows=14160316 width=8)
               Hash Cond: (stop_times.stop_id = stops.stop_id)
               ->  Seq Scan on stop_times  (cost=0.00..259606.16 rows=14160316 width=12)
               ->  Hash  (cost=644.38..644.38 rows=27838 width=4)
                     ->  Seq Scan on stops  (cost=0.00..644.38 rows=27838 width=4)
         ->  Hash  (cost=29569.53..29569.53 rows=560292 width=8)
               ->  Hash Join  (cost=236.40..29569.53 rows=560292 width=8)
                     Hash Cond: (trips.route_id = routes.route_id)
                     ->  Hash Join  (cost=194.35..21823.48 rows=560292 width=12)
                           Hash Cond: (trips.service_id = calendar.service_id)
                           ->  Seq Scan on trips  (cost=0.00..9722.92 rows=560292 width=16)
                           ->  Hash  (cost=107.49..107.49 rows=6949 width=4)
                                 ->  Seq Scan on calendar  (cost=0.00..107.49 rows=6949 width=4)
                     ->  Hash  (cost=28.13..28.13 rows=1113 width=4)
                           ->  Seq Scan on routes  (cost=0.00..28.13 rows=1113 width=4)
(18 rows)


                                  QUERY PLAN (Requête avec les nouvelles conditions)                                                 
--------------------------------------------------------------------------------------------------------------
 Aggregate  (cost=1178.25..1178.26 rows=1 width=0)
   ->  Nested Loop  (cost=1.83..1178.00 rows=100 width=0)
         ->  Nested Loop  (cost=0.99..25.06 rows=1 width=8)
               ->  Nested Loop  (cost=0.71..16.76 rows=1 width=12)
                     ->  Index Scan using trips_pkey on trips  (cost=0.42..8.44 rows=1 width=16)
                           Index Cond: (trip_id = 100872820081804::bigint)
                     ->  Index Only Scan using calendar_pkey on calendar  (cost=0.28..8.30 rows=1 width=4)
                           Index Cond: (service_id = trips.service_id)
               ->  Index Only Scan using routes_pkey on routes  (cost=0.28..8.30 rows=1 width=4)
                     Index Cond: (route_id = trips.route_id)
         ->  Nested Loop  (cost=0.85..1151.94 rows=100 width=8)
               ->  Index Only Scan using stop_times_pkey on stop_times  (cost=0.56..400.19 rows=100 width=12)
                     Index Cond: (trip_id = 100872820081804::bigint)
               ->  Index Only Scan using stops_pkey on stops  (cost=0.29..7.51 rows=1 width=4)
                     Index Cond: (stop_id = stop_times.stop_id)
(15 rows)


Ce qui change c'est la manière de procédé. Il utilise un "Netsed Loop" à la place d'un "Hash Join".
La requête va utilisé l'index dans le deuxième cas puisqu'on souhaite une seule ligne.


/* Requêtes : (trips_1, stop_times) */


EXPLAIN
SELECT COUNT(*)
  FROM ratp.calendar,ratp.routes,ratp.trips_1,ratp.stop_times,ratp.stops
WHERE trips_1.trip_id = stop_times.trip_id
  AND trips_1.service_id = calendar.service_id
  AND trips_1.route_id = routes.route_id
  AND stop_times.stop_id = stops.stop_id
  AND trips_1.trip_id = 100872820081804;

                                                  QUERY PLAN                                                  
--------------------------------------------------------------------------------------------------------------
 Aggregate  (cost=11776.20..11776.21 rows=1 width=0)
   ->  Nested Loop  (cost=1.13..11775.95 rows=100 width=0)
         ->  Nested Loop  (cost=0.28..10623.01 rows=1 width=8)
               Join Filter: (trips_1.route_id = routes.route_id)
               ->  Nested Loop  (cost=0.28..10580.96 rows=1 width=12)
                     ->  Seq Scan on trips_1  (cost=0.00..10572.65 rows=1 width=16)
                           Filter: (trip_id = 100872820081804::bigint)
                     ->  Index Only Scan using calendar_pkey on calendar  (cost=0.28..8.30 rows=1 width=4)
                           Index Cond: (service_id = trips_1.service_id)
               ->  Seq Scan on routes  (cost=0.00..28.13 rows=1113 width=4)
         ->  Nested Loop  (cost=0.85..1151.94 rows=100 width=8)
               ->  Index Only Scan using stop_times_pkey on stop_times  (cost=0.56..400.19 rows=100 width=12)
                     Index Cond: (trip_id = 100872820081804::bigint)
               ->  Index Only Scan using stops_pkey on stops  (cost=0.29..7.51 rows=1 width=4)
                     Index Cond: (stop_id = stop_times.stop_id)
(15 rows)

Time: 3.581 ms


/* Requête : (trips, stops_times_1) */

EXPLAIN
SELECT COUNT(*)
  FROM ratp.calendar,ratp.routes,ratp.trips,ratp.stop_times_1,ratp.stops
WHERE trips.trip_id = stop_times_1.trip_id
  AND trips.service_id = calendar.service_id
  AND trips.route_id = routes.route_id
  AND stop_times_1.stop_id = stops.stop_id
  AND trips.trip_id = 100872820081804;

                                                      QUERY PLAN                                                       
-----------------------------------------------------------------------------------------------------------------------
 Aggregate  (cost=297475.14..297475.15 rows=1 width=0)
   ->  Nested Loop  (cost=0.99..297474.89 rows=100 width=0)
         ->  Nested Loop  (cost=0.71..296723.14 rows=100 width=4)
               Join Filter: (trips.route_id = routes.route_id)
               ->  Seq Scan on routes  (cost=0.00..28.13 rows=1113 width=4)
               ->  Materialize  (cost=0.71..295025.76 rows=100 width=8)
                     ->  Nested Loop  (cost=0.71..295025.26 rows=100 width=8)
                           ->  Nested Loop  (cost=0.71..16.76 rows=1 width=12)
                                 ->  Index Scan using trips_pkey on trips  (cost=0.42..8.44 rows=1 width=16)
                                       Index Cond: (trip_id = 100872820081804::bigint)
                                 ->  Index Only Scan using calendar_pkey on calendar  (cost=0.28..8.30 rows=1 width=4)
                                       Index Cond: (service_id = trips.service_id)
                           ->  Seq Scan on stop_times_1  (cost=0.00..295007.50 rows=100 width=12)
                                 Filter: (trip_id = 100872820081804::bigint)
         ->  Index Only Scan using stops_pkey on stops  (cost=0.29..7.51 rows=1 width=4)
               Index Cond: (stop_id = stop_times_1.stop_id)
(16 rows)

Time: 3.260 ms


/* Requête : (trips_1, stop_times_1)*/

EXPLAIN
SELECT COUNT(*)
  FROM ratp.calendar,ratp.routes,ratp.trips_1,ratp.stop_times_1,ratp.stops
WHERE trips_1.trip_id = stop_times_1.trip_id
  AND trips_1.service_id = calendar.service_id
  AND trips_1.route_id = routes.route_id
  AND stop_times_1.stop_id = stops.stop_id
  AND trips_1.trip_id = 100872820081804;

                                                   QUERY PLAN                                                    
-----------------------------------------------------------------------------------------------------------------
 Aggregate  (cost=306383.51..306383.52 rows=1 width=0)
   ->  Nested Loop  (cost=0.57..306383.26 rows=100 width=0)
         ->  Nested Loop  (cost=0.28..305631.50 rows=100 width=4)
               ->  Nested Loop  (cost=0.28..10623.01 rows=1 width=8)
                     Join Filter: (trips_1.route_id = routes.route_id)
                     ->  Nested Loop  (cost=0.28..10580.96 rows=1 width=12)
                           ->  Seq Scan on trips_1  (cost=0.00..10572.65 rows=1 width=16)
                                 Filter: (trip_id = 100872820081804::bigint)
                           ->  Index Only Scan using calendar_pkey on calendar  (cost=0.28..8.30 rows=1 width=4)
                                 Index Cond: (service_id = trips_1.service_id)
                     ->  Seq Scan on routes  (cost=0.00..28.13 rows=1113 width=4)
               ->  Seq Scan on stop_times_1  (cost=0.00..295007.50 rows=100 width=12)
                     Filter: (trip_id = 100872820081804::bigint)
         ->  Index Only Scan using stops_pkey on stops  (cost=0.29..7.51 rows=1 width=4)
               Index Cond: (stop_id = stop_times_1.stop_id)
(15 rows)

Time: 2.895 ms

/* Commentaire */

Lorsqu'on utilise des index on va obenir un meilleur temps d'éxécution.
