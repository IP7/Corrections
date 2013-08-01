

public class Cartouche {
	
	private int contenance;
	private int remplissage;
	private boolean etat;
	private String couleur;


	public Cartouche(int contenance, String couleur) {
		remplissage = 100;
		this.contenance = contenance;
		this.couleur = couleur;
		etat = true;
	}

	public void remplissage(int volume, String couleur) {
		if (!this.couleur.equals(couleur)) {
			etat = false;
			return;
		}

		if (volume >= contenance - contenance / 100.0 * remplissage) {
			etat = false;
			return;
		}

		remplissage += 100.0 / contenance * volume;
	}
}