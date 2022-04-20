#include "algos.h"

//ERROR CODE
//-1 : error allocation memory


int main(int argc, char** argv){

    mpz_t n,k;
    mpz_inits(n,k,NULL);

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
        char entry[512];
        scanf("%s", entry); // we use scanf instead of gmp_scanf to avoid errors made by the user
        if(isnumber(entry)){
            mpz_set_str(n, entry, 10);
        }
        else{// Error if the user input for n is not a number
            printf("Usage: %s <number> <k>\n", argv[0]);
            return 1;
        }
        printf("Quel est le nombre de tests ?\n");
        scanf("%s", entry);
        if(isnumber(entry)){
            mpz_set_str(k, entry, 10);
        }
        else{// Error if the user input for k is not a number
            printf("Usage: %s <n> <number>\n", argv[0]);
            return 1;
        }
    }
    else{// Error if the user input is not correct
        printf("Usage: %s <n> <k>\n", argv[0]);
        mpz_clears(n,k,NULL);
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
        printf("Error %d\n", rtrn);                                             
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
        printf("Error %d\n", rtrn);
        return 1;
    }

    mpz_clears(n,k,NULL);

    return 0;
}