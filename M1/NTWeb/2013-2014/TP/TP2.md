# NTWeb - TP 2 (2014)

Dans la suite, on suppose que le fichier de données s’appelle `photos.txt`.

## Exercice 1

1. `cut -f2 < photos.txt`
2. `cut -f2 < photos.txt | head -20`
3. `cut -f2 < photos.txt | head -20 | sort | uniq -c` (on pourra ajouter
   un filtre `sort -r` pour lister les valeurs par nombre décroissant
   d’ocurrences)
4. `cut -f2 < photos.txt | sort | uniq -c`

## Exercice 2

1. `cut -f2 < photos.txt | sort | uniq -c | awk '{print $2 "\t" $1}' > fic`
2. `cut -f2 < fic | sort | uniq -c | awk '{print $2 "\t" $1}' > fic2`

## Exercice 3

Les commande suivantes doivent être exécutées dans Gnuplot

1. `plot 'fic'`
2. `set logscale xy; plot 'fic'`
3. `set terminal postscript; set output 'out.ps'; plot 'fic'` puis dans le
   shell `pstopdf out.ps` si on souhaite avoir un PDF plutôt qu’un fichier
   Postscript.
