#include <stdio.h>

#include <gmp.h>

void display_tab(int *t, int taille);

int mpz_to_bit_array(mpz_t n, int *bit_array, int size);

int  int_to_bit_array( int n, int *bit_array, int size);


void exponentiation_rapide2_2(mpz_t A , mpz_t e,mpz_t f, mpz_t g,mpz_t h);

void exponentiation_rapide(mpz_t A , mpz_t * T,int * N,int n);