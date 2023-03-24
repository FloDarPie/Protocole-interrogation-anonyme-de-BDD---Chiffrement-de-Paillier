#include <gmp.h>
#include <stdlib.h>
#include "paillier.h"



void genererTab(mpz_t *tableau, int dim);

void tabrequete(mpz_t *tab, int dim, int cell);

void requetechiff(mpz_t *tab,int dim, paillier_pubkey *pubkey);

void prodreqtab(mpz_t *bd, mpz_t *req ,mpz_t *chiff,mpz_t n, int dim);

