\timing

DROP FUNCTION IF EXISTS duree_intervalle(INTEGER) ;
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


DROP FUNCTION IF EXISTS parcours() ;
CREATE FUNCTION  parcours() returns integer AS $$
DECLARE
    id calendar.service_id%TYPE;
    n integer;
    c integer:=0;
BEGIN
    FOR id  IN
        SELECT service_id 
          FROM calendar
    LOOP 
        --#RAISE NOTICE 'id is %',id;
        select count(*) 
          INTO n
          from calendar_dates where service_id=id;
        IF duree_intervalle(id) < n THEN 
          c:=c+1;
        END IF;
    END LOOP;
    return c;
END;
$$ LANGUAGE plpgsql;


SELECT parcours();

SELECT C.service_id, duree_intervalle(C.service_id) as DI , count(*) as NB
  FROM calendar C, calendar_dates CD
 WHERE C.service_id= CD.service_id
 GROUP BY C.service_id
HAVING duree_intervalle(C.service_id) < count(*);
