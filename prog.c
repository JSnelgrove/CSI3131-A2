/*  Jack Snelgrove
    300247435
*/
#include <stdio.h>
#include <pthread.h>


int main(void){
    int a, b, turn;
    printf("Enter a positive integer for a: ");
    scanf("%d", &a);
    while (a<0){
        printf("Invalid input\nTry again:");
        scanf("%d", &a);
    }
    printf("Enter a positive integer for b: ");
    scanf("%d", &b);
    while (b<0){
        printf("Invalid input\nTry again:");
        scanf("%d", &b);
    }
    printf("Enter a positive integer between 0 and 3 for turn: ");
    scanf("%d", &turn);
    while (turn>3 || turn<0){
        printf("Invalid input\nTry again:");
        scanf("%d", &turn);
    }
    printf("A: %d\nB: %d\nTurn: %d\n", a, b, turn);
    return 0; 
}