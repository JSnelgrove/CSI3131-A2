/*  Jack Snelgrove
    300247435
*/
#include <stdio.h>
#include <pthread.h>

int a, b, turn;

pthread_mutex_t lock;
pthread_cond_t cond;

void *thr0() {
    for (int i = 0; i < a; ++i) {
        pthread_mutex_lock(&lock);
        while (turn % 4 != 0) {
            pthread_cond_wait(&cond, &lock);
        }
        b += 1;
        printf("Thr0, (b + 1 = %d)\n", b);
        turn++;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *thr1() {
    for (int i = 0; i < a; ++i) {
        pthread_mutex_lock(&lock);
        while (turn % 4 != 1) {
            pthread_cond_wait(&cond, &lock);
        }
        b += 2;
        printf("Thr1, (b + 2 = %d)\n", b);
        turn++;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *thr2() {
    for (int i = 0; i < a; ++i) {
        pthread_mutex_lock(&lock);
        while (turn % 4 != 2) {
            pthread_cond_wait(&cond, &lock);
        }
        b += 3;
        printf("Thr2, (b + 3 = %d)\n", b);
        turn++;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *thr3() {
    for (int i = 0; i < a; ++i) {
        pthread_mutex_lock(&lock);
        while (turn % 4 != 3) {
            pthread_cond_wait(&cond, &lock);
        }
        b += 4;
        printf("Thr3, (b + 4 = %d)\n", b);
        turn++;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
void displayFib(){
    int n1=1;
    int n2=1;
    int n3;
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

    pthread_t threads[4];

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    void *(*thr_functions[4])() = {thr0, thr1, thr2, thr3};

    printf("Enter integer a value: ");
    scanf("%d", &a);
    while (a<0){
        printf("Invalid input\nMust be a positive number (including 0)\nPlease try again: ");
        scanf("%d", &a);
    }
    printf("Enter integer b value: ");
    scanf("%d", &b);
    while (b<0){
        printf("Invalid input\nMust be a positive number (including 0)\nPlease try again: ");
        scanf("%d", &b);
    }
    printf("Enter Thread # to start first (0-3): ");
    scanf("%d", &turn);
    while (turn>3 || turn<0){
        printf("Invalid input\nMust be a value between 0-3\nTry again:");
        scanf("%d", &turn);
    }
    printf("A: %d\nB: %d\nTurn: %d\n", a, b, turn);
    

    for (int i = 0; i < 4; i++) {
        if (pthread_create(&threads[i],NULL, thr_functions[i], NULL)!= 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }
    
    for (int i = 0; i < 4; i++) {
        if (pthread_join(threads[i], NULL)) {
            fprintf(stderr, "Error joining thread %d\n", i);
            return 2;
        }
    }
    printf("Parent, (b = %d)\n",b);

    printf("The Fibonacci sequence for %d is:\n", b);

    displayFib();
    
    return 0; 
}