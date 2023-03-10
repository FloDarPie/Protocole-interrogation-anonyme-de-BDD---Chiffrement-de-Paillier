#include "paillier.h"

// Génère les clés de cryptage en utilisant les entiers n et g
void generer_cle(paillier_pubkey *pubkey, paillier_privkey *privkey, mpz_t n, mpz_t g, mpz_t lambda, mpz_t mu) {
    
    //on initialise les cles
    mpz_inits(pubkey->n, pubkey->g, NULL);
    mpz_inits(privkey->lambda, privkey->mu, NULL);



    //on trouve aussi : mu = ([
    //                          [g^lambda modulo n^2]
    //                        -1 ] / n )^-1 mod n
    //
    //mu = lambda^-1 mod n
    mpz_invert(mu, lambda, n);


    // Stockage des clés publiques et privées
    mpz_set(pubkey->n, n);
    mpz_set(pubkey->g, g);
    mpz_set(privkey->lambda, lambda);
    mpz_set(privkey->mu, mu);

}
