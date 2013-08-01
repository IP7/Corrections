

public class Test {

	// question 5
	public static void main(String[] args) {
		// creation d'une imprimante canon avec une capacité de 75 pages
		Imprimante imprimante = new Imprimante(75, "canon");
		// on remplit l'imprimante avec 50 pages
		imprimante.remplissage(50);


		// creation d'une cartouche d'une cartouche de 100ml de couleur rouge
		Cartouche cartouche = new Cartouche(100, "red");
		// on remplit une cartouche pleinne avec n'importe quoi
		cartouche.remplissage(30, "black");
	}
}