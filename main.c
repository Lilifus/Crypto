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

    
    int n,k;
    if(argc == 3){
        n = atoi(argv[1]);
        k = atoi(argv[2]);
    }
    else if(argc == 1){
        printf("Quel est l'entier à tester ?\n");
        scanf("%d", &n);
        printf("Quel est le nombre de tests ?\n");
        scanf("%d", &k);
    }
    else{
        printf("Usage: %s <n> <k>\n", argv[0]);
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

    return 0;
}