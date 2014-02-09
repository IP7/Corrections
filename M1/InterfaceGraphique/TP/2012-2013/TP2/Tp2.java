import java.util.*;
import java.text.*;
import javax.swing.*;
import java.awt.event.MouseListener;     

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.awt.event.KeyEvent;     
import java.awt.event.MouseEvent;    
import java.awt.*;

class Ex2 extends JPanel implements MouseListener{
	JButton quitter;
	JPanel conteneur;
	Ex2(){
		setSize(Tp2.fenetre_x, Tp2.fenetre_y);
		quitter = new JButton("Quitter");
		conteneur = new JPanel();
		conteneur.add(quitter);
		quitter.addMouseListener(this);
		add(conteneur);
		setVisible(true);	
	}
	public void mouseClicked(MouseEvent e){
		if(e.getSource() == quitter){
			System.out.println("Depuis le bouton"); /*Ex3*/
			System.exit(0);
		}
	}
	public void mouseEntered(MouseEvent e){}
	public void mouseExited(MouseEvent e){}
	public void mousePressed(MouseEvent e){}
	public void mouseReleased(MouseEvent e){}

}

/*Ex4 & 5*/
class Ex4 extends JPanel implements MouseListener{
	JButton plus, moins;
	int i = 0;
	JLabel value;
	JPanel conteneur;
	JPanel conteneur_bar;
	JProgressBar bar;
	Ex4(){
		setSize(Tp2.fenetre_x, Tp2.fenetre_y);
		plus  = new JButton("+5");
		moins = new JButton("-5");
		value = new JLabel("0");
		conteneur = new JPanel();
		conteneur_bar = new JPanel();
		bar = new JProgressBar();
		conteneur.add(plus);
		conteneur.add(value);
		conteneur.add(moins);
		conteneur_bar.add(bar);
		plus.addMouseListener(this);
		moins.addMouseListener(this);
		add(conteneur);
		add(conteneur_bar);
		setVisible(true);	
	}
	public void mouseClicked(MouseEvent e){
		if(e.getSource() == plus && i < 100){
			i += 5;
		} 
		else if (e.getSource() == moins && i > 0){
			i-= 5;
		}
		value.setText(i+"");
		bar.setValue(i);
	}
	public void mouseEntered(MouseEvent e){}
	public void mouseExited(MouseEvent e){}
	public void mousePressed(MouseEvent e){}
	public void mouseReleased(MouseEvent e){}
}

/*Ex6*/


/* Singleton - TP1*/
public class Tp2
{
	/* variable générales d'affichage */    
	static volatile	Tp2	instance  = null; 
	static		int	fenetre_x = 779;
	static		int	fenetre_y = 456;
	static		Locale	locale_FR = new Locale("fr", "FR");
	static		Locale	locale_WE = new Locale("we", "WE");
	private		Fenetre f;

	public final static Tp2 getInstance()
	{
		if(Tp2.instance == null){
			synchronized(Tp2.class){
				if(Tp2.instance == null){
					Tp2.instance = new Tp2();
				}
			}
		}
		return (Tp2.instance);
	}
	private Tp2(){super();}    
	public Fenetre getFen(){return (this.f);}
	public void setFen(Fenetre newf){this.f = newf;}

	public static void main(String[] args){

		javax.swing.SwingUtilities.invokeLater(new Runnable(){
			public void run(){
				try{
					for(UIManager.LookAndFeelInfo info: UIManager.getInstalledLookAndFeels()){
						if("Nimbus".equals(info.getName())){
							UIManager.setLookAndFeel(info.getClassName());
							break;
						}
					}
				}
				catch(Exception e){
					e.printStackTrace();
				}
				Tp2.getInstance().setFen(new Fenetre(6));
				//Tp2.getInstance().getFen().setContentPane(new Ex6());
			}
		});
	}
}

/* TP1 */
class Fenetre extends JFrame implements ActionListener{
	int taille_x = Tp2.fenetre_x ;
	int taille_y = Tp2.fenetre_y ;
	JPanel panel_ex6;
	LinkedList<JButton> liste_boutons = new LinkedList<JButton>();
	int exo;
	private JMenuBar menuBar = new JMenuBar();
	private JMenu fichier = new JMenu("Fichier");
	private JMenu edition = new JMenu("Edition");
	private JMenu boutons = new JMenu("Boutons");
	private JMenu aide = new JMenu("Aide");
	private JMenuItem item[];
	JMenuItem getBouton(int i){
		return item[i];
	}

	Fenetre(int exo){
		this.exo = exo;
		setTitle("TP1");
		setSize(taille_x, taille_y);
		setLocationRelativeTo(null);
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);

		item = new JMenuItem[13];
		item[0] = new JMenuItem("Nouveau", KeyEvent.VK_N);
		item[1] = new JMenuItem("Ouvrir", KeyEvent.VK_O);
		item[2] = new JMenuItem("Enregistrer", KeyEvent.VK_S);
		item[3] = new JMenuItem("Enregistrer sous ...", KeyEvent.VK_E);
		item[4] = new JMenuItem("Quitter", KeyEvent.VK_Q);
		item[5] = new JMenuItem("Annuler", KeyEvent.VK_Z);
		item[6] = new JMenuItem("Rétablir", KeyEvent.VK_Y);
		item[7] = new JMenuItem("Couper", KeyEvent.VK_X);
		item[8] = new JMenuItem("Copier", KeyEvent.VK_C);
		item[9] = new JMenuItem("Manuel", KeyEvent.VK_M);
		item[10] = new JMenuItem("Tutoriel", KeyEvent.VK_T);
		item[11] = new JMenuItem("Ajouter", KeyEvent.VK_T);
		item[12] = new JMenuItem("Enlever", KeyEvent.VK_T);

		for(int i = 0 ; i < 5; i++){
			fichier.add(item[i]);
		}

		for(int i = 5 ; i < 9; i++){
			edition.add(item[i]);
		}

		aide.add(item[9]);
		aide.add(item[10]);

		boutons.add(item[11]);
		boutons.add(item[12]);

		fichier.setMnemonic(KeyEvent.VK_F);	
		aide.setMnemonic(KeyEvent.VK_H);

		for(int i = 0; i < 13; i ++){
			item[i].addActionListener(this);
		}
		this.menuBar.add(fichier);
		this.menuBar.add(edition);
		this.menuBar.add(boutons);
		this.menuBar.add(aide); // "setHelpMenu() not yet implemented." 
		this.setJMenuBar(menuBar);

		switch(exo){
		case 2: setContentPane(new Ex2()); break;
		case 4: case 5 : setContentPane(new Ex2()); break;
		case 6: setContentPane(new Ex6()); break;
		default: System.out.println("exo existe pas");
		}
	}

	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == item[11]){
			Tp2.getInstance().getFen().getContentPane().add(new JButton("button"));
		} else if(e.getSource() == item[12]){
			
		}
	}
}