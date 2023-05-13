# Protocole-interrogation-anonyme-de-BDD---Chiffrement-de-Paillier
For the TER in M1 Cryptography Bordeaux.


Voici le protocole d'implémentation :

1. Génération des clés
   a. Choisir deux nombres premiers p et q de taille égale <br>
   b. Calculer n = p * q et lambda = ppcm(p-1, q-1)<br>
   c. On fixe g = n+1         // est random à la base<br>
   d. Calculer mu = lambda^-1 mod n<br>
   e. La clé publique est (n, g), la clé privée est (lambda, mu)

2. Chiffrement
   a. Soit m un message à chiffrer, m ∈ Zn<br>
   b. Choisir un nombre aléatoire r ∈ Zn*<br>
   c. Calculer le chiffré c = (1 + n * m) * r^n mod n^2         // c'est g^m à la base

3. Déchiffrement
   a. Soit c le chiffré à déchiffrer<br>
   b. Calculer le déchiffré m = (c^(lambda) mod n^2 - 1) / n * mu mod n


Execution du test_paillier :<br>
compilation  : gcc paillierDecryptage.c paillierEncryptage.c paillierParametre.c paillierCles.c test_paillier.c -o test -lgmp<br>
execution : ./test <br>

Execution des protocole :<br>
compilation : gcc affichage.c paillierDecryptage.c paillierEncryptage.c paillierParametre.c paillierCles.c protocole.c -o protocole -lgmp<br>

execution : exemple ./protocole 10 2 3 0  lance le protocole 1 avec un tableau de taille 10 de dimmension 2 avec comme case 3 <br>

argument 1 :taille du tableau <br>
argument 2 :dimmension du tableau <br>
argument 3 :la case à chercher <br>
argument 4 :protocole utilisé<br>


