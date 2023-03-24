#include "paillier.h"


void chiffrer(paillier_pubkey *pubkey, mpz_t message_clair, mpz_t message_chiffre)
{
    gmp_randstate_t graine;
    mpz_t r, tmp, rn;


    // Initialisation des variables GMP
    mpz_init(r);
    mpz_init(tmp);
    mpz_init(rn);

    gmp_randinit_default(graine);
    if(pubkey->seed != 1)
    {
        gmp_randseed_ui(graine, pubkey->seed);
    }
    
    

    // Choisir un nombre aléatoire r ∈ Zn*
    mpz_urandomb(r, graine, mpz_sizeinbase(pubkey->n, 10));

    
    //Calculer le chiffré c = (1 + n * m) * r^n mod n^2
    mpz_mul(tmp, pubkey->n, message_clair);
    mpz_add_ui(tmp,tmp,1);
    
    mpz_powm(rn, r, pubkey->n, pubkey->n2);
    mpz_mul(tmp, tmp, rn);
    mpz_mod(message_chiffre, tmp, pubkey->n2);
    
    //nettoyage des variables
    mpz_clear(r);
    mpz_clear(tmp);
    mpz_clear(rn);
    gmp_randclear(graine);
}
