// import le scanner
import java.util.Scanner;
// import l'object stack (la pile)
import java.util.Stack;

/**
 * @author: Guillaume Guerin et Iskeinder Ka
 *
 * correction exame CI2 2012/2013 :: exercice 2 :: question 4
 */
public final class Exo2 {

      // scanner pour lire les entrés
      private static final Scanner in = new Scanner(System.in);

      /**
      * réécriture de la fonction main en utilisant une pile
      */
      public static void main(final String[] args) {
            int ic = 0; // instruction courante
            int[] memoire = new int[10];

            // pile d'entier
            Stack<Integer> p = new Stack<Integer>();


            // boucle tant que l'on est pas arrivé à l'instruction de fin.
            while(ic != 4) { // l'instruction de fin est 4

                  // un switch qui doit prendre tous les cas ic possible
                  switch(ic) {

                        // cas d'initialisation
                        case 0:
                              // met en tête de la pile le nombre d'entré lu
                              p.push(0);
                              // on passe à l'instruction suivante
                              ic = 1;
                        break;

                        // cas de lecture des entrés
                        case 1:
                              // récupère le nombre d'entier lu
                              ic = p.pop();

                              // toutes les entrés ont été lues
                              if (ic > memoire.length - 1) {
                                    // on passe à l'instruction 2
                                    ic = 2;
                                    // met dans la pile le nombre d'éléments courant
                                    p.push(0);

                              // si non on continue la lecture
                              } else {
                                    // on met l'entré dans en haut de pile
                                    p.push(in.nextInt());
                                    // on remet le compteur du nombre de lu + 1
                                    p.push(ci + 1);
                                    ic = 1;
                              }
                        break;

                        // calcule des valeurs et mise en mémoire

                        case 2:
                              ic = p.pop();
                              if (ic < memoire.length) { // il reste des éléments
                                    /* on met dans la mémoire
                                    attention mettre dans une pile inverse
                                    les éléments donc ici on a en premier
                                    les derniers élément mis dans la pile.*/
                                    memoire[memoire.length - 1 - ic] =
                                          ((memoire.length - 1 - ic) % 5) * p.pop();
                                    
                                    // on remet l'index du tableau dans la pile
                                    p.push(ic + 1);
                                    ic = 2;
                              } else {
                                    // plus rien a mettre dans la mémoire
                                    // on passe a l'instruction suivante
                                    ic = 3;

                                    // on remet dans la pile l'index courant
                                    p.push(0);
                              }
                        break;

                        // affiche les valeurs
                        case 3:
                              ic = p.pop();

                              // si on a encore des éléments à afficher
                              if (ic < memoire.length) {
                                    // on affiche
                                    System.out.println(
                                          "t["
                                          + ic
                                          + "]="
                                          + memoire[ic]);

                                    // mise a jour de la pile
                                    p.push(ic + 1);
                                    ic = 3;
                              } else {
                                    // on a fini
                                    ic = 4;
                              }
                        break;

                  } // fin switch(ic)
            } // fin while(ic != 4)
      } // fin main

} // fin class
