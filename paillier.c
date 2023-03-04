#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
#include "paillier_gmp.h"

#define KEYGEN_ROUNDS 32

void paillier_keygen(paillier_pubkey *pub, paillier_privkey *priv, int keysize)
{
    gmp_randstate_t state;
    mpz_t p, q, p_minus_1, q_minus_1, p_minus_1_over_lambda, q_minus_1_over_lambda, phi_n, g, nsquare;
    mpz_inits(p, q, p_minus_1, q_minus_1, p_minus_1_over_lambda, q_minus_1_over_lambda, phi_n, g, nsquare, NULL);

    // Initialisation du générateur de nombres aléatoires
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    // Génération de deux nombres premiers p et q
    mpz_urandomb(p, state, keysize/2);
    mpz_urandomb(q, state, keysize/2);
    mpz_nextprime(p, p);
    mpz_nextprime(q, q);

    // Calcul de n = p*q
    mpz_mul(priv->n, p, q);
    mpz_mul(pub->n, p, q);

    // Calcul de lambda = lcm(p-1, q-1) = (p-1)*(q-1)/gcd(p-1, q-1)
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_lcm(phi_n, p_minus_1, q_minus_1);
    mpz_invert(priv->lambda, phi_n, pub->n);

    // Calcul de nsquare = n^2
    mpz_mul(nsquare, pub->n, pub->n);

    // Calcul d'un générateur g dans Z*_{n^2}
    while (1) {
        mpz_urandomm(g, state, nsquare);
        mpz_powm(priv->mu, g, phi_n, nsquare);
        mpz_sub_ui(priv->mu, priv->mu, 1);
        mpz_divexact(priv->mu, priv->
