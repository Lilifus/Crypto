#include "algos.h"

int main(int argc, char** argv){

    mpz_t n,k;
    mpz_inits(n,k,NULL);
    

    if(argc!=3){// Error if the user input is not correct
        printf("Usage: %s <n> <k>\n", argv[0]);
        mpz_clears(n,k,NULL);
        return 1;
    }

    //Conversion des arguments en mpz_t
    if(isnumber(argv[1]) && isnumber(argv[2])){
        mpz_set_str(n, argv[1], 10);
        mpz_set_str(k, argv[2], 10);
    }
    else{
        printf("Usage: %s <number to test> <number of iterations>\n", argv[0]);
        return 1;
    }

    //Check if n and k are usable
    if(mpz_cmp_ui(n,0)<=0 || mpz_cmp_ui(k,0)<=0){
        printf("Usage: %s <n> <k>\n", argv[0]);
        printf("n and k must be positive\n");
        mpz_clears(n,k,NULL);
        return 1;
    }
    mpz_t n_1;
    mpz_init(n_1);
    mpz_sub_ui(n_1, n, 1);
    if(mpz_cmp(n_1,k)<=0){
        printf("Usage: %s <n> <k>\n", argv[0]);
        printf("k must be smaller than n-1\n");
        mpz_clears(n,k,n_1,NULL);
        return 1;
    }

    // Affichage des résultats
    printf("Fermat : ");
    int rtrn = Fermat(n,k);
    if(rtrn == 1){
        printf("Prime\n");
    }
    else if(rtrn==0){
        printf("Composite\n");
    }
    else{
        printf("Error : Fermat returned %d\n", rtrn);                                            
        return 1;
    }

    
    printf("Miller-Rabin : ");
    rtrn = Miller_Rabin(n,k);
    if(rtrn == 1){
        printf("Prime\n");
    }
    else if (rtrn==0){
        printf("Composite\n");
    }
    else{
        printf("Error : Miller-Rabin returned %d\n", rtrn);
        return 1;
    }

    mpz_clears(n,k,n_1,NULL);

    return 0;
}