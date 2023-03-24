#include "communication.h"


void genererTab(mpz_t *tableau, int dim)
{

    tableau = (mpz_t *)malloc(dim * sizeof(mpz_t));
    for (int i; i < dim; i++)
    {
        mpz_set_ui(tableau[i], i);
    }
}

void tabrequete(mpz_t *tab, int dim, int cell)
{
    tab = (mpz_t *)malloc(dim * sizeof(mpz_t));
    for (int i; i < dim; i++)
    {
        if (i == cell)
        {
            mpz_set_ui(tab[i], 1);
        }
        else
        {
            mpz_set_ui(tab[i], 0);
        }
    }
}
void requetechiff(mpz_t *tab, int dim, paillier_pubkey *pubkey)
{
    for (int i; i < dim; i++)
    {
        chiffrer(pubkey, tab[i], tab[i]);
    }
}

void prodreqtab(mpz_t *bd, mpz_t *req ,mpz_t *chiff, mpz_t n, int dim )
{   mpz_t tmp;
    mpz_init(tmp);
    mpz_set_ui(*chiff,1);
    for (int i; i < dim; i++)
    {   mpz_powm(tmp, req[i], bd[i], n);

        mpz_mul(*chiff, tmp, *chiff);
    }
}


