
#include "paillier.h"

// gcc paillierDecryptage.c paillierEncryptage.c paillierParametre.c paillierCles.c test_paillier.c -o test -lgmp




int main()
{
    mpz_t n, g, lambda, mu;
    bool test = true;
    
    // Initialisation des variables GMP
    mpz_inits(n, g, lambda, mu, NULL);

    // Initialisation des cles
    paillier_pubkey pubkey;
    paillier_privkey privkey;

    // Génération des paramètres du cryptosystème de Paillier
    generer_parametre(n, g, lambda, test);

    //Generation des cles
    generer_cle(&pubkey, &privkey, n, g, lambda, mu);

    gmp_printf("---------\nCle publique {\nn      : %Zd\ng      : %Zd }\n=========", pubkey.n, pubkey.g);
    gmp_printf("\nCle prive {\nlambda : %Zd\nmu     : %Zd }\n---------\n", privkey.lambda, privkey.mu);

    printf("/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/\n"); //suppr

    //Utilisation des cles.
    mpz_t m_clair, m_chiffre;
    mpz_init(m_clair);
    mpz_init(m_chiffre);

    mpz_set_ui(m_clair, 42);
    chiffrer(&pubkey, m_clair, m_chiffre, test);

    
    gmp_printf("\nMessage clair   : %Zd", m_clair);
    gmp_printf("\nMessage chiffre : %Zd\n", m_chiffre);


    printf("/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/\n"); //suppr

    //dechiffré
    mpz_t m_dechiffre;
    mpz_init(m_dechiffre);
    dechiffrer(&pubkey, &privkey, m_chiffre, m_dechiffre);
    gmp_printf("\nMessage dechiffre : %Zd\n", m_dechiffre);

    // Libération de la mémoire utilisée par les variables GMP
    mpz_clears(n, g, lambda, mu, m_clair, m_chiffre);
    mpz_clear(m_dechiffre);
    
    return 0;
}
