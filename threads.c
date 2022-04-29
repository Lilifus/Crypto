#include "threads.h"


//-----------------FERMAT-----------------

//Function that will use threads to run Fermat
int Fermat_with_threads(mpz_t n, mpz_t k, int nb_threads){
    pthread_t threads[nb_threads];

    values* args = malloc(sizeof(values)*nb_threads);

    for(int i = 0; i < nb_threads; i++){
        mpz_inits(args[i].n, args[i].k, NULL);
        mpz_set(args[i].n, n);
        args[i].ret = 1;
    }


    if(mpz_get_ui(k)%nb_threads == 0){
        //if k is divisible by nb_threads we distribute k/nb_threads iterations on each thread
        for(int i = 0; i< nb_threads - 1; i++) mpz_divexact_ui(args[i].k, k, nb_threads);
        mpz_divexact_ui(args[nb_threads-1].k, k, nb_threads);
    }
    else if(mpz_get_ui(k)%(nb_threads-1) == 0){
        //if k is divisible by nb_threads-1 we distribute k/nb_threads 
        //iterations on each thread and add the rest to the last thread
        mpz_mod_ui(args[nb_threads-1].k, k, nb_threads);
        for(int i = 0; i< nb_threads - 1; i++) mpz_divexact_ui(args[i].k, k, nb_threads);
        mpz_add(args[nb_threads-1].k, args[nb_threads-1].k, args[0].k);
    }
    else if(mpz_get_ui(k)<nb_threads){
        //if k is smaller than nb_threads each thread will have to run 1 iteration
        // and the last thread will run nothing 
        //(complement will tell how many threads will not run)
        mpz_set_ui(args[nb_threads-1].k, 0);
        for(int i = 0; i< nb_threads - 1; i++) mpz_set_ui(args[i].k, 1);
    }
    else{
        // we distribute k/nb_threads iterations on each thread 
        // and add the rest to the last thread
        mpz_mod_ui(args[nb_threads-1].k, k, nb_threads-1);
        for(int i = 0; i< nb_threads - 1; i++) mpz_sub(args[i].k, k, args[nb_threads-1].k);
        for(int i = 0; i< nb_threads - 1; i++) mpz_divexact_ui(args[i].k, args[i].k, nb_threads-1);
    }

    //creation of the table of random values
    mpz_t* tab = malloc(sizeof(mpz_t)*mpz_get_ui(k));
    if(tab == NULL){
        printf("Erreur d'allocation de mémoire\n");
        return -1;
    }

    mpz_t a,n_2;
    mpz_inits(a,n_2,NULL);
    mpz_sub_ui(n_2, n, 2);
    gmp_randstate_t rstate; // seed for random number generation
    gmp_randinit_default(rstate);
    gmp_randseed_ui(rstate, time(NULL));
    for(int i=0; i<mpz_get_ui(k); i++){
        mpz_urandomm(a, rstate, n_2); // a = rand(1,n-2) (n-2 included)
        mpz_add_ui(a, a, 1);
        while (check_tab(tab, i, a) == 1){// check if a is already in the table
            mpz_urandomm(a, rstate, n_2);
            mpz_add_ui(a, a, 1);
        }
    }
    
    int l = 0;
    for(int i = 0; i < nb_threads; i++){
        args[i].a = malloc(sizeof(mpz_t)*mpz_get_ui(args[i].k));
        for(int j=0;j<mpz_get_ui(args[i].k);j++){
            mpz_init(args[i].a[j]);
            mpz_set(args[i].a[j], tab[l]);
            l++;
        }
    }


    //create the threads
    for(int i = 0; i < nb_threads ; i++){
        if(args[i].k>0) pthread_create(&threads[i], NULL, Fermat_for_threads, (void*)args);
    }

    int ret = 1;
    for(int i = 0; i < nb_threads; i++){
        pthread_join(threads[i], NULL);
        if(args[i].ret == 0){
            ret = 0;
        }
    }

    mpz_clears(a,n_2,NULL);
    
    gmp_randclear(rstate);
    
    for(int i = 0; i< nb_threads - 1; i++) {
        free_tab(args[i].a, mpz_get_ui(args[i].k));
        mpz_clears(args[i].n, args[i].k, NULL); 
    }
    free(args);
    return ret;
}





//Function used in threads for fermat
void* Fermat_for_threads(void* arg){

    values* v = (values*) arg; // struct that contains n,k and the return value
    mpz_t n;
    mpz_t k;
    mpz_inits(n, k, NULL);
    mpz_set(n, v->n);
    mpz_set(k, v->k);

    
    mpz_t *tab = malloc(sizeof(mpz_t)*mpz_get_ui(k)); //the table that will contain the all the random a used
    if(tab == NULL){
        printf("Erreur d'allocation de mémoire\n");
        exit(-1);
    }
    
    mpz_t h, a, r, n_2;
    mpz_inits(h, a, r, n_2, NULL);

    mpz_sub_ui(n_2, n, 2);
    mpz_sub_ui(h, n, 1);//set the exponent to n-1
    for(int i = 0; mpz_cmp_ui(k,i)>0; i++){

        mpz_set(a, v->a[i]); //take one of the random a

        square_and_multiply(a,n,h,r);
        if(mpz_cmp_ui(r, 1)){ // if r != 1 mod n
            mpz_clears(h, a, r, n_2, NULL);
            v->ret = 0; // replace "return 0;"
            pthread_exit(NULL);
        }
    }
    mpz_clears(h, a, r, n_2, NULL);
    //no need for a return 1 because v->ret is already set to 1
    pthread_exit(NULL);
}



// -----------------MILLER RABIN-----------------



//Function used in threads for miller_rabin
void* Miller_Rabin_for_thread(void* arg){
    values* args = (values*) arg; // struct containing the n, k, s, t and the return value
    
    mpz_t n, k, s, t;
    mpz_inits(n, k, s, t, NULL);
    mpz_set(n, args->n);
    mpz_set(k, args->k);  
    mpz_set(s, args->s);
    mpz_set(t, args->t);
    

    mpz_t two, n_1, a, y;      
    gmp_randstate_t rstate;
    mpz_inits(two, n_1, a, y, NULL);
    mpz_sub_ui(n_1, n, 1);
    mpz_set_ui(two, 2);
    gmp_randinit_default(rstate);
    gmp_randseed_ui(rstate, time(NULL));

    for(int i = 1; i <= mpz_get_ui(k); i++){  
        mpz_set(a, args->a[i-1]);

        square_and_multiply(a,n,t,y);

        if(mpz_cmp_ui(y, 1) && mpz_cmp(y, n_1)){ // if y != 1 mod n and y != -1 mod n
            for(int j = 1; mpz_cmp_ui(s,j)>0; j++){
                square_and_multiply(y,n,two,y);
                if(!mpz_cmp_ui(y, 1)){ // if y == 1 mod n
                    mpz_clears(s, t, two, n_1, a, y, NULL);
                    gmp_randclear(rstate);
                    args->ret = 0; // n is composite
                    return NULL;
                }
                if(!mpz_cmp(y, n_1)){ // if y == -1 mod n
                    break;
                }
            }
            // the if is needed to go to the next iteration without returning composite by mistake
            if(mpz_cmp(y, n_1)){ // if y != -1 mod n
                mpz_clears(s, t, two, n_1, a, y, NULL);
                gmp_randclear(rstate);
                args->ret = 0; // n is composite
                return NULL;
            }
        }
    }
    mpz_clears(n, k, s, t, two, n_1, a, y, NULL);
    gmp_randclear(rstate);
    // n is prime
    return NULL;
}




//thread using fuction for miller-rabin
int Miller_Rabin_with_threads(mpz_t n, mpz_t k, int nb_threads){
    pthread_t threads[nb_threads];

    values* args = malloc(sizeof(values)*nb_threads);

    mpz_t s,t;
    mpz_inits(s, t, NULL);
    //we use decompose only once before creating the threads
    decompose(n, s, t); // decompose n-1 in 2^s * t and store s and t

    for(int i = 0; i < nb_threads; i++){
        mpz_inits(args[i].n, args[i].k, args[i].s, args[i].t, NULL);
        mpz_set(args[i].n, n);
        args[i].ret = 1;
        mpz_set(args[i].s, s);
        mpz_set(args[i].t, t);
    }



    if(mpz_get_ui(k)%nb_threads == 0){
        //if k is divisible by nb_threads we distribute k/nb_threads iterations on each thread
        for(int i = 0; i< nb_threads - 1; i++) mpz_divexact_ui(args[i].k, k, nb_threads);
        mpz_divexact_ui(args[nb_threads-1].k, k, nb_threads);
    }
    else if(mpz_get_ui(k)%(nb_threads-1) == 0){
        //if k is divisible by nb_threads-1 we distribute k/nb_threads 
        //iterations on each thread and add the rest to the last thread
        mpz_mod_ui(args[nb_threads-1].k, k, nb_threads);
        for(int i = 0; i< nb_threads - 1; i++) mpz_divexact_ui(args[i].k, k, nb_threads);
        mpz_add(args[nb_threads-1].k, args[nb_threads-1].k, args[0].k);
    }
    else if(mpz_get_ui(k)<nb_threads){
        //if k is smaller than nb_threads each thread will have to run 1 iteration
        // and the last thread will run nothing 
        //(complement will tell how many threads will not run)
        mpz_set_ui(args[nb_threads-1].k, 0);
        for(int i = 0; i< nb_threads - 1; i++) mpz_set_ui(args[i].k, 1);
    }
    else{
        // we distribute k/nb_threads iterations on each thread 
        // and add the rest to the last thread
        mpz_mod_ui(args[nb_threads-1].k, k, nb_threads-1);
        for(int i = 0; i< nb_threads - 1; i++) mpz_sub(args[i].k, k, args[nb_threads-1].k);
        for(int i = 0; i< nb_threads - 1; i++) mpz_divexact_ui(args[i].k, args[i].k, nb_threads-1);
    }

    //creation of the table of random values
    mpz_t* tab = malloc(sizeof(mpz_t)*mpz_get_ui(k));
    if(tab == NULL){
        printf("Erreur d'allocation de mémoire\n");
        return -1;
    }

    mpz_t a,n_2;
    mpz_inits(a,n_2,NULL);
    mpz_sub_ui(n_2, n, 2);
    gmp_randstate_t rstate; // seed for random number generation
    gmp_randinit_default(rstate);
    gmp_randseed_ui(rstate, time(NULL));
    for(int i=0; i<mpz_get_ui(k); i++){
        mpz_urandomm(a, rstate, n_2); // a = rand(1,n-2) (n-2 included)
        mpz_add_ui(a, a, 1);
        while (check_tab(tab, i, a) == 1){// check if a is already in the table
            mpz_urandomm(a, rstate, n_2);
            mpz_add_ui(a, a, 1);
        }
    }
    
    int l = 0;
    for(int i = 0; i < nb_threads; i++){
        args[i].a = malloc(sizeof(mpz_t)*mpz_get_ui(args[i].k));
        for(int j=0;j<mpz_get_ui(args[i].k);j++){
            mpz_init(args[i].a[j]);
            mpz_set(args[i].a[j], tab[l]);
            l++;
        }
    }


    //create the threads
    for(int i = 0; i < nb_threads ; i++){
        if(args[i].k>0) pthread_create(&threads[i], NULL, Miller_Rabin_for_thread, (void*)args);
    }

    int ret = 1;
    for(int i = 0; i < nb_threads; i++){
        pthread_join(threads[i], NULL);
        if(args[i].ret == 0){
            ret = 0;
        }
    }

    mpz_clears(a,n_2,NULL);
    gmp_randclear(rstate);
    for(int i = 0; i< nb_threads - 1; i++) {
        free_tab(args[i].a, mpz_get_ui(args[i].k));
        mpz_clears(args[i].n, args[i].k, args[i].s, args[i].t, NULL);
    }
    free(args);
    return ret;
}