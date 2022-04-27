#include "tools.h"

//return 1 if n is found, 0 if not
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

// Check if a string is a number (return 1 if yes, 0 if not)
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
