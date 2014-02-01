/* Solution  XPATH*/

xpath //FILM/TITRE/text()

xpath //FILM[GENRE='Horreur']/TITRE/text()

xpath //FILM[TITRE="Alien"]/RESUME/text()

xpath //FILM/ROLES/ROLE[NOM="Stewart" and PRENOM="James"]/../../TITRE/text()

xpath //FILM/ROLES/ROLE[PRENOM="Clint"]/./NOM/text()

xpath //FILM[TITRE="La mort aux trousses"]/ROLES/ROLE[1]/PRENOM/text()

xpath //FILM[TITRE="La mort aux trousses"]/ROLES/ROLE[2]/*/text()

xpath //FILM/ROLES/ROLE[PRENOM="Clint"]/INTITULE/text()

xpath //FILM/ROLES/ROLE[PRENOM="Clint"]/../../TITRE/text()

xpath //FILM/ROLES[ROLE[NOM="Hackman" and PRENOM="Gene"] and ROLE[PRENOM="Clint"]]/../TITRE/text()

xpath //FILM[RESUME]/TITRE/text()

xpath //FILM[TITRE="Alien"]/MES/@idref

xpath //FILM[TITRE="Titanic"]/ROLES/ROLE[PRENOM="Kate" and NOM="Winslet"]/./INTITULE/text()

xpath //FILM[last()]/TITRE/text()

xpath //FILM[TITRE="Titanic"]/preceding-sibling::FILM[1]/TITRE/text()

xpath //FILM[contains(TITRE,"K")]/TITRE/text()

xpath //FILM[count(ROLES/*)=3]/TITRE/text()

xpath //*[contains(name(),"IN")]
