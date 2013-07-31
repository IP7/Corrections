
public class Arbre {
	
	private NoeudArbre racine;

	public Arbre() {
		racine = null;
	}

	// question 1
	public int etiquetteDroite() {
		if (racine == null) { return -1; }

		NoeudArbre tmp = racine;
		while (tmp.getDroit() != null) {
			tmp = tmp.getDroit();
		}

		return tmp.getEtiquette();
	}

	// question 2
	public void ajouterFeuille(int n) {
		if (racine == null) { racine = new NoeudArbre(n); }

		aux(racine, n);
	}

	public void aux(NoeudArbre a, int n) {
		if (a.getDroit() == null && a.getGauche() == null) {
			a.setGauche(new NoeudArbre(n));
			a.setDroit(new NoeudArbre(n));
		} else {
			if (a.getDroit() != null) aux(a.getDroit(), n);
			if (a.getGauche() != null) aux(a.getGauche(), n);
		}
	}
}
