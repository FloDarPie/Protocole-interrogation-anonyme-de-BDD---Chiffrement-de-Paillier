#include "paillier.h"

void generer_parametre(mpz_t n, mpz_t g, mpz_t lambda, bool test)
{
    //gmp_randstate_t state;
    gmp_randstate_t state;
    mpz_t p, q, phi, tmp;
    
    
    // Initialisation des variables GMP
    mpz_init(p);
    mpz_init(q);
    mpz_init(phi);
    mpz_init(tmp);
    
    // Initialisation de l'état aléatoire //option, avec l'horloge
    gmp_randinit_default(state);
    //=================================
    if (!test)
    {
    unsigned long seed = time(NULL); // utilise l'horloge système comme graine
    gmp_randseed_ui(state, seed);
    }
    //=====================
    
    // Génération de deux nombres premiers aléatoires de 1024 bits
    mpz_urandomb(p, state, 1024);    mpz_nextprime(p, p);
    mpz_urandomb(q, state, 1024);    mpz_nextprime(q, q);
    
    // Calcul de n = p * q
    mpz_mul(n, p, q);
    
    // Calcul de lambda = lcm(p-1, q-1) = (p-1)*(q-1)/gcd(p-1, q-1)
    mpz_sub_ui(tmp, p, 1);
    mpz_sub_ui(phi, q, 1);
    mpz_lcm(lambda, tmp, phi);  //calcul du ppcm
    mpz_gcd(tmp, tmp, phi);     //calcul pgcd    
    mpz_div(lambda, lambda, tmp);
    
    // Choix de g tel que g est dans Z*n^2 et g est d'ordre n*lcm(p-1, q-1)
    do {
        mpz_urandomm(g, state, n);
        
        unsigned long int lambda_ui = mpz_get_ui(lambda);
        mpz_powm_ui(tmp, g, lambda_ui, n);

        mpz_sub_ui(tmp, tmp, 1);
        mpz_divexact(tmp, tmp, n);

        mpz_gcd(tmp, tmp, n);
    } 
    while (mpz_cmp_ui(tmp, 1) != 0);

    
    // Libération de la mémoire utilisée par les variables GMP
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(phi);
    mpz_clear(tmp);
    gmp_randclear(state);
}
/*
int main()
{
    mpz_t n, g;
    
    // Initialisation des variables GMP
    mpz_init(n);
    mpz_init(g);
    
    // Génération des paramètres du cryptosystème de Paillier
    generer_parametre(n, g);
    
    // Affichage des paramètres générés
    gmp_printf("n = %Zd\n", n);
    gmp_printf("g = %Zd\n", g);
    
    // Libération de la mémoire utilisée par les variables GMP
    mpz_clear(n);
    mpz_clear(g);
    
    return 0;
}
*/
