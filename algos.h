#include "gmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void mul_and_mod(mpz_t a, mpz_t b, mpz_t n, mpz_t result);
void square_and_multiply(mpz_t a, mpz_t n, mpz_t H, mpz_t result);
int Fermat(mpz_t n, mpz_t k);
void decompose(mpz_t n, mpz_t* s, mpz_t* t);
int Miller_Rabin(mpz_t n, mpz_t k);
int isnumber(char *str);