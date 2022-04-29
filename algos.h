#include "tools.h"
#include <time.h>
#include <pthread.h>

//Struct for passing arguments to threads
typedef struct values{
    mpz_t n;
    mpz_t k;
    mpz_t s;
    mpz_t t;
    int ret;
} values;

void square_and_multiply(mpz_t a, mpz_t n, mpz_t H, mpz_t result);
int Fermat(mpz_t n, mpz_t k);
void* Fermat_for_threads(void* arg);
int Fermat_with_threads(mpz_t n, mpz_t k, int nb_threads);
void decompose(mpz_t n, mpz_t s, mpz_t t);
int Miller_Rabin(mpz_t n, mpz_t k);
void* Miller_Rabin_for_thread(void* arg);
int Miller_Rabin_with_threads(mpz_t n, mpz_t k, int nb_threads);
