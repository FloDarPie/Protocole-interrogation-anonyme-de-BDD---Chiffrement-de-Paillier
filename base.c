#include "communication.h"


void genererTab(int *tableau, int dim)
{

    tableau = (int *)malloc(dim * sizeof(int));
    for (int i; i < dim; i++)
    {
        tableau[i]= i;
    }
}

void tabrequete(int *tab, int dim, int cell)
{
    tab = (int *)malloc(dim * sizeof(int));
    for (int i; i < dim; i++)
    {
        if (i == cell)
        {
            tab[i]= 1;
        }
        else
        {
            tab[i]= 0;
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


