#include <stdio.h>

#include <gmp.h>

void display_tab(int *t, int taille);

int mpz_to_bit_array(mpz_t n, int *bit_array, int size);

int  int_to_bit_array( int n, int *bit_array, int size);