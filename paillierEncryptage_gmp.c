#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

void paillier_encrypt(mpz_t c, const mpz_t m, const mpz_t n, const mpz_t r)
{
    mpz_t n_squared, tmp;
    mpz_inits(n_squared, tmp, NULL);

    // Calcul de n^2
    mpz_mul(n_squared, n, n);

    // c = (1 + m * n) * r^2 mod n^2
    mpz_mul(tmp, m, n);
    mpz_add_ui(tmp, tmp, 1);
    mpz_powm_ui(c, r, 2, n_squared);
    mpz_mul(c, c, tmp);
    mpz_mod(c, c, n_squared);

    // Libération de la mémoire
    mpz_clears(n_squared, tmp, NULL);
}

int main()
{
    // Initialisation des variables
    mpz_t p, q, n, r, m, c;
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_inits(p, q, n, r, m, c, NULL);

    // Génération de p et q aléatoires
    gmp_randseed(time(NULL));
    mpz_urandomb(p, state, 512);
    mpz_urandomb(q, state, 512);

    // Calcul de n = p * q
    mpz_mul(n, p, q);

    // Choisir un nombre aléatoire r tel que 0 ≤ r < n^2 et pgcd(r, n) = 1.
    do {
        mpz_urandomm(r, state, n);
    } while (mpz_gcd(r, n) != 1);

    // Chiffrer le message m
    mpz_set_ui(m, 42); // Remplacer 42 par le message à chiffrer
    paillier_encrypt(c, m, n, r);

    // Afficher le résultat
    gmp_printf("Message chiffré : %Zd\n", c);

    // Libération de la mémoire
    mpz_clears(p, q, n, r, m, c, NULL);
    gmp_randclear(state);

    return 0;
}
