#include "paillier.h"

void dechiffrer(paillier_pubkey *pubkey, paillier_privkey *privkey, mpz_t message_chiffre, mpz_t message_dechiffre)
{

    // m = (c^(lambda) mod n^2 - 1) / n * mu mod n
    mpz_t tmp;


    // Initialisation des variables GMP
    mpz_init(tmp);

    //tmp = (c^(lambda) mod n^2 - 1)
    mpz_powm(tmp, message_chiffre, privkey->lambda, pubkey->n2);
    mpz_sub_ui(tmp, tmp, 1);

    //m = tmp / n * mu mod n
    mpz_div(tmp, tmp, pubkey->n);
    mpz_mul(tmp,tmp,privkey->mu);
    mpz_mod(message_dechiffre, tmp, pubkey->n);
    
    //nettoyage des variables
    mpz_clear(tmp);
}


