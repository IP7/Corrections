/* Requête */

EXPLAIN
SELECT COUNT(*)
  FROM ratp.calendar,ratp.routes,ratp.trips,ratp.stop_times,ratp.stops
WHERE trips.trip_id = stop_times.trip_id
  AND trips.service_id = calendar.service_id
  AND trips.route_id = routes.route_id
  AND stop_times.stop_id = stops.stop_id;

/* Arbre */


                                Hash Join
                            -              -
                      -                       -
                 -                              -
           -                                      -
      Hash Join                                  Hash
         -                                          - 
     Hash Join                                  Hash Join
     -      -                                    -       -
   Hash   Seq Scan                            -           -
    -          -                          Hash Join      Hash  
 Seq Scan    Stop_times                     -   -           -
  -                                      -         -      Seq Scan
Stops                                 Hash      Seq Scan       -
                                      -          -              -
                                  Seq Scan     Trips          Routes 
                                      -
                                   Calendar

Ligne par table:

stops : 27 838
stop_times : 14 160 316
calendar : 27 838
trips : 56 292
routes : 1113
