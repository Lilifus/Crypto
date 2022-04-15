#include "algos.h"

void square_and_multiply(mpz_t a, mpz_t n, mpz_t H, mpz_t result) {
    //Premiere version
    // mpz_set_ui((result), 1);
    // mpz_t tmp;
    // mpz_init(tmp);
    // mpz_set(tmp, a);
    // while (mpz_cmp_ui(H,0) > 0) {
    //     if (mpz_odd_p(H)) {
    //         mpz_mul((result), (result), tmp);
    //         mpz_mod((result), (result), n);
    //     }
    //     mpz_mul(tmp, tmp, tmp);
    //     mpz_mod(tmp, tmp, n);
    //     mpz_div_ui(H, H, 2);
    // }
    // mpz_clear(tmp);

    //version avec string
    char * bin = mpz_get_str(NULL,2,H);  
    int i;                               
    mpz_set((result),a); 
    for(i = 1; i < strlen(bin);i++) //on check chaque bit
    {                       
        //ici on square      
        mpz_mul((result),(result),(result));
        mpz_mod((result),(result),n);
        if(bin[i] == '1')//et là on multiply
        {
            mpz_mul((result),(result),a);
            mpz_mod((result),(result),n);
        }
    }
    free(bin);
}

//return 1 if n is prime, 0 otherwise
int Fermat(mpz_t n, mpz_t k){
    srand(time(NULL));
    mpz_t h;
    mpz_init(h);
    mpz_set_ui(h, mpz_get_ui(n)-1);
    for(int i = 0; mpz_cmp_ui(k,i)>0; i++){
        mpz_t a;
        mpz_init(a);
        mpz_set_ui(a, (rand()%(mpz_get_ui(n)-2))+1);
        mpz_t r;
        mpz_init(r);
        square_and_multiply(a,n,h,r);
        if(mpz_cmp_ui(r, 1)){
            mpz_clear(a);
            mpz_clear(r);
            mpz_clear(h);
            return 0;
        }
        mpz_clear(a);
        mpz_clear(r);
    }
    mpz_clear(h);
    return 1;
}

//decompose n-1 en 2^s * t	et return s et t
void decompose(mpz_t n, mpz_t* s, mpz_t* t){
    mpz_set_ui((*s), 0);
    mpz_sub_ui(n, n, 1);
    mpz_set(*t, n);
    while(mpz_cmp_ui(n, 0) > 0){
        if(mpz_odd_p(n)){
            return;
        }
        else{
            mpz_add_ui((*s), (*s), 1);
            mpz_div_ui(n, n, 2);
            mpz_set(*t, n);
        }
    }
}

//return 1 if n is prime, 0 otherwise
int Miller_Rabin(mpz_t n, mpz_t k){
    srand(time(NULL));
    mpz_t s, t, ntmp, two;
    mpz_init(s);
    mpz_init(t);
    mpz_init(ntmp);
    mpz_set(ntmp, n);
    mpz_init(two);
    mpz_set_ui(two, 2);
    decompose(ntmp, &s, &t);
    for(int i = 1; i <= mpz_get_ui(k); i++){
        mpz_t a;
        mpz_init(a);
        mpz_set_ui(a,(rand()%(mpz_get_ui(n)-1))+1);
        mpz_t y;
        mpz_init(y); 
        square_and_multiply(a,n,t,y);

        if(mpz_cmp_ui(y, 1) && mpz_cmp_ui(y, mpz_get_ui(n)-1)){
            for(int j = 1; mpz_cmp_ui(s,j)>0; j++){
                square_and_multiply(y,n,two,y);

                if(!mpz_cmp_ui(y, 1)){
                    mpz_clear(y);
                    mpz_clear(a);
                    mpz_clear(s);
                    mpz_clear(t);
                    mpz_clear(two);
                    return 0;
                }
                if(mpz_cmp_ui(y, mpz_get_ui(n)-1)==0){
                    break;
                }
            }
            if(mpz_cmp_ui(y, mpz_get_ui(n)-1)!=0){
                mpz_clear(y);
                mpz_clear(a);
                mpz_clear(s);
                mpz_clear(t);
                mpz_clear(two);
                return 0;
            }
        }
        mpz_clear(y);
        mpz_clear(a);
    }
    mpz_clear(s);
    mpz_clear(t);
    mpz_clear(ntmp);
    mpz_clear(two);
    return 1;
}