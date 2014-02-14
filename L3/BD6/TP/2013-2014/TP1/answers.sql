/* Question 1 */
SELECT *
  FROM produit;

SELECT *
  FROM usine;

SELECT *
  FROM masasin;

SELECT *
  FROM provenance;


/* Question 2 */
SELECT ville
  FROM usine;


/* Question 3 */
SELECT nom_prod, couleur
  FROM produit;


/* Question 4 */
SELECT ref_prod, quantite
  FROM provenance
 WHERE ref_mag = 14;


/* Question 5 */
SELECT *
  FROM usine
 WHERE ville LIKE 'Marseille';


/* Question 6 */
SELECT ref_mag
  FROM provenance
 WHERE ref_usine = 109
   AND ref_prod  = 1;


/* Question 7 */
SELECT ref_prod, nom_prod
  FROM produit
 WHERE couleur LIKE 'rouge';


/* Question 8 */
SELECT ref_prod, nom_prod
  FROM produit
 WHERE nom_prod LIKE 'casse%';

/* Question 9 */
SELECT ref_mag
  FROM provenance; /* Avec doublons */

SELECT DISTINCT ref_mag
  FROM provenance; /* Sans doublons */


/* Question 10 */
SELECT nom_prod
  FROM produit
 WHERE poids BETWEEN 15 AND 45;

/* Question 11 */
SELECT nom_prod
  FROM produit
 WHERE couleur IN ('bleu', 'jaune')
   AND poids < 20;


/* Question 12 */
SELECT nom_prod
  FROM produit
 WHERE couleur LIKE 'jaune'
    OR (
        couleur LIKE 'rouge'
    and poids < 20
       );


/* Question 13 */
SELECT nom_prod
  FROM produit
 WHERE (nom_prod LIKE 'lampe%')
    OR poids < 30;


/* Question 14 */
SELECT ref_mag
  FROM magasin
EXCEPT
SELECT ref_mag
  FROM provenance;


/* Question 15 */
SELECT ville
  FROM usine
 UNION
SELECT ville
  FROM magasin;


/* Question 16 */
   SELECT ville
     FROM usine
INTERSECT
   SELECT ville
     FROM magasin;


/* Question 17 */
SELECT ville
  FROM magasin
EXCEPT
SELECT ville
  FROM usine;



/*
 * Questions supplémentaires.
 */


/* Afficher les objets par ordre décroissant */
SELECT *
  FROM produit
 ORDER BY poids DESC;
/* Afficher les objets par ordre croissant   */
SELECT *
  FROM produit
 ORDER BY poids;


/* Afficher les cinq objets les plus légers  */
SELECT *
  FROM produit
 ORDER BY poids LIMIT 5;


/* Afficher le poids en gramme et le nom des objets par ordre croissant */
SELECT nom_mag, poids * 1000 AS poids_gramme
  FROM produit
 ORDER BY poids;


/* Afficher les villes qui ont plusieurs magasins */
SELECT ville
  FROM magasin
 GROUP BY ville
HAVING COUNT(ville);


/* Afficher le nombre de produit de poids < 50 */
SELECT COUNT(*)
  FROM produit
 WHERE poids < 50;


/* Afficher produit violet ou livrés au magasin 16 */
SELECT nom_prod
  FROM produit, provenance
 WHERE produit.ref_prod = provenance.ref_prod
   AND couleur LIKE 'violet'
   AND ref_mag          = 16;
