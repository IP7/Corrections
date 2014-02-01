/* Exercice 3 */

A : trips , trips_1 , trips_2

trips : btree sur la clé primaire (trip_id)
trips_1 : pas d'index puisqu'il n'y a pas de clé primaire
trips_2 : btree sur la clé primaire (trip_id)
          btree sur l'expression (trip_id + 0)

B : stop_times , stop_times1 , stop_times2

stop_times : btree sur les clées primaires (trip_id , stop_id)
stop_times_1 : pas d'index puisqu'il n'y a pas de clé primaire
stop_times_2 : btree sur les clées primaires (trip_id , stop_id)
               btree sur l'expression (trip_id + 0)
