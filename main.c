#include "threads.h"

#define DISPLAY_TIME 1
#define ACTIVE_THREADS 1
#define NB_THREADS 8

int main(int argc, char** argv){

    mpz_t n,k;
    mpz_inits(n,k,NULL);

    //Only used to get the time of the execution
    struct timespec start, end;
    double time_spent;
    

    if(argc==1){// if no argument is given, we ask the user to enter n and k
        printf("Please enter a number to test\n");
        char entry[1024];
        scanf("%s", entry); // we use scanf instead of gmp_scanf to avoid errors made by the user
        if(isnumber(entry)){
            mpz_set_str(n, entry, 10);
        }
        else{// Error if the user input for n is not a number
            printf("Usage: %s <number> <k>\n", argv[0]);
            return 1;
        }
        printf("How many iterations?\n");
        scanf("%s", entry);
        if(isnumber(entry)){
            mpz_set_str(k, entry, 10);
        }
        else{// Error if the user input for k is not a number
            printf("Usage: %s <n> <number>\n", argv[0]);
            return 1;
        }
    }else if(argc == 3){// if 2 arguments are given, we use them
        //Conversion des arguments en mpz_t
        if(isnumber(argv[1]) && isnumber(argv[2])){
            mpz_set_str(n, argv[1], 10);
            mpz_set_str(k, argv[2], 10);
        }
        else{
            printf("Usage: %s <number to test> <number of iterations>\n", argv[0]);
            return 1;
        }
    }
    else {// Error if the user input is not correct
        printf("Usage: %s <n> <k>\n", argv[0]);
        mpz_clears(n,k,NULL);
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

    // Lancement des tests

    int rtrn;
    
    //FERMAT
    clock_gettime(CLOCK_MONOTONIC, &start);
    if(ACTIVE_THREADS){
        //WITH THREADS
        rtrn = Fermat_with_threads(n,k,NB_THREADS);
    }
    else{
        //NO THREADS
        rtrn = Fermat(n,k);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_spent = (end.tv_sec - start.tv_sec);
    time_spent += (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    if(rtrn == -1){
        printf("Error\n");
    }
    else{
        printf("Fermat: %s\n", rtrn==1 ? "Prime" : "Composite");
        if(DISPLAY_TIME) printf("\tTime: %f\n", time_spent);
    }



    //MILLER-RABIN 
    clock_gettime(CLOCK_MONOTONIC, &start);
    if(ACTIVE_THREADS){
        //WITHTHREADS
        rtrn = Miller_Rabin_with_threads(n,k,NB_THREADS);
    }
    else{
        //NO THREADS
        rtrn = Miller_Rabin(n,k);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_spent = (end.tv_sec - start.tv_sec);
    time_spent += (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    if(rtrn == -1){
        printf("Error\n");
    }
    else{
        printf("Miller-Rabin: %s\n", rtrn==1 ? "Prime" : "Composite");
        if(DISPLAY_TIME) printf("\tTime: %f\n", time_spent);
    }
    

    mpz_clears(n,k,n_1,NULL);

    return 0;
}