import java.util.*;
import java.text.*;
import java.awt.Color;
import java.awt.Container;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.ButtonGroup;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.UIManager;

public class Ex6 extends JFrame implements ActionListener{

    public Ex6(){
	setTitle("TP1 - Ex 6, 7, 8, 9");
	setSize(taille_x, taille_y);
	setLocationRelativeTo(null);
	setResizable(false);
	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

	//ImageIcon icone_add = UIManager.getIcon("OptionPane.ErrorIcon");
		
	Container contenu = getContentPane();
		
	item = new JMenuItem[15];
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
	item[11] = new JMenuItem("Ajouter", UIManager.getIcon("FileView.fileIcon"));
	item[12] = new JMenuItem("Enlever", UIManager.getIcon("OptionPane.errorIcon"));
	item[13] = new JRadioButtonMenuItem("Français");//new JMenuItem("English");
	item[14] = new JRadioButtonMenuItem("English");//new JMenuItem("Français");

	item[13].setSelected(true);
	for(int i = 0 ; i < 5; i++){
	    fichier.add(item[i]);
	}

	for(int i = 5 ; i < 9; i++){
	    edition.add(item[i]);
	}

	ButtonGroup group = new ButtonGroup();
	group.add(item[13]);
	group.add(item[14]);
		
	langue.add(item[13]);
	langue.add(item[14]);

	aide.add(item[9]);
	aide.add(item[10]);

	menu_boutons.add(item[11]);
	menu_boutons.add(item[12]);

	fichier.setMnemonic(KeyEvent.VK_F);	
	aide.setMnemonic(KeyEvent.VK_H);

	for(int i = 0; i < 15; i ++){
	    item[i].addActionListener(this);
	}

	this.menuBar.add(fichier);
	this.menuBar.add(edition);
	this.menuBar.add(menu_boutons);
	this.menuBar.add(langue);
	this.menuBar.add(aide); // "setHelpMenu() not yet implemented." 
	this.setJMenuBar(menuBar);		
		
	creation = new JButton("Creation");
	contenu.add(creation, "North");
	creation.addActionListener(this);
		
	suppression = new JButton("Suppression");
	contenu.add(suppression, "South");
	suppression.addActionListener(this);
		
	pan = new JPanel();
	contenu.add(pan);
	boutons = new LinkedList<JButton>();
	boutSelec = new LinkedList<Boolean>();
	setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
	Object source = e.getSource();
	if(source == item[11] || source == creation){
	    boutons.add(new JButton("Bouton " + (boutons.size())));
	    boutons.get(boutons.size()-1).setBackground(Color.yellow);
	    boutSelec.add(boutons.size()-1, false);
	    pan.add(boutons.get(boutons.size()-1));
	    boutons.get(boutons.size()-1).addActionListener(this);
	    pan.validate();
	}
	else if(source == item[12] || source == suppression){
	    for(int i = 0; i < boutons.size(); i++){
		if(boutSelec.get(i)){
		    pan.remove(boutons.get(i));
		    pan.validate();
		}
	    }
	    pan.validate();
	}
	else if(source == item[13] && !fr_select){
	    creation.setText(bundle1.getString("Creation"));
	    suppression.setText(bundle1.getString("Suppression"));
	    fr_select = true;
	}
	else if(source == item[14] && fr_select){
	    creation.setText(bundle2.getString("Creation"));
	    suppression.setText(bundle2.getString("Suppression"));
	    fr_select = false;
	}
		
	for(int i = 0; i < boutons.size(); i++){
	    if(source == boutons.get(i)){
		if(boutSelec.get(i)){
		    boutSelec.set(i, false);
		    boutons.get(i).setBackground(Color.yellow);
		}
		else{
		    boutSelec.set(i, true);
		    boutons.get(i).setBackground(Color.red);
		}
	    }
	}
    }
	
    int	taille_x = 779;
    int	taille_y = 456;
	
    private JButton creation, suppression;
    private JPanel pan;
    private LinkedList<JButton> boutons;
    private LinkedList<Boolean> boutSelec;
	
    private JMenuBar menuBar = new JMenuBar();
    private JMenu fichier = new JMenu("Fichier");
    private JMenu edition = new JMenu("Edition");
    private JMenu menu_boutons = new JMenu("Boutons");
    private JMenu langue = new JMenu("Langue");
    private JMenu aide = new JMenu("Aide");
    private JMenuItem item[];
    private boolean fr_select = true;
       
    private ResourceBundle bundle1 = ResourceBundle.getBundle("Ex6", new Locale("fr", "FR")); 
    private ResourceBundle bundle2 = ResourceBundle.getBundle("Ex6", new Locale("en", "EN"));

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
		    Ex6 f = new Ex6();
		}
	    });
    }
}

