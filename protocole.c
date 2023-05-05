#include "paillier.h"
#include "affichage.c"

// gcc affichage.c paillierDecryptage.c paillierEncryptage.c paillierParametre.c paillierCles.c protocole.c -o protocole -lgmp


int main(int argc, char *argv[])
{
    if(argc != 4)
        {
            printf("Pb sur le nombre de parametre !");
            return 0;
        }
        
    //on prepare le chrono
    double time_spent = 0.0;
    clock_t begin = clock();

    // taille tableau // dimension // case requise
    int taille_tableau  = atoi(argv[1]);
    int dimension       = atoi(argv[2]);
    int cible            = atoi(argv[3]);

    //les elements
    int *tableau = (int *) malloc(taille_tableau * sizeof(int));
    int *vecteur = (int *) malloc(taille_tableau * sizeof(int));

    //remplir nos tableaux
    int i;
    int j = taille_tableau;
    for(i = 0; i< taille_tableau; i++)
        {
            tableau[i] = j;
            j--;
            vecteur[i] = 0;
        }
    vecteur[cible] = 1;

    //retour console
    clock_t balise1 = clock();
    time_spent += (double)(balise1 - begin) / CLOCKS_PER_SEC;
    printf("-- tableau et vecteur cree _ %f s.\n", time_spent);
    
    display_tab(tableau, taille_tableau);
    display_tab(vecteur, taille_tableau);


    //=== gestion gmp
    mpz_t n, n2, lambda, mu;
    bool test = false;
    
    // Initialisation des variables GMP
    mpz_inits(n, n2, lambda, mu, NULL);

    // Initialisation des cles
    paillier_pubkey pubkey;
    paillier_privkey privkey;

    unsigned long int seed = 1;

    if (!test)
    {
        srand(time(NULL));
        seed = rand(); // utilise l'horloge système comme graine
    }

    // Génération des paramètres du cryptosystème de Paillier
    generer_parametre(n, n2, lambda, seed);

    //Generation des cles
    generer_cle(&pubkey, &privkey, n, n2, lambda, mu, seed);


    balise1 = clock();
    time_spent += (double)(balise1 - begin) / CLOCKS_PER_SEC;
    printf("-- Cles pretes _ %f s.\n", time_spent);
    gmp_printf("Cle publique {\nn      : %Zd}\n", pubkey.n);
    gmp_printf("Cle prive {\nlambda : %Zd}\n---------\n", privkey.lambda);

    
    
    //=========== PROTOCOLE 1 - Utilisation du cryptosysteme de Paillier
    //Utilisation des cles.
    mpz_t m_clair, m_chiffre, m_puissance;
    mpz_init(m_clair);
    mpz_init(m_chiffre);
    mpz_init(m_puissance);/*
    printf("-- Demarrage protocole 1, echange de vecteur\n");

    clock_t protocole1_encoursDeb = clock();
    clock_t protocole1_encours = clock();
    double time_protocole = 0.0;
    for(int i =0; i < taille_tableau; i++){
        printf("-");
        mpz_set_ui(m_clair, vecteur[i]);printf("-");                                    //init case
        chiffrer(&pubkey, m_clair, m_chiffre);printf("chiffrement-");                   //chiffre case
        mpz_set_ui(m_puissance, tableau[i]);printf("-");
        mpz_powm(m_chiffre, m_chiffre, m_puissance, pubkey.n2);printf("puissance-");     //puissance case
        dechiffrer(&pubkey, &privkey, m_chiffre, m_clair);printf("dechiffrement-"); //dechiffre
        vecteur[i] = mpz_get_ui(m_clair);printf("stockage-");                           //store
        protocole1_encours = clock();                                           //temps
        time_protocole += (double)(protocole1_encours - protocole1_encoursDeb) / CLOCKS_PER_SEC;
        printf("%f s.\n", time_protocole);
        protocole1_encoursDeb = clock();
    }
    protocole1_encours = clock();
    display_tab(vecteur, taille_tableau);
    time_spent += (double)(protocole1_encours - balise1) / CLOCKS_PER_SEC;
    printf("\nTemps total protocole : %f s.",time_spent);

    */

    //=========== PROTOCOLE 2 - Transfert de la base de donnees
    clock_t protocole2_encoursDeb = clock();
    clock_t protocole2_encours = clock();
    double time_protocole2 = 0.0;
    for(int i =0; i < taille_tableau; i++){
        printf("-");
        vecteur[i] = tableau[i];
        protocole2_encours = clock();                                           //temps
        time_protocole2 += (double)(protocole2_encours - protocole2_encoursDeb) / CLOCKS_PER_SEC;
        printf("%f s.\n", time_protocole2);
        protocole2_encoursDeb = clock();
    }

    protocole2_encours = clock();
    display_tab(vecteur, taille_tableau);
    time_spent += (double)(protocole2_encours - protocole2_encoursDeb) / CLOCKS_PER_SEC;
    printf("\nTemps total protocole : %f s.",time_spent);



    //=========== Fin des protocoles
    balise1 = clock();
    time_spent += (double)(balise1 - begin) / CLOCKS_PER_SEC;
    printf("\nTemps total : %f s.\n",time_spent);











    
    // Libération de la mémoire utilisée par les variables GMP
    mpz_clear(n);
    mpz_clear(n2);
    mpz_clear(lambda);
    mpz_clear(mu);
    mpz_clear(m_clair);
    mpz_clear(m_chiffre);
    mpz_clear(m_puissance);


    free(tableau);
    free(vecteur);


    return 0;
}
