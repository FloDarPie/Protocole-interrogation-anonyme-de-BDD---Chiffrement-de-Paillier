#include "paillier.h"


void chiffrer(paillier_pubkey *pubkey, mpz_t message_clair, mpz_t message_chiffre, bool test)
{
    gmp_randstate_t graine;
    mpz_t r, tmp, n2, rn;


    // Initialisation des variables GMP
    mpz_init(r);
    mpz_init(tmp);
    mpz_init(n2);
    mpz_init(rn);

    // Initialisation de l'état aléatoire --- option, avec l'horloge
    gmp_randinit_default(graine);
    //=================================
    if (!test)
    {
    unsigned long seed = time(NULL); // utilise l'horloge système comme graine
    gmp_randseed_ui(graine, seed);
    }
    //=====================

    // Choisir un nombre aléatoire r ∈ Zn*
    mpz_urandomb(r, graine, mpz_sizeinbase(pubkey->n, 10));

    
    //Calculer le chiffré c = (g * m) * r^n mod n^2
    mpz_mul(tmp, pubkey->g, message_clair);
    mpz_mul(n2, pubkey->n,pubkey->n);
    mpz_powm(rn, r, pubkey->n, n2);
    mpz_mul(tmp, tmp, rn);
    mpz_mod(message_chiffre, tmp, n2);
    
    //nettoyage des variables
    mpz_clear(r);
    mpz_clear(tmp);
    mpz_clear(n2);
    mpz_clear(rn);
    gmp_randclear(graine);
}
