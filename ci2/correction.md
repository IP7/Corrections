# Examen IC2 2012/2013


## Exercice 1 :

### Question 1 :
Des variables sont déclarées aux lignes :
* ligne `21` C'est un objet de type Bidule à la fois déclaré et initialisé
* ligne `26` même chose qu'a la ligne `21`
* ligne `33` c'est un type primitif à la fois déclaré et initialisé
* ligne `38` même chose que pour la ligne `33`

### Question 2 :
Les fonction de la `class Ex1` sont déclarées aux lignes :
* ligne `8`, `11`, `15`, `20`
* ligne `20` bien que se soit le `main` du programme c'est une fonction

#### Remarque 1 :
Ici on considère que les constructeurs ne sont pas des fonctions car ils ne respecte pas toutes les caractéristiques d'une fonction.


### Question 3 :
Le programme affiche :
* ligne `22` l'adresse de l'objet de la forme `package.nomDeLaClass@adresseEnHexadecimal`
* ligne `24` la même chose qu'à la ligne `22`
* ligne `27` `2` Puisque nous avons utilisé le constructeur avec l'argument `2` à la ligne `26`
* ligne `29` `2` Puisque l'on ne récupère pas le résultat de la fonction `int [] f` à la ligne `28` et que la fonction initialise un nouveau tableau sans modifier l'ancien
* ligne `31` `2` Puisqu'on ne récupère pas le résultat de la fonctio `int f` à la ligne `20`
* ligne `36` `3` La modification d'un type primitif dans une fonction n'a pas d'influence sur le reste du code donc l'appel à `int f` ne change pas la valeur de `i`
* ligne `40` `I[AdresseDuTableauEnHexadeciaml 4`
* ligne `42` `AdresseDuTableau 4` la même adresse qu'à la ligne 40, 4 car on ne traite pas le tableau retourné par la fonction `int[] f` à la ligne `41`

### Question 4 :
Si on remplace la ligne `41` par `t1 = f(t1)` la ligne `42` va afficher `10` car cette fois ci on récupère la valeur de retour.


## Exercice 2 :
Ne pas oublier de lire exo2.java.

### Question 1 :
input: `1 2 3 4 5 6 7 8 9 10`

La premier boucle remplit le tableau en partant de l'indice `0` jusqu'à l'indice `9` avec comme valeur `f(v, in.nextInt())`.
`v`: indice courant dans le tableau.
`in.nextInt()`: entré utilisateur courante.

A la fin de la boucle le tableau contiendra les valeurs suivantes :
```java
t[0] = 0   // (0 % 5) * 1
t[1] = 2   // (1 % 5) * 2
t[2] = 6   // (2 % 5) * 3
t[3] = 12  // (3 % 5) * 4
t[4] = 20  // (4 % 5) * 5
t[5] = 0   // (5 % 5) * 6
t[6] = 7   // (6 % 5) * 7
t[7] = 16  // (7 % 5) * 8
t[8] = 27  // (8 % 5) * 9
t[9] = 40  // (9 % 5) * 10
```

Un peu long et fastidieux mais ça se fait bien. La deuxième boucle affiche le tableau avec le model suivant :
`"t[" + v + "]=" + t[v]`
donc l'affichage produit à l'exécution est: (à vous de completer les "...")
```java
t[0]=0
t[1]=2
t[2]=6
.
.
.
t[9]=40
```

#### Remarque 1:
`v % n = ` reste de la division euclidienne de `v` par `n`.

#### Remarque 2:
System.out.println(...); rajoute une fin de ligne à la fin

### Question 2:
la taille mininum de mémoire est `0`.

### Question 3:
Le tableau t devient la mémoire, les autres varaibles sont stockées dans la pile.

### Question 4:
voir Exo2.java

