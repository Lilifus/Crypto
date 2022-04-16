#include "algos.h"


// return : result = a * b mod n
void mul_and_mod(mpz_t a, mpz_t b, mpz_t n, mpz_t result){
    mpz_t r;
    mpz_init(r);
    mpz_mul(r, a, b);
    mpz_mod(r, r, n);
    mpz_set(result, r);
    mpz_clear(r);
}

// return : result = a^H mod n
void square_and_multiply(mpz_t a, mpz_t n, mpz_t H, mpz_t result) {
    char * Hbin = mpz_get_str(NULL,2,H);  // H in binary                         
    mpz_set((result),a); 
    for(int i = 1; i < strlen(Hbin);i++) //check each bit of H
    {                       
        //square     
        mul_and_mod(result,result,n,result);
        if(Hbin[i] == '1')//multiply
        {
            mul_and_mod(result,a,n,result);
        }
    }
    free(Hbin);
}

//return 1 if n is prime, 0 otherwise
int Fermat(mpz_t n, mpz_t k){
    srand(time(NULL)); // seed the random number generator
    mpz_t h;
    mpz_init(h);
    mpz_set_ui(h, mpz_get_ui(n)-1); //set the exponent to n-1
    for(int i = 0; mpz_cmp_ui(k,i)>0; i++){
        mpz_t a;
        mpz_init(a);
        mpz_set_ui(a, (rand()%(mpz_get_ui(n)-2))+1); // set a random number between 1 and n-2(included)
        mpz_t r;
        mpz_init(r);
        square_and_multiply(a,n,h,r);
        if(mpz_cmp_ui(r, 1)){ // if r != 1 mod n
            mpz_clear(a);
            mpz_clear(r);
            mpz_clear(h);
            return 0; // n is composite
        }
        mpz_clear(a);
        mpz_clear(r);
    }
    mpz_clear(h);
    return 1; // n is prime
}

//decompose n-1 in 2^s * t	and return s and t
void decompose(mpz_t n, mpz_t* s, mpz_t* t){
    //t is the binary representation of n-1 without the lasts 0
    //and s is the number of 0 left

    mpz_t n_1; // n is replaced by n_1 so it's not modified
    mpz_init(n_1);
    mpz_sub_ui(n_1, n, 1); // n-1
    mpz_set_ui((*s), 0);
    mpz_set(*t, n_1);
    while(mpz_cmp_ui(n_1, 0) > 0){
        if(mpz_odd_p(n_1)){ // if the number is odd, it means we reached the last 1
            return;
        }
        else{
            mpz_add_ui((*s), (*s), 1); // we add 1 to s for each 0 we find
            mpz_div_ui(n_1, n_1, 2); // we divide n_1 by 2 to remove the last bit
            mpz_set(*t, n_1);
        }
    }
}

//return 1 if n is prime, 0 otherwise
int Miller_Rabin(mpz_t n, mpz_t k){
    srand(time(NULL)); // seed the random number generator

    mpz_t s, t, two;
    mpz_init(s);
    mpz_init(t);
    mpz_init(two);
    mpz_set_ui(two, 2);

    decompose(n, &s, &t); // decompose n-1 in 2^s * t and store s and t

    for(int i = 1; i <= mpz_get_ui(k); i++){
        mpz_t a;
        mpz_init(a);
        mpz_set_ui(a,(rand()%(mpz_get_ui(n)-1))+1); // set a random number between 1 and n-1(included)

        mpz_t y;
        mpz_init(y); 
        square_and_multiply(a,n,t,y);

        if(mpz_cmp_ui(y, 1) && mpz_cmp_ui(y, mpz_get_ui(n)-1)){ // if y != 1 mod n and y != -1 mod n
            for(int j = 1; mpz_cmp_ui(s,j)>0; j++){
                square_and_multiply(y,n,two,y);

                if(!mpz_cmp_ui(y, 1)){ // if y == 1 mod n
                    mpz_clear(y);
                    mpz_clear(a);
                    mpz_clear(s);
                    mpz_clear(t);
                    mpz_clear(two);
                    return 0; // n is composite
                }
                if(!mpz_cmp_ui(y, mpz_get_ui(n)-1)){ // if y == -1 mod n
                    break;
                }
            }
            // the if is needed to go to the next iteration without returning composite by mistake
            if(mpz_cmp_ui(y, mpz_get_ui(n)-1)){ // if y != -1 mod n
                mpz_clear(y);
                mpz_clear(a);
                mpz_clear(s);
                mpz_clear(t);
                mpz_clear(two);
                return 0; // n is composite
            }
        }
        mpz_clear(y);
        mpz_clear(a);
    }
    mpz_clear(s);
    mpz_clear(t);
    mpz_clear(two);
    return 1; // n is prime
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