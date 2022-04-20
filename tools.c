#include "tools.h"

//return 1 if n is found, 0 if not, -1 if error
int check_tab(mpz_t *tab, int size, mpz_t n){
    for(int i=0; i<size; i++){
        if(mpz_cmp(tab[i], n) == 0){
            return 1;
        }
    }
    mpz_init(tab[size]);
    mpz_set(tab[size], n);
    return 0;
}

// clear and free the tab of random mpz_t
void free_tab(mpz_t *tab, int size){
    for(int i=0; i<size; i++){
        mpz_clear(tab[i]);
    }
    free(tab);
}

// return : result = a * b mod n
void mul_and_mod(mpz_t a, mpz_t b, mpz_t n, mpz_t result){
    mpz_t r;
    mpz_init(r);
    mpz_mul(r, a, b);
    mpz_mod(r, r, n);
    mpz_set(result, r);
    mpz_clear(r);
}


// Check if a string is a number
int isnumber(char *str){
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] < '0' || str[i] > '9'){
            return 0;
        }
        i++;
    }
    return 1;
}
