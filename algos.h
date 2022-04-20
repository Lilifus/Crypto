#include "tools.h"


void square_and_multiply(mpz_t a, mpz_t n, mpz_t H, mpz_t result);
int Fermat(mpz_t n, mpz_t k);
void decompose(mpz_t n, mpz_t s, mpz_t t);
int Miller_Rabin(mpz_t n, mpz_t k);