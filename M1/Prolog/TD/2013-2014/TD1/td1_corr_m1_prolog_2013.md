# Correction du TD 1 de Prolog (2013/2014)

## Exercice 1

Voir le fichier `fact.pl`.

Le prédicat binaire `fact` vérifie que la factorielle de son premier
premier argument est égale à son second argument.

## Exercice 2

1. Socrate est un homme.
2. Tout homme est mortel.
3. Tout chien est un animal.
4. Tout mammifère ovipare amphibie est un ornithorynque.

## Exercice 3

```prolog
/* likes(people,thing) */
likes(adam,apples).
likes(clara,carrots).
likes(olivier,oranges).

/* fruit(thing) */
fruit(apples).
fruit(oranges).

/* vegetable(thing) */
vegetable(carrots).

/* 2- Qui est en bonne santé ? */
healthy(X) :- likes(X, Y), fruit(Y).

/* 3- Qui aime les pommes ? */
likes(X, apples).

/* 4- Liste des fruits */
fruit(X).
```

## Exercice 4

### Exercice 4.1

```prolog
bio(X, f, _, _, _, _).
```

### Exercice 4.2

```prolog
bio(X, f, _, _, _, _), bio(X, _, _, _, _, X).
```

### Exercice 4.3

```prolog
bio(X, _, N, _, _, _), N > 1750, N < 1800.
```

### Exercice 4.4

```prolog
bio(X, _, _, _, henri4, _), bio(_, _, _, _, _, X).
```

### Prédicats à ajouter

```prolog
enfant(X, Y) :- bio(X, _, _, _, Y, _).
enfant(X, Y) :- bio(X, _, _, _, _, Y).

ptenfant(X, Z) :- enfant(X, Y), enfant(Y, Z).

descendent(X, Z) :- enfant(X, Z).
descendent(X, Z) :- enfant(X, Y), descendent(Y, Z).
```

### Requêtes 1

```prolog
ptenfant(X, henri4), bio(X, f, _, _, _, _).
```

### Requêtes 2

```prolog
descendent(X, louis14).
```

### Requêtes 3

```prolog
descendent(louis17, X).
```
