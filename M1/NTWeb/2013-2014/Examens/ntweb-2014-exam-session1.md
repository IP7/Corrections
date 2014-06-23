# Examen de NTWeb session 1 2014

## I. Historique

TODO

## II. Usages

TODO

### Distributions

#### Question 6

La courbe de gauche représente la distribution des photos en fonction du nombre
d’utilisateurs, avec des axes logarithmiques. Il faut lire la courbe comme « Y
utilisateurs ont publiés X photos. »

#### Question 7

Cette distribution n’est pas suprenante par rapport aux usages des plateformes
Web en général, où l’on retrouve généralement un petit nombre de gros
producteurs de contenu, et beaucoup de consommateurs de contenu.

#### Question 8

La courbe de droite montre le taux d’utilisateurs (ordonnées) qui ont produit
un certain taux de contenu (abscisse). Une courbe complètement droite (`y=x`)
indique une homogénéité parfaite, où tous les utilisateurs produisent la même
part de contenu. Plus la courbe est au dessus, plus la distribution est
hétérogène, comme ici où une minorité d’utilisateurs produit la majorité du
contenu. On peut voir sur la courbe que 20% des utilisateurs produisent 80% des
photos.

#### Question 9

Le coefficient de Gini est calculé en prenant la distance entre la courbe
complètement droite et la courbe de Lorenz. Il vaut 0 pour une homogénéité
parfaite, et 1 pour une hétérogénéité totale (par exemple un seul utilisateur
produit 100% des photos).

#### Question 10

Une plateforme Web peut tirer parti de cette hétérogénéité des usages en
encourageant les producteurs de contenu (par exemple Flickr offre 1To de
stockage, en sachant pertinamment que très peu d’utilisateurs utiliseront plus
de quelques centaines de Mo, Quora offre des tshirts et une communication plus
personalisée à ses « Top Writers, » YouTube permet aux producteurs
sufffisamment vus de monétiser leurs vidéos, etc) et en utilisant le grand
nombre de consommateurs pour monétiser la plateforme, souvent grâce aux
publicités. Twitter attire les consommateurs de contenu grâce aux célébrités
qui y sont inscrites, et monétise en affichant des tweets sponsorisés, qui sont
de ce fait vus par un grand nombre de personnes.

## III. Programmation

#### Question 1

Le document HTML doit charger le script de D3, et le script qui définit les
données utilisées (`window.data[tag]`).

#### Question 2

Lors de l’appel à la fonction `plot("wedding")`, l’élément sélectionné à la
ligne 11 doit avoir pour `id` `tag-wedding`.

#### Question 3

Cet élément doit contenir un élément `svg`, qui est sélectionné à la ligne
suivante (ligne 12).

#### Question 4

La variable `x` est une fonction (comme on peut le voir ligne 24), elle prend
en argument une valeur d’abscisse et renvoit la valeur à utiliser sur le
graphique, de façon à rester entre 0 et la largeur du graphique.

#### Question 5

La chaîne `".dot"` à la ligne 19 désigne les points du graphique, qui sont des
éléments SVG avec une `class` `dot`. Si on modifie cette chaîne, il faut
changer également la ligne 22, et la feuille de style CSS s’il y en a une qui
utilise cette classe.

#### Question 6

Ce script définit une fonction `plot` qui prend en argument un tag et trace les
données associées à celui-ci, situées dans `window.data[tag]`, dans un élément
SVG situé dans un élément du document HTML qui a l’id `tag-<nom du tag>`, avec
une échelle logarithmique. Cette fonction est ensuite appelée sur les tags
`wedding` et `beach`.

#### Question 7

```html
<h1>De jolies courbes</h1>

<section id="tag-wedding">
    <h1>#Wedding</h1>

    <p>Ce tag est intéressant parce que …</p>

    <svg></svg>
</section>

<section id="tag-beach">
    <h1>#Beach</h1>

    <p>Celui-ci est également intéressant car …</p>

    <svg></svg>
</section>
```

Note : on utilise ici le fait qu’à partir de HTML5 la hiérarchie des titres est
interne aux éléments, donc il peut y avoir plusieurs `h1` dans le document
pourvus qu’ils soient dans des éléments différents (par ex `article`,
`section`, etc).
