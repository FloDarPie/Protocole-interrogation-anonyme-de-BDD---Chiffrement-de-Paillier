#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void paillier_decrypt(mpz_t m, const mpz_t c, const mpz_t p, const mpz_t q)
{
    mpz_t p_minus_1, q_minus_1, lambda, tmp, g, mu;
    mpz_inits(p_minus_1, q_minus_1, lambda, tmp, g, mu, NULL);

    // Calcul de lambda = ppcm(p-1, q-1)
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_lcm(lambda, p_minus_1, q_minus_1);

    // Calcul du symbole de Legendre de r mod n
    mpz_powm_ui(g, c, lambda, mpz_mul(p_minus_1, p_minus_1, q_minus_1));
    mpz_sub_ui(g, g, 1);
    mpz_divexact(tmp, g, p);
    mpz_divexact(mu, g, q);
    mpz_invert(tmp, tmp, q);
    mpz_invert(mu, mu, p);
    mpz_mul(mu, mu, p);
    mpz_mul(tmp, tmp, q);
    mpz_add(m, tmp, mu);
    mpz_mod(m, m, mpz_mul(p, q, NULL));

    // Libération de la mémoire
    mpz_clears(p_minus_1, q_minus_1, lambda, tmp, g, mu, NULL);
}

int main()
{
    // Initialisation des variables
    mpz_t p, q, n, r, m, c;
    mpz_inits(p, q, n, r, m, c, NULL);

    // Remplacer les valeurs de p, q, n et r par celles utilisées pour le chiffrement
    mpz_set_str(p, "85330815622451187222705070757766568159510514746908935617389527643205486989331", 10);
    mpz_set_str(q, "122639111174481437278139447855132031858803969960304395152400418513521183648371", 10);
    mpz_mul(n, p, q);
    mpz_set_str(r, "69584063589494410628357870540993458281791201600330473862161023472756862496356", 10);

    // Déchiffrer le message c
    mpz_set_str(c, "120412728063243572712346020199130428999279985789671864424875069675842204100223120538569506661225630028908605082049688583460982007271531771955139564631066174208363418171770666183402755434027529771850186007345659499315338138848366004537838911299081727672731951404097297602742047604146346648274685456858323208859", 10);
    paillier_decrypt(m, c, p, q);

    // Afficher le résultat
    gmp_printf("Message déchiffré : %Zd\n", m);

    // Libération de la mémoire
    mpz_clears(p, q, n, r, m, c, NULL);

    return 0;
}
