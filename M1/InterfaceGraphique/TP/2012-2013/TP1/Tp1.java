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
    JPanel	conteneur;
    JButton[]	buttons;
    Ex2(){
	setSize(Tp1.fenetre_x, Tp1.fenetre_y);
	buttons = new JButton[5];
	conteneur = new JPanel();
	for(int i = 0; i < 5; i++){
	    buttons[i] = new JButton(i+"");
	    conteneur.add(buttons[i]);
	    buttons[i].addMouseListener(this);
	}
	add(conteneur);
       	setVisible(true);
    }
    public void mouseClicked(MouseEvent e){
	for(int i = 0 ; i < 5; i++){
	    if(e.getSource() == buttons[i]){
		JOptionPane.showMessageDialog(Tp1.getInstance().getFen(), "Vous avez cliqué sur le bouton " + i);
	    }
	}
    }
    public void mouseEntered(MouseEvent e){}
    public void mouseExited(MouseEvent e){}
    public void mousePressed(MouseEvent e){}
    public void mouseReleased(MouseEvent e){}
}

/* comme l'ex2, seule difference: le layout */ 
class Ex3 extends JPanel implements MouseListener{
    JPanel[]	conteneur;
    JButton[]	buttons;
    Ex3(){
	this.setSize(Tp1.fenetre_x, Tp1.fenetre_y);
	this.setLayout(new BorderLayout());
	buttons = new JButton[5];
	conteneur = new JPanel[5];
	for(int i = 0; i < 5; i++){
	    conteneur[i] = new JPanel();
	    buttons[i] = new JButton(i+"");
	    buttons[i].addMouseListener(this);
	    conteneur[i].add(buttons[i]);
	}
	this.add("North", conteneur[0]);
	this.add("East", conteneur[1]);
	this.add("Center", conteneur[2]);//todo: setAlignementY
	this.add("West", conteneur[3]);
	this.add("South", conteneur[4]);
       	this.setVisible(true);
    }
    public void mouseClicked(MouseEvent e){
	for(int i = 0 ; i < 5; i++){
	    if(e.getSource() == buttons[i]){
		JOptionPane.showMessageDialog(Tp1.getInstance().getFen(), "Vous avez cliqué sur le bouton " + i);
	    }
	}
    }
    public void mouseEntered(MouseEvent e){}
    public void mouseExited(MouseEvent e){}
    public void mousePressed(MouseEvent e){}
    public void mouseReleased(MouseEvent e){}
}

class Ex4 extends JPanel{
    JPanel centre;
    Ex4(){
	this.setSize(Tp1.fenetre_x, Tp1.fenetre_y);
	this.setLayout(new BorderLayout());
	centre = new JPanel(new GridLayout(0, 3, 10, 10));
	for (int i = 1; i <= 10; i++)
	    centre.add(new JButton("Button #" + i));
	this.add("North", new JLabel("Nord"));
	this.add("East", new JLabel("Est"));
	this.add("Center", centre);
	this.add("West", new JLabel("Ouest"));
	this.add("South", new JLabel("Sud"));
	this.setVisible(true);
    }
}

class Ex5 extends JPanel{
    Ex5(){
	this.setSize(Tp1.fenetre_x, Tp1.fenetre_y);
	this.setLayout(new  GridLayout(2, 1));
	Locale locale_FR = new Locale("fr","FR");
	Locale locale_WE = new Locale("we","WE");
	ResourceBundle bundle1 =
	    ResourceBundle.getBundle("Ex5", locale_FR); // on va chercher dans Ex5_fr_FR.properties
	ResourceBundle bundle2 =
	    ResourceBundle.getBundle("Ex5", locale_WE); // idem pour WE
	this.add(new JLabel("Message in " + locale_FR + ": " + bundle1.getString("greeting")));
	this.add(new JLabel("Message in " + locale_WE + ": " + bundle2.getString("greeting")));
	this.setVisible(true);
    }
}


/* Singleton , Ex1 */
public class Tp1 
{
    /* variable générales d'affichage */    
    static volatile	Tp1	instance  = null; 
    static		int	fenetre_x = 779;
    static		int	fenetre_y = 456;
    static		Locale	locale_FR = new Locale("fr", "FR");
    static		Locale	locale_WE = new Locale("we", "WE");
    private		Fenetre f;
    
    public final static Tp1 getInstance()
    {
	if(Tp1.instance == null){
	    synchronized(Tp1.class){
		if(Tp1.instance == null){
		    Tp1.instance = new Tp1();
		}
	    }
	}
	return (Tp1.instance);
    }
    
    private Tp1(){super();}    
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
		    Tp1.getInstance().setFen(new Fenetre());
		    Tp1.getInstance().getFen().setContentPane(new Ex5());
		}
	    });
    }
}

/* Ex6, Ex7 Ex8*/
class Fenetre extends JFrame
{
    int taille_x = Tp1.fenetre_x ;
    int taille_y = Tp1.fenetre_y ;

    private JMenuBar menuBar = new JMenuBar();
    private JMenu fichier = new JMenu("Fichier");
    private JMenu edition = new JMenu("Edition");
    private JMenu aide = new JMenu("Aide");

    private JMenuItem item[];
    Fenetre()
    {
	setTitle("TP1");
	setSize(taille_x, taille_y);
	setLocationRelativeTo(null);
	setResizable(false);
	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	setVisible(true);
	
	item = new JMenuItem[11];
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
	
	for(int i = 0 ; i < 5; i++){
	    fichier.add(item[i]);
	}

	for(int i = 5 ; i < 9; i++){
	    edition.add(item[i]);
	}
	
	aide.add(item[9]);
	aide.add(item[10]);

	fichier.setMnemonic(KeyEvent.VK_F);	
	edition.setMnemonic(KeyEvent.VK_E);
	aide.setMnemonic(KeyEvent.VK_H);
	
	this.menuBar.add(fichier);
	this.menuBar.add(edition);
	this.menuBar.add(aide); // "setHelpMenu() not yet implemented." 
	this.setJMenuBar(menuBar);
    }
}

