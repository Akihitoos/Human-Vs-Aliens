# Human-Vs-Aliens

## Français

---

### Les Arguments

>./HumanVsAliens [modeDeJeu] [Difficulté]

Le premier argument est obligatoire, le deuxième ne l'est pas. Voici comment les utiliser :

- modeDeJeu : Il peut valoir 0 ou 1. 0 pour le multijoueur, 1 pour le solo.

- Difficulté : Il peut valoir entre 1 et 3. À entrer uniquement pour la version solo.

---

### Les bibliothèques externes utilisées

- stdlib.h, stdio.h, string.h, time.h
-> pour les allocations, la gestion des inputs, la gestion des chaines de caractères, et du temps pour le score

- SDL
-> Pour la gestion du rendu graphique

---

### Les différents mode de jeu

Deux modes de jeux sont disponibles : Le multijoueur et le solo.
Le mode multijoueur met à égalité les deux joueurs en terme de revenus.

Tandis que le mode solo donne la main à l'IA pour la gestion des Aliens.
En mode Solo, le choix de la difficulté influe sur les revenus des aliens : plus la difficulté augmente, plus les aliens seront nombreux.

---

### Les contrôles

Pour l'humain :

- Le changement de rangée s'effectue grâce à "z" et "s", "z" montant le curseur, "s" le descendant.

- Le changement de position dans la rangée s'effectue grâce à "q" et "d", "q" déplace le curseur à gauche, "d" le déplace à droite.

- Le changement de séléction dans la boutique s'effectue grâce à "a" et "e", "a" déplace le curseur à gauche, "e" le déplace à droite.

- La pose d'humain s'effectue grâce à "Espace". L'humain choisi sera placé selon les curseurs précédents, et son type sera celui choisi dans la boutique, si le joueur dispose des fonds néscessaires.

Pour l'alien :

- Le changement de rangée s'effectue respectivement avec "flèche du haut" et "flèche du bas". "flèche du haut" déplace le curseur vers le haut, "flèche du bas" le déplace vers le bas.

- Le changement de séléction dans la boutique s'effectue avec "flèche de gauche" et "flèche de droite".

- La pose d'alien s'effectue grâce à "Entrée" (celui au dessus de shift). L'alien choisi sera placé selon le curseur précédent, et son type sera celui choisi dans la boutique, si le joueur dispose des fonds néscessaires.
