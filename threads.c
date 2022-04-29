#include "threads.h"


//-----------------FERMAT-----------------

//Function that will use threads to run Fermat
int Fermat_with_threads(mpz_t n, mpz_t k, int nb_threads){
    pthread_t threads[nb_threads];
    //if k/nb_threads is not an integer, we will have to put a different number of iteration on the last threads, 
    //and complement determine the number of threads
    int complement = 1;
    values* args = malloc(sizeof(values));
    values* last = malloc(sizeof(values));

    mpz_inits(args->n, args->k, last->n, last->k, NULL);
    mpz_set(args->n, n);
    mpz_set(last->n, n);
    args->ret = 1;
    last->ret = 1;


    if(mpz_get_ui(k)%nb_threads == 0){
        //if k is divisible by nb_threads we distribute k/nb_threads iterations on each thread
        mpz_divexact_ui(args->k, k, nb_threads);
        mpz_divexact_ui(last->k, k, nb_threads);
    }
    else if(mpz_get_ui(k)%(nb_threads-1) == 0){
        //if k is divisible by nb_threads-1 we distribute k/nb_threads 
        //iterations on each thread and add the rest to the last thread
        mpz_mod_ui(last->k, k, nb_threads);
        mpz_divexact_ui(args->k, k, nb_threads);
        mpz_add(last->k, last->k, args->k);
    }
    else if(mpz_get_ui(k)<nb_threads){
        //if k is smaller than nb_threads each thread will have to run 1 iteration
        // and the last thread will run nothing 
        //(complement will tell how many threads will not run)
        mpz_set_ui(last->k, 0);
        mpz_set_ui(args->k, 1);
        complement = nb_threads - mpz_get_ui(k);
    }
    else{
        // we distribute k/nb_threads iterations on each thread 
        // and add the rest to the last thread
        mpz_mod_ui(last->k, k, nb_threads-1);
        mpz_sub(args->k, k, last->k);
        mpz_divexact_ui(args->k, args->k, nb_threads-1);
    }

    //creation of the table of random values
    args->tab = malloc(sizeof(mpz_t)*mpz_get_ui(k));
    if(args->tab == NULL){
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
        while (check_tab(args->tab, i, a) == 1){// check if a is already in the table
            mpz_urandomm(a, rstate, n_2);
            mpz_add_ui(a, a, 1);
        }
    }
    last->tab = args->tab;
    args->id=0;

    //create the threads
    for(int i = 0; i < nb_threads ; i++){
        if(i<nb_threads-complement)
        {
            pthread_create(&threads[i], NULL, Fermat_for_threads, (void*)args);
            args->id += mpz_get_ui(args->k);
            last->id = args->id;
        }
        else if(last->k > 0) //if last->k is 0, we don't need to create a thread
        {
            pthread_create(&threads[i], NULL, Fermat_for_threads, (void*)last);
        }
    }

    int ret = 1;
    for(int i = 0; i < nb_threads; i++){
        pthread_join(threads[i], NULL);
        if((args->ret == 0) || (last->ret == 0)){
            ret = 0;
        }
    }

    mpz_clears(args->n, args->k, last->n, last->k, NULL);
    mpz_clears(a,n_2,NULL);
    gmp_randclear(rstate);
    free_tab(args->tab, mpz_get_ui(k));
    free(args);
    free(last);
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

        mpz_set(a, v->tab[v->id+i]); //take one of the random a

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
        mpz_urandomm(a, rstate, n_1);// set a random number between 1 and n-1(included)
        mpz_add_ui(a, a, 1);

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
    //if k/nb_threads is not an integer, we will have to put a different number of iteration on the last threads, 
    //and complement determine the number of threads
    int complement = 1;

    values* args = malloc(sizeof(values));
    values* last = malloc(sizeof(values));

    mpz_inits(args->n, args->k, args->s, args->t, last->n, last->k, last->s, last->t, NULL);
    mpz_set(args->n, n);
    mpz_set(last->n, n);
    args->ret = 1;
    last->ret = 1;

    //we use decompose only once before creating the threads
    decompose(n, args->s, args->t); // decompose n-1 in 2^s * t and store s and t
    mpz_set(last->s, args->s);
    mpz_set(last->t, args->t);


    if(mpz_get_ui(k)%nb_threads == 0){
        //if k is divisible by nb_threads we distribute k/nb_threads iterations on each thread
        mpz_divexact_ui(args->k, k, nb_threads);
        mpz_divexact_ui(last->k, k, nb_threads);
    }
    else if(mpz_get_ui(k)%(nb_threads-1) == 0){
        //if k is divisible by nb_threads-1 we distribute k/nb_threads 
        //iterations on each thread and add the rest to the last thread
        mpz_mod_ui(last->k, k, nb_threads);
        mpz_divexact_ui(args->k, k, nb_threads);
        mpz_add(last->k, last->k, args->k);
    }
    else if(mpz_get_ui(k)<nb_threads){
        //if k is smaller than nb_threads each thread will have to run 1 iteration
        // and the last thread will run nothing 
        //(complement will tell how many threads will not run)
        mpz_set_ui(last->k, 0);
        mpz_set_ui(args->k, 1);
        complement = nb_threads - mpz_get_ui(k);
    }
    else{
        // we distribute k/nb_threads iterations on each thread 
        // and add the rest to the last thread
        mpz_mod_ui(last->k, k, nb_threads-1);
        mpz_sub(args->k, k, last->k);
        mpz_divexact_ui(args->k, args->k, nb_threads-1);
    }

    //creation of the table of random values
    args->tab = malloc(sizeof(mpz_t)*mpz_get_ui(k));
    if(args->tab == NULL){
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
        while (check_tab(args->tab, i, a) == 1){// check if a is already in the table
            mpz_urandomm(a, rstate, n_2);
            mpz_add_ui(a, a, 1);
        }
    }
    last->tab = args->tab;
    args->id=0;


    //create the threads
    for(int i = 0; i < nb_threads ; i++){
        if(i<nb_threads-complement)
        {
            pthread_create(&threads[i], NULL, Fermat_for_threads, (void*)args);
            args->id += mpz_get_ui(args->k);
            last->id = args->id;
        }
        else if(last->k > 0) //if last->k is 0, we don't need to create a thread
        {
            pthread_create(&threads[i], NULL, Fermat_for_threads, (void*)last);
        }
    }

    int ret = 1;
    for(int i = 0; i < nb_threads; i++){
        pthread_join(threads[i], NULL);
        if((args->ret == 0) || (last->ret == 0)){
            ret = 0;
        }
    }

    mpz_clears(args->n, args->k, args->s, args->t, last->n, last->k, last->s, last->t, NULL);
    mpz_clears(a,n_2,NULL);
    gmp_randclear(rstate);
    free_tab(args->tab, mpz_get_ui(k));
    free(args);
    free(last);
    return ret;
}