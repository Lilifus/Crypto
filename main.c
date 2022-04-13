#include "algos.h"


int main(int argc, char** argv){
    
    //test square_and_multiply
    // mpz_t a,r;
    // mpz_init(r);
    // mpz_init(a);
    // mpz_set_ui(a, 2);
    // square_and_multiply(a, 10, 26, &r);
    // gmp_printf("%Zd\n", r);
    // mpz_clear(r);

    //test decompose
    // int t;
    // int s = decompose(5569,&t);
    // printf("%d %d\n", s, t);

    
    mpz_t n,k;
    mpz_init(n);
    mpz_init(k);
    if(argc == 3){
        mpz_set_str(n, argv[1], 10);
        mpz_set_str(k, argv[2], 10);
    }
    else if(argc == 1){
        printf("Quel est l'entier à tester ?\n");
        gmp_scanf("%Zd", n);
        printf("Quel est le nombre de tests ?\n");
        gmp_scanf("%Zd", k);
    }
    else{
        printf("Usage: %s <n> <k>\n", argv[0]);
        mpz_clear(n);
        mpz_clear(k);
        return 1;
    }
    printf("Test de Fermat : ");
    if(Fermat(n,k)){
        printf("Premier\n");
    }
    else{
        printf("Compose\n");
    }
    printf("Test de Miller-Rabin : ");
    if(Miller_Rabin(n,k)){
        printf("Premier\n");
    }
    else{
        printf("Compose\n");
    }

    mpz_clear(n);
    mpz_clear(k);

    return 0;
}