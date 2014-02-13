# Examen 2013-2014 Architecture

## Exercice 1

### a)

S = /e2.e1.e0 + e2./e1.e0 + e2.e1./e0 + e2.e1.e0

### b)

![](1b.png)

Il est possible d'éviter les portes NOT, pour ça il faut refaire la formule, on se sert d'un tableau de karnaug:

|e2\e1e0| 00 |  01 | 11 | 10 |
|-------|:--:|:---:|:--:|:--:|
| **0** |  0 |  0  |  1 |  0 |
| **1** |  0 |  1  |  1 |  1 |

S = e2e1 + e0e1 + e0e2

![](1bn.png)

### c)

Pour se contenter d'utiliser des portes NOR, on utilise les formules suivantes:

a+b = /(/(a+b)+0)
a.b = /(/(a+0)+/(b+0))

![](1c.png)