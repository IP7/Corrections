Rappel:
une constante c’est pour distinguer quelque chose dans un domaine, par exemple pour personne,
une constante désigne une personne en particulier.

## Exercice 1 ##

### 1) ###
domaine

* age

constantes

* moins de 8 ans: âge
* entre 8 et 12: âge
* plus de 12: age

op de test:

  * est moins 8: âge -> bool
  * est entre 8 et 12: âge -> bool
  * est plus 12: âge -> bool

### 2) ###
domaine:

* activite_demandee (a.d)

constantes: 

 *  bibliotheque: a.d
 *  peinture: a.d

operation de construction:

 *  cours_piscine: {x int | 1 ≤ x ≤ 230} → a.d
 *  cours_tennis : {(x, y): int, int | 1 ≤ x + y ≤ 100} → a.d

operation de test:

*  est_bibliotheque, est_peinture, est_tennis, est_piscine: a.d → bool

opération d’accès:

 *  nb_piscine: {x: a.d | est_piscine(x) →  {y: int | 1 ≤ y ≤ 230}}
 *  nb_matchs_simple {x : a.d | est_tennis(x) } → {y: int | 1 ≤ y ≤ 100}
 * nb_matchs_double {x : a.d | est_tennis(x) } → {y: int | 1 ≤ y ≤ 100}

operations de construction edentue
 * int_to_piscine: int → a.d
 * int_int_to_piscine: int, int → a.d

domaine:

* ville

constante:

* astride: ville
  * pas_astride: ville

operations de test:

* est_astride: ville → bool

### 3) ###

domaine: 

*  personne

constante: (aucune)

operation de construction:

* cons_personne: âge, ville, string -> personne

operation de test:

 * age_personne: personne -> âge
 *  ville_personne: personne -> ville   
 *  nom_personne: personne -> string

### 4) ###

domaine:

*  dossier

operations de constructions

* cons_dossier: personne, a.d, -> dossier

opération d’accès:

 *  personne_dossier: dossier -> personne
 *  ad_dossier: dossier -> a.d


### 5) ###

domaine:
 
* liste_dossier (liste.d)

constante:

*   liste_vide: liste.d

opération de construction

* nom_liste: dossier, liste.d -> liste.d

operation de test:

*   est_liste_vide: liste.d -> bool

opération d’accès:

*   tête: {x: liste.d | mot (est_liste_vide(x)} -> dossier
*   queue: {x: liste.d | mot (est_liste_vide(x)} -> liste.d
  
### 6) ###

Fonct a_droits_age_ville(p, a): personne, a.d -> boo  l

 > Si(
 
 >>   est_piscine(a) ou est_peinture(a) ou 
 
 >>   (est_bibliotheque(a) and est_plus_12(p)) ou 
 
 >>   (est_tennis(a) and est_astride(ville_personne(p)) and not moins_8(age_personne(p)))

>  )alors

>>    renvoie Vrai

> finSi

> renvoie Faux

finFonct


### 7) ###

a_droit_dossier(d) -> bool

>  a_droit_age_ville(personne_dossier(d), ad_dossier(d))

### 8) ###

Fonct prix_dossier(d): dossier-> int 

>  soit p = personne_dossier(d) et a = ad_dossier(d) dans

> Si (est_piscine(a) then

>> renvoie 15 * nb_piscine(a)

> Sinon Si (est_bibliotheque(a))

>> renvoie 0

> Sinon Si (est_peinture(a))

>> Si(plus_12(age_personne(p))

>>> renvoie 1500

>>    Sinon 

>>> renvoie 1300

>> finSi

> Sinon

>> renvoie 40 * nb_matchs_simples(a) + nb_matchs_double(a)

> finSi

finFonct

### 9) ###

Fonct prix-global(l): liste.d -> int

>  Si est_liste_vide(l) alors

>>    0

>  Sinon

>>    soit d = tête(l) et q = queue(l) dans

>>  Si a_droits_dossiers(d)

>>> prix_dossier(d) + prix_global(q)

>>  Sinon 

>>>  prix_global(q)

>>  finSi

>  finSi

finFonc