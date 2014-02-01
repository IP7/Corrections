create or replace function ex1(id ratp.stop_times.trip_id%type, n integer) returns table(sequence integer) as $$
declare
	s integer;
	time ratp.stop_times.departure_time%type;
	fin integer;
begin
s := 1;
select max(stop_sequence) into fin from stop_times where id = trip_id;
while (s < fin) loop
	select departure_time into time from stop_times where s = stop_sequence and id = trip_id;
	select max(stop_sequence) into s from stop_times where (id = trip_id) and ((to_timestamp(departure_time,'HH24:MI:SS') - to_timestamp(time ,'HH24:MI:SS')) < n * interval '1 minutes');
	sequence := s;
	return next;
end loop;
end;

$$ LANGUAGE plpgsql;


CREATE FUNCTION  duree_intervalle(id calendar.service_id%TYPE) returns integer AS $$
DECLARE
   debut DATE;
   fin DATE ;
BEGIN
   select to_date(to_char(start_date,'99999999'),'YYYYMMDD') 
     INTO debut
     FROM calendar 
     WHERE service_id=id;

   select to_date(to_char(end_date,'99999999'),'YYYYMMDD') 
     INTO fin 
     FROM calendar 
     WHERE service_id=id;
   RETURN (fin-debut+1);
END;
$$ LANGUAGE plpgsql;


create or replace function ex2() returns void as $$
declare
	debut DATE;
   	fin DATE ;
	temp Date;
	id record;
begin
	for id in 
		select service_id from calendar
	loop
	select to_date(to_char(start_date,'99999999'),'YYYYMMDD'),to_date(to_char(end_date,'99999999'),'YYYYMMDD') 
	     INTO debut,fin
		     FROM calendar 
			     WHERE service_id=id.service_id;
	select date into temp from calendar_dates where service_id = id.service_id and ((to_date(to_char(date,'99999999'),'YYYYMMDD') - debut) < 0 or
		(to_date(to_char(date,'99999999'),'YYYYMMDD') - fin) > 0);
	if temp is not null
		then raise notice 'erreur : %', id.service_id;
	end if;
	end loop;
end;
$$ LANGUAGE plpgsql;


create or replace function ex4(debut date, fin date) returns integer as $$
declare
	i integer;
begin
	select count(*) into i from calendar_dates where ((to_date(to_char(date,'99999999'),'YYYYMMDD') - debut) >= 0 or
		(to_date(to_char(date,'99999999'),'YYYYMMDD'))  0)
end;
$$ LANGUAGE plpgsql;


