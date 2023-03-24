
#include "paillier.h"

// gcc paillierDecryptage.c paillierEncryptage.c paillierParametre.c paillierCles.c test_paillier.c -o test -lgmp


int main()
{
    mpz_t n, n2, lambda, mu;
    bool test = true;
    
    // Initialisation des variables GMP
    mpz_inits(n, n2, lambda, mu, NULL);

    // Initialisation des cles
    paillier_pubkey pubkey;
    paillier_privkey privkey;

    unsigned long int seed = 1;

    if (!test)
    {
        seed = time(NULL); // utilise l'horloge système comme graine
    }

    // Génération des paramètres du cryptosystème de Paillier
    generer_parametre(n, n2, lambda, seed);

    //Generation des cles
    generer_cle(&pubkey, &privkey, n, n2, lambda, mu, seed);

    gmp_printf("---------\nCle publique {\nn      : %Zd\nn2      : %Zd }\n=========", pubkey.n, pubkey.n2);
    gmp_printf("\nCle prive {\nlambda : %Zd\nmu     : %Zd }\n---------\n", privkey.lambda, privkey.mu);

    printf("/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/\n"); //suppr

    //Utilisation des cles.
    mpz_t m_clair, m_chiffre;
    mpz_init(m_clair);
    mpz_init(m_chiffre);

    mpz_set_ui(m_clair, 42);
    mpz_set_ui(m_clair,195947168573380514);
    //mpz_set_str(m_clair, "120412728063243572712346020199130428999279985789671864424875069675842204100223120538569506661225630028908605082049688583460982007271531771955139564631066174208363418171770666183402755434027529771850186007345659499315338138848366004537838911299081727672731951404097297602742047604146346648274685456858323208859120412728063243572712346020199130428999279985789671864424875069675842204100223120538569506661225630028908605082049688583460982007271531771955139564631066174208363418171770666183402755434027529771850186007345659499315338138848366004537838911299081727672731951404097297602742047604146346648274685456858323208859120412728063243572712346020199130428999279985789671864424875069675842204100223120538569506661225630028908605082049688583460982007271531771955139564631066174208363418171770666183402755434027529771850186007345659499315338138848366004537838911299081727672731951404097297602742047604146346648274685456858323208859", 10);
    chiffrer(&pubkey, m_clair, m_chiffre);

    
    gmp_printf("\nMessage clair   : %Zd", m_clair);
    gmp_printf("\nMessage chiffre : %Zd\n", m_chiffre);


    printf("/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/\n"); //suppr

    //dechiffré
    mpz_t m_dechiffre;
    mpz_init(m_dechiffre);
    dechiffrer(&pubkey, &privkey, m_chiffre, m_dechiffre);
    gmp_printf("\nMessage dechiffre : %Zd\n", m_dechiffre);


    mpz_set_ui(m_clair, 0);
    chiffrer(&pubkey, m_clair, m_chiffre);
    printf("/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/\n"); //suppr
    gmp_printf("\nMessage clair   : %Zd", m_clair);
    gmp_printf("\nMessage chiffre : %Zd\n", m_chiffre);

    mpz_set_ui(m_clair, 1);
    chiffrer(&pubkey, m_clair, m_chiffre);
    printf("/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/\n"); //suppr
    gmp_printf("\nMessage clair   : %Zd", m_clair);
    gmp_printf("\nMessage chiffre : %Zd\n", m_chiffre);

    // Libération de la mémoire utilisée par les variables GMP
    mpz_clear(n);
    mpz_clear(n2);
    mpz_clear(lambda);
    mpz_clear(mu);
    mpz_clear(m_clair);
    mpz_clear(m_chiffre);
    mpz_clear(m_dechiffre);
    
    return 0;
}
