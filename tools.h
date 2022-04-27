#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int check_tab(mpz_t *tab, int size, mpz_t n);
void free_tab(mpz_t *tab, int size);
int isnumber(char *str);
