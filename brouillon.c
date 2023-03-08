#include <gmp.h>

// Structure de données pour stocker la clé publique
typedef struct {
    mpz_t n;
    mpz_t g;
} paillier_pubkey;

// Structure de données pour stocker la clé privée
typedef struct {
    mpz_t lambda;
    mpz_t mu;
} paillier_privkey;

// Génère les clés de cryptage en utilisant les entiers n et g
void generer_cle(paillier_pubkey *pubkey, paillier_privkey *privkey, const mpz_t n, const mpz_t g) {
    // Initialisation des nombres premiers p et q
    mpz_t p, q;
    mpz_inits(p, q, NULL);

    // Génération des nombres premiers p et q de grande taille
    mpz_urandomb(p, state, 1024); // Choisir la taille des nombres premiers selon vos besoins
    mpz_urandomb(q, state, 1024);
    mpz_nextprime(p, p);
    mpz_nextprime(q, q);

    // Calcul du produit n = p * q
    mpz_mul(pubkey->n, p, q);

    // Calcul de lambda = lcm(p-1, q-1)
    mpz_t p_minus_1, q_minus_1, lambda;
    mpz_inits(p_minus_1, q_minus_1, lambda, NULL);
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_lcm(lambda, p_minus_1, q_minus_1);

    // Calcul de g^lambda mod n^2
    mpz_t g_lambda_mod_n_square;
    mpz_init(g_lambda_mod_n_square);
    mpz_powm_sec(g_lambda_mod_n_square, g, lambda, pubkey->n);
    mpz_powm_ui(g, g, 2, pubkey->n);

    // Calcul de mu = L(g^lambda mod n^2)^-1 mod n
    mpz_t L, mu;
    mpz_inits(L, mu, NULL);
    mpz_sub_ui(L, g_lambda_mod_n_square, 1);
    mpz_divexact(L, L, pubkey->n);
    mpz_invert(mu, L, pubkey->n);

    // Stockage des clés publiques et privées
    mpz_set(pubkey->g, g);
    mpz_set(privkey->lambda, lambda);
    mpz_set(privkey->mu, mu);

    // Libération de la mémoire
    mpz_clears(p, q, p_minus_1, q_minus_1, lambda, g_lambda_mod_n_square, L, NULL);
}
