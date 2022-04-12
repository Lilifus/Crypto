#include "algos.h"

void square_and_multiply(mpz_t a, int n, int H, mpz_t *result) {
  
    mpz_set_ui((*result), 1);
    mpz_t tmp;
    mpz_init(tmp);
    mpz_set(tmp, a);
    while (H > 0) {
    if (H%2) {
        mpz_mul((*result), (*result), tmp);
        mpz_mod_ui((*result), (*result), n);
    }
    mpz_mul(tmp, tmp, tmp);
    mpz_mod_ui(tmp, tmp, n);
    H/=2;
    }
    mpz_clear(tmp);
}

//return 1 if n is prime, 0 otherwise
int Fermat(int n, int k){
    srand(time(NULL));
    for(int i = 0; i < k; i++){
        mpz_t a;
        mpz_init(a);
        mpz_set_ui(a, (rand()%(n-2))+1);
        mpz_t r;
        mpz_init(r);
        square_and_multiply(a,n,n-1,&r);
        if(mpz_cmp_ui(r, 1)){
            mpz_clear(a);
            mpz_clear(r);
            return 0;
        }
        mpz_clear(a);
        mpz_clear(r);
    }
    return 1;
}

int decompose(int n, int* t){
    int i = 0;
    n--;
    (*t) = n;
    while(n>0){
        if(n%2){
            return i;
        }
        else{
            i++;
            n/=2;
            (*t) = n;
        }
    }
    return i;
}

//return 1 if n is prime, 0 otherwise
int Miller_Rabin(int n, int k){
    srand(time(NULL));
    int t;
    int s = decompose(n, &t);

    for(int i = 1; i < k; i++){
        mpz_t a;
        mpz_init(a);
        mpz_set_ui(a,(rand()%(n-1))+1);
        mpz_t y;
        mpz_init(y); 
        square_and_multiply(a,n,t,&y);

        if(mpz_cmp_ui(y, 1) && mpz_cmp_ui(y, n-1)){
            for(int j = 1; j < s-1; j++){
                mpz_mul(y, y, y);
                mpz_mod_ui(y, y, n);

                if(!mpz_cmp_ui(y, 1)){
                    mpz_clear(y);
                    return 0;
                }
                if(!mpz_cmp_ui(y, n-1)){
                    break;
                }
            }
            return 0;
        }
        mpz_clear(y);
    }
    return 1;
}