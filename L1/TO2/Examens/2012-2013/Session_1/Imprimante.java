
public class Imprimante {

	private static int compteur = 0;
	
	// question 1
	private int quantite;
	private int max;
	private Cartouche cartouche;
	private String marque;
	private int numeroSerie;

	// question 2
	public Imprimante(int maxQuantite, String marque) {
		quantite = 0;
		max = maxQuantite;
		cartouche = null;
		this.marque = marque;
		numeroSerie = compteur;
		compteur++;
	}

	// question 3
	public int remplissage(int nombreDeFeuille) {
		if (nombreDeFeuille >= max - quantite) {
			quantite = max;
			return nombreDeFeuille - (max - quantite);
		}

		quantite += nombreDeFeuille;
		return 0;
	}
}
