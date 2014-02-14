/* La même base que le TP1 */

/* Question 1 */
SELECT ref_prod, nom_prod, couleur, poids * 2 AS nouveau_poids
  FROM produit
 WHERE couleur LIKE 'rouge';


/* Question 2 */
SELECT *
  FROM provenance
 ORDER BY quantite DESC LIMIT 3;


/* Question 3 */
SELECT *
  FROM produit
 ORDER BY poids;


/* Question 4 */
SELECT nom_usine
  FROM usine, magasin
 WHERE nom_mage LIKE 'JaiTout'
   AND magasin.ville = usine.ville;


/* Question 5 */
SELECT nom_prod, couleur
  FROM produit, provenance
 WHERE ref_usine        = 302
   AND produit.ref_prod = provenance.ref_prod;


/* Question 6 */
SELECT AVG(poids) AS moyenne
  FROM produit;


/* Question 7 */
SELECT COUNT(*)
  FROM magasin, provenance
 WHERE nom_mag LIKE 'PrixBas'
   AND magasin.ref_mag = provenance.ref_mag;


/* Question 8 */
SELECT quantite * poids AS poids_livraisons
  FROM produit, provenance
 WHERE produit.ref_prod = 12
   AND produit.ref_prod = 12
   AND ref_mag          = 30
   AND ref_usine        = 189;


/* Question 9 */
SELECT quantite * poids AS poids_livraisons, produit.ref_prod,
       magasin.ref_mag, usine.ref_usine
  FROM produit, magasin, usine, provenance
 WHERE produit.ref_prod = provenance.ref_prod
   AND magasin.ref_mag  = provenance.ref_mag
   AND usine.ref_usine  = provenance.ref_usine;


/* Question 10 */
SELECT (nom_usine, nom_mag), magasin.ville
  FROM usine, magasin
 WHERE usine.ville = magasin.ville;


/* Question 11 */
SELECT DISTINCT nom_prod
  FROM produit, usine, provenance
 WHERE couleur LIKE 'rouge'
 AND produit.ref_prod = provenance.ref_prod
   AND usine.ref_usine  = provenance.ref_usine;


/* Question 12 */
SELECT (p1.ref_mag, p2.ref_mag)
  FROM provenance AS p1, provenance AS P2
 where p1.ref_mag   < p2.ref_mag
   AND p1.ref_prod  = p2.ref_prod
   AND p1.ref_usine = p2.ref_usine;


/* Question 13 */
SELECT poids
  FROM produit, magasin, provenance
 WHERE magasin.ville    = 'Marseille'
   AND produit.ref_prod = provenance.ref_prod
   AND magasin.ref_mag  = provenance.ref_mag
 ORDER BY poids DESC LIMIT 1;


/* Question 14 */
SELECT nom_mag
  FROM magasin
EXCEPT
SELECT DISTINCT nom_mag
  FROM usine, magasin, provenance
 WHERE nom_usine LIKE 'peugeot'
   AND usine.ref_usine = provenance.ref_usine
   AND magas.ref_mag   = provenance.ref_mag;


/* Question 15 */
SELECT DISTINCT nom_prod
  FROM produit, usine, provenance, magasin
 WHERE nom_prod LIKE 'lampe%'
   AND produit.ref_prod = provenance.ref_prod
   AND nom_usine LIKE 'peugeot'
   AND usine.ref_usine  = provenance.ref_usine
   AND magasin.ville LIKE 'Bordeaux'
   AND magasin.ref_mag  = provenance.ref_mag;


/* Question 16 */
SELECT DISTINCT produit.ref_prod, couleur
  FROM produit, usine, magasin, provenance
 WHERE usine.ville      = magasin.ville
   AND usine.ref_usine  = provenance.ref_usine
   AND magasin.ref_mag  = provenance.ref_mag
   AND produit.ref_prod = provenance.ref_prod;


/* Question 17 */
SELECT DISTINCT (produit1.nom_prod, produit2.nom_prod)
  FROM produit AS produit1, produit AS produit2, provenance AS provenance1,
       provenance AS provenance2
 WHERE produit1.ref_prod                    <  produit2.ref_prod
   AND ABS(produit1.poids - produit2.poids) <= 2
   AND produit1.ref_prod                    =  provenance1.ref_prod
   AND produit2.ref_prod                    =  provenance2.ref_prod
   AND provenance1.ref_mag                  =  provenance2.ref_mag;


/* Question 18 */
SELECT DISTINCT (produit1.nom_prod, produit2.nom_prod)
  FROM produit AS produit1, produit AS produit2, provenance AS provenance1,
       provenance AS provenance2, magasin AS magasin1, magasin AS magasin2
 WHERE produit1.ref_prod                   <  produit2.ref_prod
   AND ABS(produit1.poid - produit2.poids) <= 2
   AND produit1.ref_prod                   =  provenance1.ref_prod
   AND produit2.ref_prod                   =  provenance2.ref_prod
   AND magasin1.ref_mag                    =  provenance1.ref_mag
   AND magasin2.ref_mag                    =  provenance2.ref_mag
   AND magasin1.ville                      =  magasin2.ville;


/* Question 19 */
SELECT (usine.ville, magasin.ville), AVG(poids * quantite)
  FROM usine, magasin, provenance, produit
 WHERE usine.ref_usine    = provenance.ref_usine
   AND provenance.ref_mag = magasin.ref_mag
   AND produit.ref_prod   = provenance.ref_prod
 GROUP BY (usine.ville, magasin.ville);
