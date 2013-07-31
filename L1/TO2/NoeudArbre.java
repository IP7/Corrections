
public class NoeudArbre {

	private int etiquette;
	private NoeudArbre gauche;
	private NoeudArbre droit;

	public NoeudArbre(
		int etiquette,
		NoeudArbre gauche,
		NoeudArbre droit) {
		this.etiquette = etiquette;
		this.gauche = gauche;
		this.droit = droit;
	}

	public NoeudArbre(int etiquette) {
		this.etiquette = etiquette;
		this.gauche = null;
		this.droit = null;
	}

	public int getEtiquette() { return etiquette; }
	public NoeudArbre getDroit() { return droit; }
	public NoeudArbre getGauche() { return gauche; }

	public void setGauche(NoeudArbre g) { gauche = g; }
	public void setDroit(NoeudArbre d) { droit = d; }
}