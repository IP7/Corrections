/* Requête */

EXPLAIN
SELECT COUNT(*)
  FROM ratp.calendar,ratp.routes,ratp.trips,ratp.stop_times,ratp.stops
WHERE trips.trip_id = stop_times.trip_id+0
  AND trips.service_id = calendar.service_id
  AND trips.route_id = routes.route_id
  AND stop_times.stop_id = stops.stop_id
  AND trips.trip_id+0 = 100872820081804;


/* Temps d'éxécution */

Total runtime: 14181.197 ms


/* Création d'un index */

CREATE INDEX on trips (trips_id+0);


/* Fonction */

CREATE OR REPLACE FUNCTION int_to_date(d INTEGER) RETURNS DATE AS $$
BEGIN
  RETURN to_date(to_char(d,'99999999'),'YYYYMMDD');
END;
$$ LANGUAGE plpgsql IMMUTABLE;


/* Requêtes */

EXPLAIN ANALYZE
SELECT C.service_id,int_to_date(start_date) AS debut, int_to_date(end_date) AS fin, int_to_date(date) AS jour
  FROM ratp.calendar C, ratp.calendar_dates CD
WHERE C.service_id = CD.service_id
  AND int_to_date(CD.date)
  NOT BETWEEN int_to_date(start_date)
  AND int_to_date(end_date);

                                                           QUERY PLAN                                                           
--------------------------------------------------------------------------------------------------------------------------------
 Hash Join  (cost=194.35..202946.48 rows=77239 width=16) (actual time=4693.038..9389.741 rows=3 loops=1)
   Hash Cond: (cd.service_id = c.service_id)
   Join Filter: ((int_to_date(cd.date) < int_to_date(c.start_date)) OR (int_to_date(cd.date) > int_to_date(c.end_date)))
   Rows Removed by Join Filter: 139028
   ->  Seq Scan on calendar_dates cd  (cost=0.00..2142.31 rows=139031 width=8) (actual time=0.049..287.749 rows=139031 loops=1)
   ->  Hash  (cost=107.49..107.49 rows=6949 width=12) (actual time=13.454..13.454 rows=6949 loops=1)
         Buckets: 1024  Batches: 1  Memory Usage: 245kB
         ->  Seq Scan on calendar c  (cost=0.00..107.49 rows=6949 width=12) (actual time=0.057..6.205 rows=6949 loops=1)
 Total runtime: 9389.858 ms
(9 rows)

Time: 9394.232 ms


/* Requêtes */

SELECT C.service_id,int_to_date(start_date) AS debut, to_date(to_char(end_date, ’99999999’), ’YYYYMMDD’) AS fin, to_date(to_char(date, ’99999999’), ’YYYYMMDD’) AS jour
  FROM ratp.calendar C, ratp.calendar_dates CD
WHERE C.service_id = CD.service_id
  AND to_date(to_char(CD.date, ’99999999’), ’YYYYMMDD’)
  NOT BETWEEN to_date(to_char(start_date, ’99999999’), ’YYYYMMDD’)
  AND to_date(to_char(end_date, ’99999999’), ’YYYYMMDD’);


