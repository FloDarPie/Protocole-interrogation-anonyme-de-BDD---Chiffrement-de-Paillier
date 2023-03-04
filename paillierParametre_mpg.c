#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gmp.h>

const int BIT_LENGTH = 1024;

void generate_paillier_params(mpz_t n, mpz_t g, mpz_t l, mpz_t mu)
{
    // Initialise le générateur de nombres aléatoires
    srand(time(NULL));

    // Génère deux nombres premiers aléatoires p et q de taille BIT_LENGTH / 2 bits
    mpz_t p, q;
    mpz_inits(p, q, NULL);
    mpz_tdiv_q_ui(p, mpz_urandomb(NULL, BIT_LENGTH/2), 2);
    mpz_tdiv_q_ui(q, mpz_urandomb(NULL, BIT_LENGTH/2), 2);
    while (!mpz_probab_prime_p(p, 80) || !mpz_probab_prime_p(q, 80)) {
        mpz_tdiv_q_ui(p, mpz_urandomb(NULL, BIT_LENGTH/2), 2);
        mpz_tdiv_q_ui(q, mpz_urandomb(NULL, BIT_LENGTH/2), 2);
    }

    // Calcule n = p * q et lambda = lcm(p-1, q-1)
    mpz_mul(n, p, q);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_lcm(l, p, q);

    // Génère un entier aléatoire g tel que g^n mod n^2 = 1
    mpz_t gg, modn2;
    mpz_inits(gg, modn2, NULL);
    mpz_mul(modn2, n, n);
    while (1) {
        mpz_urandomm(gg, NULL, modn2);
        if (mpz_gcd(gg, modn2) == 1) {
            mpz_powm(l, gg, l, modn2);
            if (mpz_cmp_ui(l, 1) == 0) {
                mpz_set(g, gg);
                break;
            }
        }
    }

    // Calcule mu = lcm(p^2, q^2)^-1 mod lambda
    mpz_t pp, qq, lcm;
    mpz_inits(pp, qq, lcm, NULL);
    mpz_pow_ui(pp, p, 2);
    mpz_pow_ui(qq, q, 2);
    mpz_lcm(lcm, pp, qq);
    mpz_invert(mu, lcm, l);
}

int main()
{
    mpz_t n, g, l, mu;
    mpz_inits(n, g, l, mu, NULL);
    generate_paillier_params(n, g, l, mu);
    gmp_printf("Public key: (n, g) = (%Zd, %Zd)\n", n, g);
    gmp_printf("Private key: (lambda, mu) = (%Zd, %Zd)\n", l, mu);
    return 0;
}
