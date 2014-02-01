DROP TABLE IF EXISTS note;
DROP TABLE IF EXISTS enseigne;
DROP TABLE IF EXISTS etudiant;

CREATE TABLE etudiant (
   numEtudiant INT PRIMARY KEY,
   nom VARCHAR(40) NOT NULL,
   prenom VARCHAR(40) NOT NULL,
   login VARCHAR(20) NOT NULL ,
   UNIQUE (nom, prenom),
   UNIQUE (login)
);

CREATE TABLE enseigne (
   login VARCHAR(20),
   codeMatiere VARCHAR(20),
   PRIMARY KEY (login, codeMatiere)
);

CREATE TABLE note (
   codeMatiere VARCHAR(20),
   numEtudiant INT REFERENCES etudiant,
   note INT CHECK ((note >=0) AND (note <=20)),
   PRIMARY KEY (codeMatiere, numEtudiant)
);

INSERT INTO etudiant(numEtudiant, nom, prenom, login)
VALUES
  (11111, 'Ball', 'Lucille', 'BALL'),
  (22222, 'Arnaz', 'Desi', 'ARNAZ'),
  (33333, 'Marx', 'Groucho', 'MARX'),
  (44444, 'Abbott', '', 'ABBOTT'),
  (55555, 'Costello', '', 'COSTELLO')
;

INSERT INTO enseigne (login, codeMatiere)
VALUES
  ('Zielonka', 'BDA'),
  ('Laroussinie', 'Algo')
;

INSERT INTO note (codeMatiere, numEtudiant )
VALUES
  ('BDA', 11111),
  ('BDA', 22222),
  ('BDA', 33333),
  ('Algo', 11111),
  ('Algo', 33333),
  ('Algo', 44444),
  ('Algo', 55555)
;
