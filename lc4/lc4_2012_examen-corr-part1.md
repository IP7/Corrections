# Examen LC4 - 26 mai 2013

## Exercice 1: Recuperation et exploitation des données du fichier de configuration

### 1.1

Il suffit de lire l'énoncer et de reserver une case mémoire pour chaque champ fournis par les fichiers de configuration.
```c
typedef struct {
    int nbQ;
    int minY;
    int minX;
    int cote;
    int pasY;
    int pasX;
} configuration;
```

### 1.2
La fonction doit prendre en argument un fichier (son chemin ?) et remplir une structure configuration avec ces infos. Voici quelques prototypes possibles :
```c
int getConf(char *path, configuration *conf);
void getConf(char *path, configuration *conf);
configuration *getConf(char *path);
```
##### Remarque 1:
Passer une structure en argument sans passer par un pointeur n'a pas ici d'interet, car on ne modifira pas la structure d'origine, mais seulement une copie (locale) de cette derniere (cf passage par valeur).

##### Remarque 2:
La dernière solution implique l'utilisation d'un `malloc` dans la fonction, et le pointeur alors renvoyé devra être libéré avec `free`.
On aurait éventuellement pu définir une fonction prenant en parametre un `FILE*` au lieu d'un `char*`, mais il faudrait alors vérifier que le fichier a été bien ouvert, et avec les droits corrects.

### 1.3
```c
int getConf(char *path, configuration *conf) {

  FILE *f = fopen(path, "r");

  int lus = fscanf(f, "%d %d %d %d %d %d",
                   &(conf->nbQ),
                   &(conf->minY),
                   &(conf->minX),
                   &(conf->cote),
                   &(conf->pasY),
                   &(conf->pasX));

    return lus == 6;
}
```
Ici on retourne un int (qui fait office de boolean) pour verifier que la structure a été remplie correctement, mais le type de retour aurait pu être `void` (et la dernière ligne supprimée).

### 1.4
```c
int main(int argc, char **argv) {
    configuration conf;

    if(!getConf("parQCM.cfg", &conf))
        return 1;
}
```
On déclare une variable de type conf, et on passe son adresse, grâce à l'opérateur `&`.  
On peut vérifier que tout c'est bien passé (getConf() renvoie 0 en cas d'echec), et sortir du programme si ce n'est pas le cas.

### 1.5

En C (norme ANSI), la déclaration de tableau est possible lorsque la longueur est connue à la compilation. Ce qui revient à dire qu'on ne peut déclarer des tableaux qu'avec des constantes (et non des variables comme en java).

Pour nous aider dans la rédaction, on peut definir un type coord, qui sera un tableau de 2 entiers :
```c
typedef int coord[2];
```
##### Utilisation
Soit des coordonées c, on accède au premier champs (abscisse) avec `c[0]`, et au second champ (ordonnée) avec `c[1]`.

De même, une ligne est une suite de 10 cases, pour recuperer les coordonées des cases, on définit donc :
```c
typedef coord ligne[10];
```
##### Utilisation
Soit une ligne l. Pour acceder à la coordonée x de la 3ème case, on ecrira `l[2][0]`.

Cependant, on ne peut pas utiliser cette methode pour déclarer le tableau de ligne (car de longueur variable). Il faut donc utiliser malloc.

```c
int main(int argc, char **argv) {
  configuration conf;

  if(!getConf("parQCM.cfg", &conf))
    return 1;

  ligne *l = malloc(sizeof(ligne)*conf.nbQ);

  int i, j;

  for(i = 0; i < conf.nbQ; i++) {
    for(j = 0; j < 10; j++) {
      l[i][j][0] = conf.minX + j*conf.pasX;
      l[i][j][1] = conf.minY + i*conf.pasY;
    }
  }

  /* ... */

  free(l);

  return 0;
}
```
##### Remarque 1
La mémoire étant ici allouée avec malloc, il faudra penser à la libérer avec un appel à free une fois qu'on en aura plus besoin.

##### Remarque 2
Ici, conf est de type `configuration`, on peut donc acceder à ses champs avec l'opérateur `.`. S'il s'agissait d'un pointeur, on aurait utlisé l'opérateur `->`.

##### Remarque 3
A vrai dire, le nombre maximum de question est ici connu (45), on pourrait donc déclarer un tableau de 45 lignes, qu'on ne remplirait que partiellement (le fait que le nombre maximum de ligne soit connu dans l'énoncé pourrait faire croire que c'est même ce qui était attendu).

### 1.6

Rappel sur les macros : elle doivent etre définie sur une ligne, au moins de terminer la ligne par un backslash `\`.

Ici on applique un filtre sur un entier de 32 bits, afin de sélectionner la composante qui nous intéresse (rouge, bleu ou vert). Dans le cas du vert et du bleu on doit en plus effectuer un décalage à droite.

```c
#define rouge(x) ((x) & 0xFF)
#define vert(x) (((x) & 0xFF00) >> 8)
#define bleu(x) (((x) & 0xFF0000) >> 16)
#define estBlanc (((x) & 0xFFFFFF) == 0xFFFFFF)
#define estNoir (!((x) << 8))
```

##### Remarque 1
La valeur `0xFF` (notation hexadécimal) correspond en binaire à `0b11111111` c'est à dire un octet remplit uniquement avec des 1. Dans la même logique `0xFF00` équivaux à `0b1111111100000000`.

##### Remarque 2
L'opérateur `&` est le "et" binaire, il effectue une comparaison bit à bit. Exemple : `0b10111101 & 0b11110000 = 0b10110000`

##### Remarque 3
L'opérateur de `>>` permet d'effectuer des décalages, exemple : `0b11010101 >> 4 = 0b1101`

##### Remarque 4
Pensez toujours à parentheser vos variables dans le corps des macro.

Par exemple, si on écrit `#define rouge(x) (x & 0xFF)`, et que l'on appel cette macro avec `1 && 2` (ne cherchez pas le sens de cet appel) :
```
rouge(1 && 2) -> (1 && 2 & 0xFF) -> (1 && (2 & 0xFF))
```
Alors que l'on souhaitait obtenir `((1 && 2) & 0xFF)`
