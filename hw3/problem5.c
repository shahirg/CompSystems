#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *getPrimes(void *_args);
void printPrimes(int arr[], int n);

int main(int argc, char **argv) {
    int n;
    pthread_t tid;
    for (;;){
        printf("n = ");
        scanf("%d",&n);
        if((pthread_create(&tid, NULL, &getPrimes, (void *)&n)) !=0){
            fprintf(stderr,"Thread Creation Failed");
            exit(EXIT_FAILURE);
        }
        pthread_join(tid,NULL);
    }
    return EXIT_SUCCESS;
}

void *getPrimes(void *_args){
    int i,j;
    int n = *((int*)_args);
    int A[n+1]; /* init array length n */

    memset(A,1,sizeof(A)); /* set all values in array to true */

    for(i = 2; i*i <= n; i++){
        if(A[i]){
            for(j = i*i; j <= n; j += i){
                A[j] = 0;
            }
        }        
    }
    A[2] = 0; 
    printPrimes(A,n);
    return NULL;
}
void printPrimes(int arr[], int n){
    int i;
    for(i = 3; i <= n; i+=2){
        if(arr[i]){
            printf("%d ",i);
        }
    }
    printf("\n");
}