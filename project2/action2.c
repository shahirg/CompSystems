#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#define ARR_SIZE 20
#define NUM_TEAMS 4
// SIGINT, SIGABRT, SIGILL, SIGCHLD 
// SIGSEGV, SIGFPE, SIGHUP, SIGTSTP

// FUNCTION PROTOTYPES
int* selectionSort(int arr[], int start, int end);
void swap(int *xp, int *yp);
void printArray(int arr[], int size);
void sig_handler1(int sig);
void sig_handler2(int sig);
void sig_handler3(int sig);
void sig_handler4(int sig);
void* thread_func1();
void* thread_func2();
void* thread_func3();
void* thread_func4();

// structure passed for sorting array
typedef struct data{
    int thread_num;
    int start;
    int end;
    int arr[ARR_SIZE];
} data;

int main(int argc, char ** argv){
    pthread_t tid[NUM_TEAMS]; // 4 thread teams
    pthread_attr_t attr[NUM_TEAMS];
    sigset_t set[NUM_TEAMS];
    data sorting_data[NUM_TEAMS];
    int i,split;
    int arr[ARR_SIZE];

    //Generate random array
    srand(0);
    for(i = 0;i <ARR_SIZE; i++){
        arr[i] = rand() % 100 + 1; //Range of nums: 1-100
    }
    split = (int)(ARR_SIZE/NUM_TEAMS);

    //EACH TEAM ASSIGNED 3 SIGNALS

    //Team 1 - SIGINT, SIGABRT, SIGILL
    signal(SIGINT,sig_handler1);
    signal(SIGABRT,sig_handler1);
    signal(SIGILL,sig_handler1);

    //TEAM 2 - SIGABRT, SIGILL, SIGHCHLD
    signal(SIGABRT,sig_handler2);
    signal(SIGILL,sig_handler2);
    signal(SIGCHLD,sig_handler2);

    //TEAM 3 - SIGSEGV, SIGFPE, SIGHUP
    signal(SIGSEGV,sig_handler3);
    signal(SIGFPE,sig_handler3);
    signal(SIGHUP,sig_handler3);

    //TEAM 4 - SIGFPE, SIGHUP, SIGTSTP
    signal(SIGFPE,sig_handler4);
    signal(SIGHUP,sig_handler4);
    signal(SIGTSTP,sig_handler4);

    //CREATE TEAM 1

    for(i = 0; i < 4; i++){
        
        if(i == 0){ // Blocked signals TEAM 1
            sigemptyset(&set[0]);
            sigaddset(&set[0],SIGCHLD);
            sigaddset(&set[0],SIGSEGV);
            sigaddset(&set[0],SIGFPE);
            sigaddset(&set[0],SIGHUP);
            sigaddset(&set[0],SIGTSTP);
        }
        else if(i == 1){ // Blocked signals TEAM 2
            sigemptyset(&set[1]);
            sigaddset(&set[1],SIGINT);
            sigaddset(&set[1],SIGSEGV);
            sigaddset(&set[1],SIGFPE);
            sigaddset(&set[1],SIGHUP);
            sigaddset(&set[1],SIGTSTP);
        }
        else if(i == 2){ // Blocked signals TEAM 3
            sigemptyset(&set[2]);
            sigaddset(&set[2],SIGINT);
            sigaddset(&set[2],SIGABRT);
            sigaddset(&set[2],SIGILL);
            sigaddset(&set[2],SIGCHLD);
            sigaddset(&set[2],SIGTSTP);         
        }
        else if (i ==3){ // Blocked signals TEAM 4
            sigemptyset(&set[3]);
            sigaddset(&set[3],SIGINT);
            sigaddset(&set[3],SIGABRT);
            sigaddset(&set[3],SIGILL);
            sigaddset(&set[3],SIGCHLD);
            sigaddset(&set[3],SIGSEGV);
        }
        sorting_data[i].thread_num = i;
        sorting_data[i].start = i == 0 ? split* i : sorting_data[i-1].end +1;
        sorting_data[i].end = i != NUM_TEAMS -1 ? split * (i+1) : ARR_SIZE;
        pthread_sigmask(SIG_BLOCK, &set[i],NULL);
        pthread_attr_init(&attr[i]);
        pthread_create(&tid[i],&attr[i],(void*) thread_func1,&sorting_data[i]);
    }
    
    


    // send signals to thread
    sleep(1);
    pthread_kill(tid[0],SIGINT);
    pthread_kill(tid[0],SIGTSTP);
    
    pthread_kill(tid[0],SIGABRT);


    pthread_kill(tid[1],SIGILL);

    void* retvalue;
    int * ret;

    // CLOSE THREADS
    for(i = 0; i < 4; i++){
        pthread_join(tid[i],&retvalue);
        ret = (int*)retvalue;
        printArray(ret,ARR_SIZE);

    }
    
    return 0;
}

//SELECTION SORT
int * selectionSort(int arr[], int start, int end){
    int i, j, min_idx;
  
    // One by one move boundary of unsorted subarray
    for (i = start; i < end-1; i++){
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < end; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;
  
        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
    return arr;
}

void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
/* Function to print an array */
void printArray(int arr[], int size){
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// TEAM 1 HANDLER
void sig_handler1(int sig) {
    fprintf(stdout,"thread %d caught signal num %d\n",(int)pthread_self(),sig);
    sleep(2);
    //write(1, "Caught signal no = %d\n",sig);
}

// TEAM 2 HANDLER
void sig_handler2(int sig) {
    fprintf(stdout,"thread %d caught signal num %d\n",(int)pthread_self(),sig);
}

// TEAM 3 HANDLER
void sig_handler3(int sig) {
    fprintf(stdout,"thread %d caught signal num %d\n",(int)pthread_self(),sig);
}

//TEAM 4 HANDLER
void sig_handler4(int sig) {
    fprintf(stdout,"thread %d caught signal num %d\n",(int)pthread_self(),sig);
}

// TEAM 1 FUNCTION
void* thread_func1(void * arg){
    fprintf(stdout, "Thread %d created\n",(int)pthread_self());
    
    data sort_data = *((data*)arg);
    printf("i = %d: start =  %d end = %d\n", sort_data.thread_num , sort_data.start, sort_data.end);
    // SORT
    int * arr;
    arr = selectionSort(sort_data.arr,sort_data.start,sort_data.end);

    sleep(2);
    pthread_exit((void*)arr);
}

// TEAM 2 FUNCTION
void* thread_func2(void * arg){
    fprintf(stdout, "Thread %d created\n",(int)pthread_self());
    
    data sort_data = *((data*)arg);
    printf("i = %d: start =  %d end = %d\n", sort_data.thread_num , sort_data.start, sort_data.end);
    // SORT
    int * arr;
    arr = selectionSort(sort_data.arr,sort_data.start,sort_data.end);

    sleep(2);
    pthread_exit((void*)arr);
}

// TEAM 3 FUNCTION
void* thread_func3(void * arg){
    fprintf(stdout, "Thread %d created\n",(int)pthread_self());

    data sort_data = *((data*)arg);
    printf("i = %d: start =  %d end = %d\n", sort_data.thread_num , sort_data.start, sort_data.end);
    int * arr;
    arr = selectionSort(sort_data.arr,sort_data.start,sort_data.end);

    sleep(2);
    pthread_exit((void*)arr);
}

// TEAM 4 FUNCTION
void* thread_func4(void * arg){
    fprintf(stdout, "Thread %d created\n",(int)pthread_self());

    data sort_data = *((data*)arg);
    printf("i = %d: start =  %d end = %d\n", sort_data.thread_num , sort_data.start, sort_data.end);
    // SORT
    int * arr;
    arr = selectionSort(sort_data.arr,sort_data.start,sort_data.end);
    
    sleep(2);
    pthread_exit((void*)arr);
}