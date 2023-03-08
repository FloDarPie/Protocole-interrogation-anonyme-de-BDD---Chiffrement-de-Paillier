#include "paillier.h"

// Génère les clés de cryptage en utilisant les entiers n et g
void generer_cle(paillier_pubkey *pubkey, paillier_privkey *privkey, mpz_t n, mpz_t g, mpz_t lambda, mpz_t mu) {
    
    //on initialise les cles
    mpz_inits(pubkey->n, pubkey->g, NULL);
    mpz_inits(privkey->lambda, privkey->mu, NULL);

    // Affecter une valeur à n
    mpz_set(pubkey->n, n); 

    // Calcul de g^lambda mod n^2
    mpz_t g_lambda_mod_n_square;
    mpz_init(g_lambda_mod_n_square);
    mpz_powm_sec(g_lambda_mod_n_square, g, lambda, pubkey->n);
    mpz_powm_ui(g, g, 2, pubkey->n);

    // Calcul de mu = L(g^lambda mod n^2)^-1 mod n
    mpz_t L;
    mpz_inits(L, mu, NULL);
    mpz_sub_ui(L, g_lambda_mod_n_square, 1);
    mpz_divexact(L, L, pubkey->n);
    mpz_invert(mu, L, pubkey->n);

    // Stockage des clés publiques et privées
    mpz_set(pubkey->g, g);
    mpz_set(privkey->lambda, lambda);
    mpz_set(privkey->mu, mu);

    // Libération de la mémoire
    mpz_clears(g_lambda_mod_n_square, L, NULL);
}
