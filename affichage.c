
#include "affichage.h"

void display_tab(int *t, int taille){

    for(int i = 0; i< taille; i++)
        printf("| %d ", t[i]);
    printf("|\n");

}

int mpz_to_bit_array(mpz_t n, int* bit_array, int size) {
    int bit_index = 0;
    mpz_t remainder;
    mpz_init(remainder);

    while (mpz_cmp_ui(n, 0) > 0 && bit_index < size) {
        
        mpz_mod_ui(remainder, n, 2);
        bit_array[size - 1 - bit_index] = mpz_get_ui(remainder);
        mpz_divexact_ui(n, n, 2);
        bit_index++;
    }

    // Remplir le reste du tableau avec des zéros
    int cpt = bit_index;
    while (bit_index < size) {
        bit_array[size - 1 - bit_index] = 0;
        bit_index++;
    }

    mpz_clear(remainder);
    return size-cpt;
}


int  int_to_bit_array(int n, int* bit_array, int size) {
    int bit_index = 0;
    while (n > 0 && bit_index < size) {
        bit_array[size - 1 - bit_index] = n % 2;
        n /= 2;
        bit_index++;
    }
    // Remplir le reste du tableau avec des zéros
    int cpt = bit_index;
    while (bit_index < size) {
        bit_array[size - 1 - bit_index] = 0;
        bit_index++;
    }

    return size-cpt;

}



void exponentiation_rapide2_2(mpz_t A , mpz_t e,mpz_t f, mpz_t g,mpz_t h){

    
        int bit_array_e[128];

        int bit_array_f[128];

        int size = 128;

        int count_e = mpz_to_bit_array(e, bit_array_e, size);
        int count_f = mpz_to_bit_array(f, bit_array_f, size);

        int count =  count_e < count_f ? count_e : count_f;


        for(int i = count; i<=size-1; i++){
            
           
            mpz_mul(A,A,A);
            if(bit_array_e[i]==1){
               
                mpz_mul(A,A,g);
            }
            if(bit_array_f[i]==1){
               mpz_mul(A,A,h);
            }
        }


     }


void exponentiation_rapide(mpz_t A , mpz_t * T,int * N,int n){
    int size = 128;
     int tab[n][size];
     int count;
     int cpt ;
     int my_int;
     mpz_t my_mpz;


     count = mpz_to_bit_array(T[0],tab[0] , size);
    
     for(int i = 1; i<n; i++){
        
        cpt = mpz_to_bit_array(T[i], tab[i], size);

        count =  count < cpt ? count : cpt;

     }

     for(int i = count; i<=size-1; i++){
           
            mpz_mul(A,A,A);
            for(int j = 0; j<n; j++){
                if(tab[i][j] == 1){
                printf("%d  %d\n",i,tab[i][j]);
                my_int = N[j];
                mpz_init_set_si(my_mpz, my_int);
                mpz_mul(A,A,my_mpz);
            }

            }
            
        }
     

        mpz_clear(my_mpz);
}
