/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Gnukos
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 *
 * @author Guillaume Guerin aka Gnukos
 *
 * Partiel 2013-2014: exercice 5 
 *
 */


/*
 * on importe la class Scanner pour pouvoir lire
 * les entres des joueurs
 */
import java.util.Scanner;


/**
 * Le jeu de 13 allumettes ce joue comme ce-ci:
 * Initialisation de la partie: 13 allumettes en jeu
 * Les joueurs jouent chacun leur tour, le joueur 0 commence
 * Il y a seulement 2 joueurs.
 * Les joueurs peuvent retirer de une a 3 allumette par tour.
 * Le joueur qui enleve la derniere allumette gagne.
 */
public final class Jeu13 {


    /**
     * Fonction main, point de depart du programme
     */
    public static void main(String[] args) {
	// nombre d'allumette
	int nbAllumette = 16;
	// numereau du joueur
	int numJoueur = 1;


	/*
	 * On boucle tant que la partie n'est pas fini
	 * c'est a dire tant qu'il reste des allumettes.
	 */
	while (nbAllumette > 0) {
	    
	    /*
	     * alternance des joueurs
	     * Rappel: s'il n'y a pas d'acolade un if, if else ou else
	     *         ne s'applique qu'a l'instruction suivante.
	     */
	    if (numJoueur == 0)
		numJoueur = 1;
	    else
		numJoueur = 0;

	    // affichage + demande du coup suivant
	    int nbAllumetteRetirees = jouer(nbAllumette, numJoueur);
	    
	    // controlle de la validite du coup
	    if (nbAllumetteRetirees < 1        // pas de rajout d'alumette
		|| nbAllumetteRetirees > 3) {  // 3 maximum
		System.out.println("Le joueur "
				   + numJoueur
				   + " a ete discalifie pour non respect des regles.");
		return; // termine le programme
	    } // fin du if de control
	    
	    /**
	     * mise a jour du nombre d'allumettes
	     * Pour ceux qui ne conaissent pas cette syntaxe est equivalente a:
	     * nbAllumette = nbAllumette - nbAllumetteRetirees
	     */
	    nbAllumette -= nbAllumetteRetirees;

	} // fin du while

	// La partie est finie, on affiche le resultat.
	System.out.println("Le joueur "
			   + numJoueur
			   + " a gagne la partie!");


    } // fin de la methode main

   
    /**
     * Affiche l'etat de la partie et recupere le prochain coup
     *
     * @param nbAllumette nombre d'allumettes restantes
     * @param numJoueur numero du joueur courant
     * @return le nombre d'allumette que le joueur veux enlever
     */
    public static int jouer (final int nbAllumette, final int numJoueur) {
	// affiche l'etat actuel du jeu, et demande le coup au joueur
	System.out.print("Il reste "
			 + nbAllumette
			 + " Allumettes. C'est au joueur "
			 + numJoueur
			 + " de joueur. Retirer combien d'allumette? ");
	// creation d'un scanner pour lire le coup
	Scanner sc = new Scanner(System.in);
	
	// on lit et on renvoie l'entier rente
	return sc.nextInt();
    } // fin de la methode jouer

} // fin de la class Jeu13

