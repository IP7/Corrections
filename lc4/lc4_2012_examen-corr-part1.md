# Examen LC4 - 26 mai 2013

## Exercice 1: Recuperation et exploitation des données du fichier de configuration

#### 1.1

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

#### 1.2
La fonction doit prendre en argument un fichier (son chemin ?) et remplir une structure configuration avec ces infos. Voici quelques prototypes possibles :
```c
int getConf(char *path, conf *configuration);
void getConf(char *path, conf *configuration);
configuration *getConf(char *path);
```
Remarque 1:
Passer une tructure en argument sans passer par un pointeur n'a pas ici d'interet, car on ne modifira pas la structure d'orrigine.

Remarque 2:
La dernière solution implique l'utilisation d'un `malloc` dans la fonction, et le pointeur alors renvoyé devra être libéré avec `free`.
On aurait éventuellement pu définir une fonction prenant en parametre un `FILE*` au lieu d'un `char*`, mais il faudrait alors vérifier que le fichier a été bien ouvert, et avec les droits corrects.

#### 1.3
```c
int getConf(char *path, conf *configuration) {

    FILE *f = fopen(path, "r");

    int lus = fscanf(f, "%d %d %d %d %d %d",
                   &(conf->nbQ),
                   &(conf->minY),
                   &(conf->minX),
                   &(conf->cote),
                   &(conf->pasY),
                   &(conf->pasX))
    return lus == 6;
}
```

#### 1.4
```c
int main(int argc, char **argv) {
    configuration conf;

    if(!getConf("parQCM.cfg", &conf))
        return 1;
}
```
On déclare un une variable de type conf, et on passe son adresse, grâce à l'opérateur '&'

#### 1.5

En C (norme ANSI), la déclaration de tableau est possible lorsque la longueur est connue à la compilation. Ce qui revient à dire qu'on ne peut déclarer des tableaux qu'avec des constantes (et non des variables comme en java).

Pour nous aider dans la rédaction, on peut definir un type coord, qui sera un tableau de 2 entiers.

```c
typedef int[2] coord;
```
Soit des coordonées c, on accède au premier champs (abscisse) avec c[0], et au second champ (ordonnée) avec c[1].

De même, une ligne est une suite de 10 cases, pour recuperer les coordonées des cases, on définit donc :
```c
typedef coord[10] ligne;
```
Soit une ligne l. Pour acceder à la coordonée x de la 3ème case, on ecrira l[2][0]

Cependant, on ne peut pas utiliser cette methode pour déclarer le tableau. Il faut donc utiliser malloc.

```c
ligne *l = malloc(sizeof(ligne)*conf->nbQ);

int i, j;

for(i = 0; i < conf->nbQ; i++) {
    for(j = 0; j < 10; j++) {
        l[i][j][0] = x + j*nb->pasX;
        l[i][j][1] = y + i*nb->pasY;
    }
}

/* ... */

free(l);
```

Attention, la mémoire étant ici allouée avec malloc, il faudra penser à la libérer avec un appel à free une fois qu'on en aura plus besoin.

A vrai dire, le nombre maximum de question est ici connu (45), on pourrait donc déclarer un tableau de 45 lignes, qu'on ne remplirait que partiellement (le fait que le nombre maximum de ligne soit connu dans l'énoncé pourrait faire croire que c'est même ce qui était attendu)
