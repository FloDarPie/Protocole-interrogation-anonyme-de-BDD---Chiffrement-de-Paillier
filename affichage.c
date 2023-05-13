
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