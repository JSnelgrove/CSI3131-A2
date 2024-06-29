/*  Jack Snelgrove
    300247435
*/
#include <stdio.h>
#include <pthread.h>

int a, b, turn; //Global variables 

pthread_mutex_t lock; //Mutex lock to ensure mutual exlusion
pthread_cond_t cond; //Mutex condition to specify when a thread can access critical section


//Implementation for thread 0 function
void *thr0() {
    for (int i = 0; i < a; ++i) { // repeats a times
        pthread_mutex_lock(&lock); // ensure mutual exlusion to critical section
        while (turn % 4 != 0) { // sleeps until it is the turn of thr0
            pthread_cond_wait(&cond, &lock); 
        }
        b += 1;
        printf("Thr0, (b + 1 = %d)\n", b);
        turn++;
        pthread_cond_broadcast(&cond); // wakes up each thread to check if it is their turn
        pthread_mutex_unlock(&lock); // releases the mutex lock
    }
    return NULL;
}

//Implementation for thread 1 function
void *thr1() {
    for (int i = 0; i < a; ++i) { // repeats a times
        pthread_mutex_lock(&lock);  // ensure mutual exlusion to critical section
        while (turn % 4 != 1) { // sleeps until it is the turn of thr0
            pthread_cond_wait(&cond, &lock);
        }
        b += 2;
        printf("Thr1, (b + 2 = %d)\n", b);
        turn++;
        pthread_cond_broadcast(&cond); // wakes up each thread to check if it is their turn
        pthread_mutex_unlock(&lock); // releases the mutex lock
    }
    return NULL;
}

//Implementation for thread 2 function
void *thr2() {
    for (int i = 0; i < a; ++i) { // repeats a times
        pthread_mutex_lock(&lock); // ensure mutual exlusion to critical section
        while (turn % 4 != 2) { // sleeps until it is the turn of thr0
            pthread_cond_wait(&cond, &lock);
        }
        b += 3;
        printf("Thr2, (b + 3 = %d)\n", b);
        turn++;
        pthread_cond_broadcast(&cond); // wakes up each thread to check if it is their turn
        pthread_mutex_unlock(&lock); // releases the mutex lock
    }
    return NULL;
}

//Implementation for thread 3 function
void *thr3() {
    for (int i = 0; i < a; ++i) { // repeats a times
        pthread_mutex_lock(&lock); // ensure mutual exlusion to critical section
        while (turn % 4 != 3) { // sleeps until it is the turn of thr0
            pthread_cond_wait(&cond, &lock);
        }
        b += 4; 
        printf("Thr3, (b + 4 = %d)\n", b);
        turn++;
        pthread_cond_broadcast(&cond); // wakes up each thread to check if it is their turn
        pthread_mutex_unlock(&lock); // releases the mutex lock
    }
    return NULL;
}
void displayFib(){
    int n1=1; // first index
    int n2=1; // second index
    int n3; // third index (tbd)

    // prints fib sequence of b derived from psuedo code given is a2 documentation
    if (b==1){ 
        printf("1");
    }
    else{
        printf("1 1");
        for (int i=2; i<b;i++){
            n3=n1+n2;
            n1=n2;
            n2=n3;
            printf(" %d",n3);
        }

    }

}

int main(void){
    pthread_t threads[4];// initiates 4 threads

    pthread_mutex_init(&lock, NULL);// initiates mutex lock
    pthread_cond_init(&cond, NULL);// initiates mutex condition

    void *(*thr_functions[4])() = {thr0, thr1, thr2, thr3}; //defines an array of thread functions 

    // Gets input for a 
    printf("Enter integer a value: ");
    scanf("%d", &a);
    while (a<0){
        printf("Invalid input\nMust be a positive number (including 0)\nPlease try again: ");
        scanf("%d", &a);
    }

    //Gets input for b
    printf("Enter integer b value: ");
    scanf("%d", &b);
    while (b<0){
        printf("Invalid input\nMust be a positive number (including 0)\nPlease try again: ");
        scanf("%d", &b);
    }

    //Gets input for turn
    printf("Enter Thread # to start first (0-3): ");
    scanf("%d", &turn);
    while (turn>3 || turn<0){
        printf("Invalid input\nMust be a value between 0-3\nTry again:");
        scanf("%d", &turn);
    }
    
    // Creates all 4 threads and assigns them a function from the function array
    for (int i = 0; i < 4; i++) {
        if (pthread_create(&threads[i],NULL, thr_functions[i], NULL)!= 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }
    
    // Waits for all threads to complete 
    for (int i = 0; i < 4; i++) {
        if (pthread_join(threads[i], NULL)) {
            fprintf(stderr, "Error joining thread %d\n", i);
            return 2;
        }
    }
    // Display final value of b 
    printf("Parent, (b = %d)\n",b);

    // Display fib sequence of b
    printf("The Fibonacci sequence for %d is:\n", b);
    displayFib();
    
    return 0; 
}