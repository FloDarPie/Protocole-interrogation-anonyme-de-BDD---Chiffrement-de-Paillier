#ifndef PAILLIER_GMP_H
#define PAILLIER_GMP_H

#include <stdbool.h>
#include <stdio.h>
#include <gmp.h>
#include <time.h>


//Memorisation des cles
typedef struct {
    mpz_t n; 
    mpz_t g; 
} paillier_pubkey;

typedef struct {
    mpz_t lambda;
    mpz_t mu; 
} paillier_privkey;



void generer_parametre(mpz_t n, mpz_t g, mpz_t lambda, bool test);

void generer_cle(paillier_pubkey *pubkey, paillier_privkey *privkey, mpz_t n, mpz_t g, mpz_t lambda, mpz_t mu);

void chiffrer(paillier_pubkey *pubkey, mpz_t message_clair, mpz_t message_chiffre, bool test);

void dechiffrer(paillier_pubkey *pubkey, paillier_privkey *privkey, mpz_t message_chiffre, mpz_t message_dechiffre);

#endif
