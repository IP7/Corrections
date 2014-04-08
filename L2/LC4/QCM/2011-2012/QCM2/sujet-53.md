# Corrigé du QCM du 2 mai 2012 - Sujet 53

Corrigé non-officiel par Baptiste Fontaine pour IP7

## Question 1

`z` vaudra `3-6*4+2` soit `-23` (réponse 5). Pour obtenir `-18`, il aurait
fallu utiliser des parenthèses :

```c
#define f(x,y) (x)*(y)
```

Il est même préférable de mettre des parenthèses partout pour éviter les
problèmes :

```c
#define f(x,y) ((x)*(y))
```

## Question 2

La boucle `for(A;B;C) D` exécute `A`, puis tant que `B` est vrai, exécute `D`
puis `C`, ce qui correspond à la réponse 3.


## Question 3

Réponse 7.


## Question 4

Réponse 3 : `20 21 6 7`. La structure est passée par valeur, donc aucun
changement dans `f1` n’est conservé en dehors, sauf pour le champ `p` qui est
un pointeur, donc on modifie les valeurs pointées.


## Question 5

Réponses 5 et 7 : on prend en argument un entier (`int`) et un pointeur sur
caractère `char*` et on renvoit un pointeur sur `void` (`void*`), ce sont les
deux seuls prototypes qui correspondent.


## Question 6

Réponses 6 et 8. Les autres réponses ont soit un problème de type (par exemple
pour la 1, on passe un argument de type `T*` à une fonction qui attend un type
`T`), soit un problème de mémoire (`T` est un type pointeur sur structure, il
faut donc allouer la mémoire qui correspond à la structure).


## Question 7

La compilation provoque une erreur (réponse 1) car le champ `suivant` est un
pointeur sur structure, et `maliste` est une structure donc les types ne
correspondent pas, il y a une erreur à la première ligne de la fonction `main`.


## Question 8

Cette question est une variante de la question 4, sauf qu’ici on passe un
pointeur sur la structure, donc les valeurs sont bien modifiées. Le programme
affiche donc `21 22 6 7` (réponse 1).

## Question 9

Seules les réponses 3, 4, 8 et 9 sont syntaxiquement correctes. De façon
générale, on ne peut pas caster une structure en une autre différente, même si
les champs sont identiques. La réponse 8 est correcte car on caste un
*pointeur*, pas la structure associée. Attention ici, le fait qu’une expression
soit correcte syntaxiquement ne signifie pas qu’elle ne fera pas planter le
programme.


## Question 10
## Question 11
## Question 12
## Question 13
## Question 14
## Question 15
## Question 16

Réponse 8. On définit un type avec `typedef`, donc les réponses 2, 4, 6 et 7
sont éliminées d’office. La réponse 5 est éliminée car il n’y a pas de pointeur
sur pointeur dans le type sinon on aurait une suite de deux étoiles (`**`).

## Question 17
## Question 18
## Question 19
## Question 20
## Question 21
## Question 22
## Question 23
## Question 24
## Question 25
## Question 26
## Question 27
## Question 28
## Question 29
## Question 30
## Question 31
