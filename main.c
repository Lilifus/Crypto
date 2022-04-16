#include "algos.h"


int main(int argc, char** argv){

    mpz_t n,k;
    mpz_init(n);
    mpz_init(k);

    //Lecture de n et k
    if(argc == 3){ // if n and k are given as arguments
        if(isnumber(argv[1]) && isnumber(argv[2])){
            mpz_set_str(n, argv[1], 10);
            mpz_set_str(k, argv[2], 10);
        }
        else{
            printf("Usage: %s <number to test> <number of iterations>\n", argv[0]);
            return 1;
        }
    }
    else if(argc == 1){ // if n and k are not given as arguments they are asked to the user
        printf("Quel est l'entier à tester ?\n");
        char n_str[1024];
        scanf("%s", n_str); // we use scanf instead of gmp_scanf to avoid errors made by the user
        if(isnumber(n_str)){
            mpz_set_str(n, n_str, 10);
        }
        else{// Error if the user input for n is not a number
            printf("Usage: %s <number> <k>\n", argv[0]);
            return 1;
        }
        printf("Quel est le nombre de tests ?\n");
        scanf("%s", n_str);
        if(isnumber(n_str)){
            mpz_set_str(k, n_str, 10);
        }
        else{// Error if the user input for k is not a number
            printf("Usage: %s <n> <number>\n", argv[0]);
            return 1;
        }
    }
    else{// Error if the user input is not correct
        printf("Usage: %s <n> <k>\n", argv[0]);
        mpz_clear(n);
        mpz_clear(k);
        return 1;
    }

    // Affichage des résultats
    printf("Fermat : ");
    if(Fermat(n,k)){
        printf("Prime\n");
    }
    else{
        printf("Composite\n");
    }
    printf("Miller-Rabin : ");
    if(Miller_Rabin(n,k)){
        printf("Prime\n");
    }
    else{
        printf("Composite\n");
    }

    mpz_clear(n);
    mpz_clear(k);

    return 0;
}