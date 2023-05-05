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

Objectifs :

Construire un tableau très grand.
Établir une communication entre un client et un serveur.
Communication chiffré.
Il faut pouvoir effectuer une requête sans que le serveur puisse l'identifier.

m_clair => m_chiffré ==========> 
   CLIENT                           SERVEUR



stocké n2 plutôt que g dans la clé publique



Source : 
 - https://www.sciencedirect.com/topics/computer-science/paillier-cryptosystem (pour les images)

 - https://www.theses.fr/2017GREAT092.pdf
