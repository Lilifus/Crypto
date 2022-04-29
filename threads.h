#include "algos.h"
#include <pthread.h>

//Struct for passing arguments to threads
typedef struct values{
    mpz_t n;
    mpz_t k;
    mpz_t *tab;
    mpz_t s;
    mpz_t t;
    int id;
    int ret;
} values;


void* Fermat_for_threads(void* arg);
int Fermat_with_threads(mpz_t n, mpz_t k, int nb_threads);

void* Miller_Rabin_for_thread(void* arg);
int Miller_Rabin_with_threads(mpz_t n, mpz_t k, int nb_threads);
