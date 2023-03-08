# Protocole-interrogation-anonyme-de-BDD---Chiffrement-de-Paillier
For the TER in M1 Cryptography Bordeaux.


This is how it's implemented :

1. Génération des clés
   a. Choisir deux nombres premiers p et q de taille égale
   b. Calculer n = p * q et lambda = ppcm(p-1, q-1)
   c. Choisir un entier g tel que g est un résidu quadratique modulo n^2
   d. Calculer mu = inv(ppcm(puissance(g, lambda) - 1, n), n)
   e. La clé publique est (n, g), la clé privée est (lambda, mu)

2. Chiffrement
   a. Soit m un message à chiffrer, m ∈ Zn
   b. Choisir un nombre aléatoire r ∈ Zn*
   c. Calculer c = g^m * r^n mod n^2
   d. Le chiffré est c

3. Déchiffrement
   a. Soit c le chiffré à déchiffrer
   b. Calculer L(c^(lambda) mod n^2) = (c^(lambda) mod n^2 - 1) / n * mu mod n
   c. Le message déchiffré est m = L(c^(lambda) mod n^2) * inv(r, n) mod n

 -- inv(a,n) désigne l'inverse modulaire de 'a' modulo 'n'

