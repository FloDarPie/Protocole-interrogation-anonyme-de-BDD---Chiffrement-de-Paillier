# Protocole-interrogation-anonyme-de-BDD---Chiffrement-de-Paillier
For the TER in M1 Cryptography Bordeaux.


This is how it's implemented :

1. Génération des clés
   a. Choisir deux nombres premiers p et q de taille égale
   b. Calculer n = p * q et lambda = ppcm(p-1, q-1)
   c. On fixe g = n+1
   d. Calculer mu = lambda^-1 mod n
   e. La clé publique est (n, g), la clé privée est (lambda, mu)

2. Chiffrement
   a. Soit m un message à chiffrer, m ∈ Zn
   b. Choisir un nombre aléatoire r ∈ Zn*
   c. Calculer le chiffré c = (g * m) * r^n mod n^2

3. Déchiffrement
   a. Soit c le chiffré à déchiffrer
   b. Calculer le déchiffré m = (c^(lambda) mod n^2 - 1) / n * mu mod n

 -- inv(a,n) désigne l'inverse modulaire de 'a' modulo 'n'

Source : https://www.sciencedirect.com/topics/computer-science/paillier-cryptosystem (pour les images)
