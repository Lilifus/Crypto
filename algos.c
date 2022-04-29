#include "algos.h"


// return : result = a^H mod n
void square_and_multiply(mpz_t a, mpz_t n, mpz_t H, mpz_t result) {
    size_t size = mpz_sizeinbase(H,2); // size of H in base 2
    mpz_set(result,a);     
    for(int i = size-2; i >= 0;i--){ //check each bit of H except the MSB     
        //square     
        mpz_mul(result,result,result);
        mpz_mod(result,result,n);
        if(mpz_tstbit(H,i)==1){ //if the bit is 1, multiply by a
            mpz_mul(result,result,a);
            mpz_mod(result,result,n);
        }
    }
}

//return 1 if n is prime, 0 otherwise
int Fermat(mpz_t n, mpz_t k){
    mpz_t *tab = malloc(sizeof(mpz_t)*mpz_get_ui(k)); //the table that will contain the all the random a used
    if(tab == NULL){
        printf("Erreur d'allocation de mémoire\n");
        return -1;
    }

    mpz_t h, a, r, n_2;
    gmp_randstate_t rstate; // seed for random number generation
    mpz_inits(h, a, r, n_2, NULL);
    gmp_randinit_default(rstate);
    gmp_randseed_ui(rstate, time(NULL));

    mpz_sub_ui(n_2, n, 2);
    mpz_sub_ui(h, n, 1);//set the exponent to n-1
    for(int i = 0; mpz_cmp_ui(k,i)>0; i++){
        mpz_urandomm(a, rstate, n_2); // a = rand(1,n-2) (n-2 included)
        mpz_add_ui(a, a, 1);
        while (check_tab(tab, i, a) == 1){// check if a is already in the table
            mpz_urandomm(a, rstate, n_2);
            mpz_add_ui(a, a, 1);
        }
        square_and_multiply(a,n,h,r);
        if(mpz_cmp_ui(r, 1)){ // if r != 1 mod n
            mpz_clears(h, a, r, n_2, NULL);
            gmp_randclear(rstate);
            free_tab(tab, i+1);
            return 0; // n is composite
        }
    }
    mpz_clears(h, a, r, n_2, NULL);
    gmp_randclear(rstate);
    free_tab(tab, mpz_get_ui(k));
    return 1; // n is prime
}


//decompose n-1 in 2^s * t	and return s and t
void decompose(mpz_t n, mpz_t s, mpz_t t){
    //t is the binary representation of n-1 without the lasts 0
    //and s is the number of 0 left

    mpz_t n_1;
    mpz_init(n_1);
    mpz_sub_ui(n_1, n, 1);

    mpz_set_ui(s, 0);
    mpz_set(t, n_1);
    while(mpz_cmp_ui(n_1, 0) > 0){
        if(mpz_odd_p(n_1)){ // if the number is odd, it means we reached the last 1
            mpz_clear(n_1);
            return;
        }
        else{
            mpz_add_ui(s, s, 1); // we add 1 to s for each 0 we find
            mpz_div_ui(n_1, n_1, 2); // we divide n_1 by 2 to remove the last bit
            mpz_set(t, n_1);
        }
    }
    mpz_clear(n_1);
}

//return 1 if n is prime, 0 otherwise
int Miller_Rabin(mpz_t n, mpz_t k){
    mpz_t *tab = malloc(sizeof(mpz_t)*mpz_get_ui(k)); //the table that will contain the all the random a used
    if(tab == NULL){
        printf("Erreur d'allocation de mémoire\n");
        return -1;
    }

    mpz_t s, t, two, n_1, a, y;      
    gmp_randstate_t rstate;
    mpz_inits(s, t, two, n_1, a, y, NULL);
    mpz_sub_ui(n_1, n, 1);
    mpz_set_ui(two, 2);
    gmp_randinit_default(rstate);
    gmp_randseed_ui(rstate, time(NULL));

    decompose(n, s, t); // decompose n-1 in 2^s * t and store s and t

    for(int i = 1; i <= mpz_get_ui(k); i++){  
        mpz_urandomm(a, rstate, n_1);// set a random number between 1 and n-1(included)
        mpz_add_ui(a, a, 1);
        while (check_tab(tab, i-1, a) == 1){// check if a is already in the table
            mpz_urandomm(a, rstate, n_1);
            mpz_add_ui(a, a, 1);
        }
        square_and_multiply(a,n,t,y);

        if(mpz_cmp_ui(y, 1) && mpz_cmp(y, n_1)){ // if y != 1 mod n and y != -1 mod n
            for(int j = 1; mpz_cmp_ui(s,j)>0; j++){
                square_and_multiply(y,n,two,y);

                if(!mpz_cmp_ui(y, 1)){ // if y == 1 mod n
                    mpz_clears(s, t, two, n_1, a, y, NULL);
                    gmp_randclear(rstate);
                    free_tab(tab, i);
                    return 0; // n is composite
                }
                if(!mpz_cmp(y, n_1)){ // if y == -1 mod n
                    break;
                }
            }
            // the if is needed to go to the next iteration without returning composite by mistake
            if(mpz_cmp(y, n_1)){ // if y != -1 mod n
                mpz_clears(s, t, two, n_1, a, y, NULL);
                gmp_randclear(rstate);
                free_tab(tab, i);
                return 0; // n is composite
            }
        }
    }
    mpz_clears(s, t, two, n_1, a, y, NULL);
    gmp_randclear(rstate);
    free_tab(tab, mpz_get_ui(k));
    return 1; // n is prime
}
