#include "paillier.h"
#include "affichage.h"


// gcc affichage.c paillierDecryptage.c paillierEncryptage.c paillierParametre.c paillierCles.c protocole.c -o protocole -lgmp


int main(int argc, char *argv[])
{
    if(argc != 5)
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
    int protocole      = atoi(argv[4]);

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
    if(protocole==0){
    mpz_t m_clair, m_chiffre, m_puissance, m_total;
    mpz_init(m_clair);
    mpz_init(m_chiffre);
    mpz_init(m_puissance);
    mpz_init(m_total);
    mpz_set_ui(m_total,1);
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
       
        mpz_mul(m_total,m_total,m_chiffre);
        mpz_mod(m_total, m_total, pubkey.n2);
        
        protocole1_encours = clock();                                           //temps
        time_protocole += (double)(protocole1_encours - protocole1_encoursDeb) / CLOCKS_PER_SEC;
        printf("%f s.\n", time_protocole);
        protocole1_encoursDeb = clock();
    }
        
    dechiffrer(&pubkey, &privkey, m_total, m_clair); //dechiffre
    gmp_printf("\nMessage clair   : %Zd", m_clair);

    protocole1_encours = clock();
    time_spent += (double)(protocole1_encours - balise1) / CLOCKS_PER_SEC;

    printf("\nTemps total protocole : %f s.",time_spent);
   
   
    mpz_clear(m_total);
    mpz_clear(m_clair);
    mpz_clear(m_chiffre);
    mpz_clear(m_puissance);
}

    //=========== PROTOCOLE 2 - Transfert de la base de donnees
      if(protocole==1){
    clock_t protocole2_encoursDeb = clock();
    clock_t protocole2_encours = clock();
    double time_protocole2 = 0.0;

    int *tabtelechareger = (int *) malloc(taille_tableau * sizeof(int));

    for(int i =0; i < taille_tableau; i++){
        printf("-");
        tabtelechareger[i] = tableau[i];
        protocole2_encours = clock();                                           //temps
        time_protocole2 += (double)(protocole2_encours - protocole2_encoursDeb) / CLOCKS_PER_SEC;
        printf("%f s.\n", time_protocole2);
        protocole2_encoursDeb = clock();
    }
    protocole2_encours = clock();
    display_tab(vecteur, taille_tableau);
    time_spent += (double)(protocole2_encours - protocole2_encoursDeb) / CLOCKS_PER_SEC;
    printf("\nTemps total protocole : %f s.",time_spent);
    }



    //=========== PROTOCOLE 3 - Exponentiation rapide 2 à 2




 if(protocole==2){
    mpz_t m_clair_1, m_clair_2,m_chiffre_1, m_chiffre_2, m_puissance_1, m_puissance_2, m_total,m_cpt;
    mpz_init(m_clair_1);
    mpz_init(m_clair_2);
    mpz_init(m_chiffre_1);
    mpz_init(m_chiffre_2);
    mpz_init(m_puissance_1);
    mpz_init(m_puissance_2);
    mpz_init(m_total);
    mpz_set_ui(m_total,1);
    mpz_init(m_cpt);

    clock_t protocole3_encoursDeb = clock();
    clock_t protocole3_encours = clock();
    double time_protocole = 0.0;
    
    for(int i =0; i < taille_tableau-1; i=i+2){

        mpz_set_ui(m_cpt,1);
        mpz_set_ui(m_clair_1, vecteur[i]);                                 
        chiffrer(&pubkey, m_clair_1, m_chiffre_1);

        mpz_set_ui(m_clair_2, vecteur[i+1]);                                    
        chiffrer(&pubkey, m_clair_2, m_chiffre_2);
                        
        mpz_set_ui(m_puissance_1, tableau[i]);
        mpz_set_ui(m_puissance_2, tableau[i+1]);                      


        exponentiation_rapide2_2(m_cpt,m_puissance_1,m_puissance_2,m_chiffre_1,m_chiffre_2);                                  
       
        mpz_mul(m_total,m_total,m_cpt);
        mpz_mod(m_total, m_total, pubkey.n2);
        
        protocole3_encours = clock();                                           //temps
        time_protocole += (double)(protocole3_encours - protocole3_encoursDeb) / CLOCKS_PER_SEC;
        printf("%f s.\n", time_protocole);
        protocole3_encoursDeb = clock();
    }
    if(taille_tableau%2!=0){                         // les cas ou on a un tableau de taille impaire 
        mpz_set_ui(m_cpt,1);
        mpz_set_ui(m_clair_1, vecteur[i]);                                  

        mpz_set_ui(m_chiffre_2, 1);                                    
                        
        mpz_set_ui(m_puissance_1, tableau[taille_tableau-1]);

        exponentiation_rapide2_2(m_cpt,m_puissance_1,m_puissance_2,m_chiffre_1,m_chiffre_2);
        mpz_mul(m_total,m_total,m_cpt);
        mpz_mod(m_total, m_total, pubkey.n2);
    }
    dechiffrer(&pubkey, &privkey, m_total, m_clair_1); 

    gmp_printf("\nMessage clair   : %Zd", m_clair_1);

    protocole3_encours = clock();
    time_spent += (double)(protocole3_encours - balise1) / CLOCKS_PER_SEC;

    printf("\nTemps total protocole : %f s.",time_spent);
   
   
    mpz_clear(m_total);
    mpz_clear(m_clair_1);
    mpz_clear(m_clair_2);
    mpz_clear(m_puissance_1);
    mpz_clear(m_puissance_2);
    mpz_clear(m_chiffre_1);
    mpz_clear(m_chiffre_2);
    mpz_clear(m_cpt);
 }


  //=========== PROTOCOLE 4 - Exponentiation NON fonctionnelle 

  if(protocole==3){
    mpz_t m_cpt,m_clair,m_chiffre;
  

    clock_t protocole4_encoursDeb = clock();
    clock_t protocole4_encours = clock();
    double time_protocole = 0.0;
    mpz_init(m_cpt);
    mpz_set_ui(m_cpt,1);  
    mpz_init(m_clair);
    mpz_init(m_chiffre);
    mpz_t tab[taille_tableau];
      
      
      for(int i =0; i < taille_tableau; i++){
        mpz_set_ui(m_clair,vecteur[i]);
        
        chiffrer(&pubkey, m_clair, m_chiffre);
        mpz_init(tab[i]);
        mpz_set(tab[i],m_chiffre); 
      }


  exponentiation_rapide(m_cpt,tab,tableau,taille_tableau);

  dechiffrer(&pubkey, &privkey, m_cpt, m_cpt); 
    gmp_printf("\nMessage clair   : %Zd", m_cpt);

    protocole4_encours = clock();
    time_spent += (double)(protocole4_encours - balise1) / CLOCKS_PER_SEC;

    printf("\nTemps total protocole : %f s.",time_spent);
    mpz_clear(m_cpt);

  }




    //=========== Fin des protocoles
    balise1 = clock();
    time_spent += (double)(balise1 - begin) / CLOCKS_PER_SEC;
    printf("\nTemps total : %f s.\n",time_spent);

    



    
    // Libération de la mémoire utilisée par les variables GMP

    mpz_clear(n);
    mpz_clear(n2);
    mpz_clear(lambda);
    mpz_clear(mu);

    free(tableau);
    free(vecteur);


    return 0;
}
