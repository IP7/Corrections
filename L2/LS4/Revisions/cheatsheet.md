# Les itérables en Python 3

Les « itérables » sont des valeurs Python sur lesquels on peut itérer, comme
les listes, chaînes de caractères, dictionnaires, tuples et ensembles.

Certaines fonctions marchent sur tous les types d’itérables, par exemple `len`
qui renvoit le nombre d’éléments (sauf pour les générateurs).

## Générateurs

Les générateurs sont un type particulier d’itérables, qui ne sont pas vraiment
des listes, et que vous ne rencontrerez pas en dehors de la fonction `range` :

La fonction `range` prend un, deux, ou trois arguments :

1. Avec un argument `m`, elle génère les nombres de à n-1.
2. Avec deux arguments `n` et `m`, elle génère les nombres de n à m exclus.
3. Avec trois arguments, `n`, `m` et `p`, elle génère les nombres de n à m
   exclus, en utilisant un pas p. Par exemple, si `p` vaut 2, elle génèrera un
   nombre sur 2. Si `p` est négatif (par exemple -1), elle ira de haut en bas,
   si n est supérieur à m.

La fonction ne génère rien dans les cas suivants :

* `m` est plus petit que `n`, sauf si `p` est négatif
* `m` est plus grand que `n` et `p` est négatif
* `m` est égal à `n`

Par défaut (cas à un et deux arguments), `n` vaut 0 et `p` vaut 1.

On utilise généralement `range` dans le cas de `for … in`:

```py
for i in range(12):
    print(i)
```

Comme `range(17)` ne renvoit pas une liste, si on en veut une il faut forcer
Python à nous la donner, avec `list(range(17))`. Par exemple il n’est pas
possible d’avoir la longueur d’un générateur (`len(range(3))`) ou d’utiliser un
indice (`range(17, 84)[3]`).


Quelques exemples avec `range`:

```py
# nombres de 0 à 42
range(43)

# nombres de 17 à 21
range(17, 22)

# 1 nombre sur 2 de 10 à 20
range(10, 21, 2)

# nombres de 3 à -5
range(3, -5, -1)

# juste 56
range(56, 57)
```

## Listes

Les listes sont représentées entre crochets, sont extensibles (pas de taille
fixe), et peuvent contenir n’importe quel type, y compris d’autres listes.

On peut transformer un itérable en liste avec `list`:

```py
list(range(3))      # [0, 1, 2]
list((True, False)) # [True, False]
list("wxc")         # ["w", "x", "c"]
```

### Opérations sur les listes

On peut récupérer la valeur à un indice donné avec `l[i]`, où `i` est l’indice.

#### Modification

On peut modifier un indice existant d’une liste :

```py
l = ["bonjour", "le", "monde"]

l[0] = "bonsoir"
```

Les indices négatifs sont supportés, ils partent de la fin de la liste. Par
exemple, `l[-1]` est pareil que `l[len(l)-1]`.

La fonction `.append` permet d’ajouter en fin de liste :

```py
a = [1, 2]
a.append(3)
a.append(4)

print(a) # [1, 2, 3, 4]
```

On peut insérer un élément au milieu d’une liste avec `.insert(i, el)` :

```py
a = ["bonjour", "monde"]
a.insert(1, "le")

print(a) # ["bonjour", "le", "monde"]
```

La fonction `.pop()` enlève et retourne le dernier élément de la liste :

```py
a = ["monde", "le", "bonjour"]

print(a.pop()) # bonjour
print(a.pop()) # le
print(len(a))  # 1
print(a.pop()) # monde
print(a)       # []
```

On peut concaténer deux listes avec l’opérateur `+` ou la fonction `extend` :

```py
print([1, 2] + [3, 4]) # [1, 2, 3, 4]

a = [1, 2]
a.extend([5, 6])

print(a) # [1, 2, 5, 6]
```

À noter que la fonction `extend` prend un itérable, pas uniquement une liste :

```py
a = [1]
a.extend(range(2, 5))
print(a) # [1, 2, 3, 4]
```

Les fonctions suivantes ne renvoient rien mais modifient la liste :

* `l.reverse()` : inverse la liste
* `l.sort()` : trie la liste
* `l.clear()` : efface tous les éléments de la liste

#### Compréhension de listes

Les compréhensions de listes permettent de construire simplement une liste à
partir d’un (ou deux) itérable(s), comme par exemple une autre liste.

Elles ont la syntaxe suivante :

```py
a = [expr1 for expr2 in iterable]
b = [expr1 for expr2 in iterable if condition]
c = [expr1 for expr2 in iterable1 for expr3 in iterable2]
d = [expr1 for expr2 in iterable1 for expr3 in iterable2 if condition]
```

Les 4 exemples ci-dessus sont respectivement équivalents aux codes suivants:

```py
a = []
for expr2 in iterable:
    a.append(expr1)

b = []
for expr2 in iterable:
    if condition:
        b.append(expr1)

c = []
for expr2 in iterable1:
    for expr3 in iterable2:
        c.append(expr1)

d = []
for expr2 in iterable1:
    for expr3 in iterable2:
        if condition:
            d.append(expr1)
```

Quelques exemples :

```py
# recopie d'une liste
[e for e in ma_liste]

# le double de chaque élément de la liste
[e*2 for e in ma_liste]

# tous les couples de nombres (tuples à 2 éléments) entre 0 et 3 inclus
[(a, b) for a in range(4) for b in range(4)]

# tous les nombres impairs d'une liste
[x for x in ma_liste if x%2==1]

# 2e élément de chaque sous-liste
[l[1] for l in ma_liste]

# multiples de 9 jusqu’à 90
[9*i for i in range(1, 11)]
```

#### `map`

`map(f, l)` est équivalent à `[f(e) for e in l]`, en plus efficace. Le premier
argument est une fonction, et le second une liste (ou un tuple). La fonction
renvoit un générateur donc il faut utiliser `list` dessus pour récupérer la
liste correspondante.

Par exemple pour créer une liste avec les éléments d’une autre liste en
strings :

```py
list(map(str, maliste))
```

#### `for … in`

On peut parcourir les éléments d’une liste avec `for … in` :

```py
# affiche 1, 2, puis 3
for x in [1, 2, 3]:
    print(x)
```

La fonction `enumerable` permet d’itérer sur les indices et les valeurs à la
fois :

```py
# affiche:
#   0 --> foo
#   1 --> bar
#   2 --> qux
for i, e in ["foo", "bar", "qux"]:
    print(i, "-->", e)
```

#### `max` et `min`

`max(L)` et `min(L)` renvoient respectivement la valeur max et la valeur min
d’une liste. La liste doit contenir des valeurs de même type. Si ce sont des
chaînes, l’ordre lexicographique est utilisé (par exemple `min(['b', 'a',
'c'])` renvoit 'a').

#### `sum`

`sum(L)` renvoit la somme de tous les éléments d’une liste. Ceux-ci doivent
tous être des nombres.

#### Autres méthodes

* `L.count(v)` renvoit le nombre de fois où `v` est présent dans `L`
* `L.index(v)` renvoit l’indice de la première occurrence de `v`, ou lève une
  exception s’il n’y est pas

#### Sous-listes

On peut obtenir une sous-liste grâce à la syntaxe `[n:m:p]`. `n` est l’indice
de départ, `m` est l’indice de fin (non inclus), et `p` est le pas. Tous les
« arguments » sont optionnels, `n` vaut 0 par défaut, `m` vaut la longueur de
la liste, et `p` vaut 1.

Par exemple :

```py
a = [12, 34, 56, 78, 90]

a[:]  # copie de a
a[::] # idem
a[0:] # idem
a[:5] # idem

a[1000:] # liste vide
a[:1000] # pareil que a

a[1:] # [34, 56, 78, 90]
a[2:] # [56, 78, 90]

a[:4]  # [12, 34, 56, 78]
a[:-1] # idem
a[:3]  # [12, 34, 56]
a[:-1] # idem

a[1:4] # [34, 56, 78]
a[1:-1] # pareil

a[::-1] # a, inversé
```

##### Pour aller plus loin

Si vous avez compris comment fonctionnent les compréhensions de listes et
`range`, vous remarquerez que `L[n:m:p]` est presque équivalent à `[l[i] for i
in range(n, m, p)]`.

Les sous-listes peuvent même être utilisées pour modifier la liste :

```py
a = [1, 2, 3, 4]

a[1:-1] = [42, 17]
print(a) # [1, 42, 17, 4]

a[1:] = ["foo"]
print(a) # [1, "foo"]

a.append("bar")
a[1:2] = "bar"
print(a) # [1, "b", "a", "r", "bar"]
```

## Chaînes de caractères (Strings)

Les chaînes de caractères peuvent être notées avec des guillemets simples
(`'`) ou doubles (`"`).

On peut transformer un élément en chaîne avec la fonction `str`:

```py
str(42)        # "42"
str([1, 2, 3]) # "[1, 2, 3]"
str(None)      # "None"
str("abc")     # "abc"
```

### Opérations sur les chaînes

<!-- TODO -->

#### `.join`
#### `.split`
#### `.strip`
#### Autres

## Dictionnaires

Les dictionnaires sont des ensembles de paires clef/valeur. Chaque clef est
unique, et l’ordre des clefs n’est pas fixé. Ils sont représentés avec des
accolades, et chaque clef est séparée de sa valeur avec deux points (`:`).

## Tuples

Les tuples sont similaires aux listes, mais sont immutables : on ne peut pas
les modifier une fois qu’ils sont créés. Ils sont représentés par des
parenthèses.

## Opérations sur les tuples

Les tuples supportent toutes les opérations non-modifiantes des listes.

## Ensembles

Les ensembles contiennent des valeurs non ordonnées et uniques : on ne peut
avoir qu’une seule fois une valeur. Ils sont notés avec des accolades.
