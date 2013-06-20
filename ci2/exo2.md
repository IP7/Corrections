
# Examen IC2 2012/2013


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
la taille mininum de mémoire est 10, effectivement on doit stoker les `10` nombres entré par l'utilisateur. `in.nextInt()` renvoie un entier, donc mémoire sera de type `int[]`.

### Question 3:
Le tableau t devient la mémoire, les autres varaibles sont stockées dans la pile.

### Question 4:
voir Exo2.java

