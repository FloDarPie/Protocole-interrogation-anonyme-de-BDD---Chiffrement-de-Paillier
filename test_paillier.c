
#include "paillier.h"

// gcc paillierParametre.c paillierCles.c test_paillier.c -o test -lgmp


int main()
{
    mpz_t n, g, lambda, mu;
    bool test = true;
    
    // Initialisation des variables GMP
    mpz_init(n);
    mpz_init(g);
    mpz_init(lambda);
    mpz_init(mu);

    // Initialisation des cles
    paillier_pubkey pubkey;
    paillier_privkey privkey;

    // Génération des paramètres du cryptosystème de Paillier
    generer_parametre(n, g, lambda, test);

    gmp_printf("n = %Zd\n", n);
    gmp_printf("g = %Zd\n", g);


    //Generation des cles
    generer_cle(&pubkey, &privkey, n, g, lambda, mu);

    gmp_printf("---------\nCle publique {\nn      : %Zd\ng      : %Zd }\n=========", pubkey.n, pubkey.g);
    gmp_printf("\nCle prive {\nlambda : %Zd\nmu     : %Zd }\n---------\n", privkey.lambda, privkey.mu);




    // Libération de la mémoire utilisée par les variables GMP
    mpz_clear(n);
    mpz_clear(g);
    mpz_clear(lambda);
    mpz_clear(mu);
    
    return 0;
}