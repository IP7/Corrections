

public class Noeud {
	// modification de la visibilité de val et suivant
	private int val;
	private Noeud suivant;

	public Noeud (int x, Noeud n) {
		this.val = x;
		this.suivant = n;
	}

	public int getVal() { return val; }
	public Noeud getSuivant() { return suivant; }
	public void setVal(int n) { val = n; }
}
