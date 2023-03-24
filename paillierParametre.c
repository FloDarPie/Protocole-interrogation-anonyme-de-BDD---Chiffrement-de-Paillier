#include "paillier.h"

void generer_parametre(mpz_t n, mpz_t n2, mpz_t lambda, unsigned long int seed)
{
    gmp_randstate_t state;
    mpz_t p, q, phi, tmp;
    
    
    // Initialisation des variables GMP
    mpz_init(p);
    mpz_init(q);
    mpz_init(phi);
    mpz_init(tmp);
    
    gmp_randinit_default(state);
    if(seed != 1)
    {
        gmp_randseed_ui(state, seed);
    }
    
    
    // Génération de deux nombres premiers aléatoires de 1024 bits
    mpz_urandomb(p, state, 1024);    mpz_nextprime(p, p);
    mpz_urandomb(q, state, 1024);    mpz_nextprime(q, q);
    
    // Calcul de n = p * q
    mpz_mul(n, p, q);
    
    // Calcul de lambda = lcm(p-1, q-1)     = (p-1)*(q-1)/gcd(p-1, q-1)
    mpz_sub_ui(tmp, p, 1);
    mpz_sub_ui(phi, q, 1);
    mpz_lcm(lambda, tmp, phi);  //calcul du ppcm

    //affectation de n2 = n * n
    mpz_mul(n2, n, n);

    
    // Libération de la mémoire utilisée par les variables GMP
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(phi);
    mpz_clear(tmp);
    gmp_randclear(state);
}

