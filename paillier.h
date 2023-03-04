#ifndef PAILLIER_GMP_H
#define PAILLIER_GMP_H

#include <gmp.h>

typedef struct {
    mpz_t n; // modulo
    mpz_t g; // générateur
    mpz_t lambda; // facteur d'extension
} paillier_pubkey;

typedef struct {
    mpz_t p; // premier
    mpz_t q; // deuxième
    mpz_t n; // modulo
    mpz_t nsquare; // n^2
    mpz_t lambda; // facteur d'extension
    mpz_t mu; // coefficient de décryptage
} paillier_privkey;

void paillier_keygen(paillier_pubkey *pub, paillier_privkey *priv, int keysize);

void paillier_encrypt(mpz_t ct, mpz_t m, paillier_pubkey pub);

void paillier_decrypt(mpz_t m, mpz_t ct, paillier_privkey priv, paillier_pubkey pub);

#endif
