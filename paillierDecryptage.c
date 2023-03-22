#include "paillier.h"

void dechiffrer(paillier_pubkey *pubkey, paillier_privkey *privkey, mpz_t message_chiffre, mpz_t message_dechiffre)
{

    // m = (c^(lambda) mod n^2 - 1) / n * mu mod n
    mpz_t r, tmp, n2;


    // Initialisation des variables GMP
    mpz_init(r);
    mpz_init(tmp);
    mpz_init(n2);

    //tmp = (c^(lambda) mod n^2 - 1)
    mpz_mul(n2, pubkey->n,pubkey->n);
    mpz_powm(tmp, message_chiffre, privkey->lambda, n2);
    mpz_sub_ui(tmp, tmp, 1);

    //m = tmp / n * mu mod n
    mpz_div(tmp, tmp, pubkey->n);
    mpz_mul(tmp,tmp,privkey->mu);
    mpz_mod(message_dechiffre, tmp, pubkey->n);
    
    //nettoyage des variables
    mpz_clear(r);
    mpz_clear(tmp);
    mpz_clear(n2);
}


