


public class Liste {
	private Noeud tete;

	public Liste() {
		this.tete = null;
	}

	public void ajouter(int x) {
		this.tete = new Noeud(x, this.tete);
	}

	/*
		question 1

		pas possible sans modifier la class Noeud
	*/
	public int nbreZeros() {
		int nb = 0;
		Noeud tmp = tete;
		
		while (tmp != null) {
			if (tmp.getVal() == 0) {
				nb++;
			}

			tmp = tmp.getSuivant();
		}

		return nb;
	}

	// question 2
	public void enlevePremier() {
		if (tete == null) return;
		tete = tete.getSuivant();
	}

	// question 3
	public void sommePartielle() {
		aux(tete);
	}

	private void aux(Noeud n) {
		if (n == null || n.getSuivant() == null) { return; }

		aux(n.getSuivant());
		n.setVal(n.getVal() + n.getSuivant().getVal());
	}



	// bonus
	public String toString() {
		Noeud tmp = tete;
		String str = "(";

		while(tmp != null) {
			if (tmp.getSuivant() != null)
				str += tmp.getVal() + ", ";
			else
				str += tmp.getVal();

			tmp = tmp.getSuivant();
		}

		return str += ")";
	}


	public static void main(String[] args) {
		Liste l = new Liste();
		l.ajouter(0);
		l.ajouter(1);
		l.ajouter(0);

		System.out.println("l.nbrezeros(): " + l.nbreZeros());
		l.enlevePremier();
		l.ajouter(5);
		l.ajouter(10);
		System.out.print(l + ".sommePartielle(): ");
		l.sommePartielle();
		System.out.println(l);
	}
}
