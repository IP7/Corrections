# Partiel IF1 2013/2014


## Exercice 1

### Obwod
Les choses à connaitre ici:
* Visibiliter des variables en fonction du block dans le quel elle a été définit
* Priorité des opérateurs arithmérique
* Différencier les divisions sur les entiers et sur les flotants

```java
/* La class Obwod avec des commentaires  */
class Obwod {

      public static void main(String[] args) {
      	     /* definition d'un entier i visible dans toute la methode main */
	     int i = 2;
	     
	     /* i est bien supérieur à 0 */
	     if (i > 0) {
	     	/* definition d'un entier j visible uniquement à l'intérieur du if */
	     	int j;
		
		
		j = 2 + 2 * i; /* j = 2 + (2 * 2) = 6 */
		i = i + 2 * j; /* i = 2 + (2 * 6) = 14 */
		
		/* affiche "14 6" */
		System.out.println(i + " " + j);

		/* j est bien supérieur à 0 */
		if (j > 0) {
		   /* définition d'un entier k visible uniqument à l'intéreur du if */
		   int k;


		   k = i + j / 2; /* k = 14 + (6 / 2) = 17 */
		   j = j + k / 2; /* j = 6 + (17 / 2) = 6 + 8 =  14 */
		   i = k + i / 2; /* i = 17 + (14 / 2) = 17 + 7 = 24 */

		   /* affiche "24 14 17" */
		   System.out.println(i + " " + j + " " + k);
		
		} /* fin du if (j > 0)

		/* definition d'un entier k, attention l'ancien k n'exite plus ici */
		int k;

		k = i + j / 2; /* k = 24 + (14 / 2) = 24 + 7 = 31 */
		j = j + k / 2; /* j = 14 + (31 / 2) = 14 + 15 = 29 */
		i = k + i / 2; /* i = 31 + (24 / 2) = 31 + 12 = 43 */

		/* affiche "43 29 31" */
		System.out.println(i + " " + j + " " + k);
	     
	     } /* fin du if (i > 0) */
	     
	     /* définition d'un double j et d'un entier k
	     	les autres variables du meme nom n'existe plus ici */
	     double j;
	     int k;

	     
	     i = 2 + i / 2; /* i = 2 + (43 / 2) = 2 + 21 = 23 */
	     j = 2 + i / 2; /* j = 2 + (23 / 2) = 2 + 11 = 13.0 */
	     k = 1 + i / 2; /* k = 1 + (23 / 2) = 1 + 11 = 12 */

	     /* affiche "23 13.0 12" */
	     System.out.println(i + " " + j + " " + k);

	     i = 2 + i / 2; /* i = 2 + (23 / 2) = 2 + 11 = 13 */
	     j = i / 4.0;   /* j = 13 / 4.0 = 3.25 */
	     k = i / 4;     /* k = 13 / 4 = 3 */

	     /* affiche "13 3.25 3" */
	     System.out.println(i + " " + j + " " + k);
	}
}
```

Donc l'affichage final est:
```
14 6
24 14 17
43 29 31
23 13.0 12
13 3.25 3
```

### Magic