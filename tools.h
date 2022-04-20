#include "gmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int check_tab(mpz_t *tab, int size, mpz_t n);
void free_tab(mpz_t *tab, int size);
void mul_and_mod(mpz_t a, mpz_t b, mpz_t n, mpz_t result);
int isnumber(char *str);
