#include "gmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void square_and_multiply(mpz_t a, int n, int H, mpz_t *result);
int Fermat(int n, int k);
int decompose(int n, int* t);
int Miller_Rabin(int n, int k);