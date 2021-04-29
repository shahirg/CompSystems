#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#define NUM_TEAMS 4
// SIGINT, SIGABRT, SIGILL, SIGCHLD 
// SIGSEGV, SIGFPE, SIGHUP, SIGTSTP

// FUNCTION PROTOTYPES
void sig_handler1(int sig);
void sig_handler2(int sig);
void sig_handler3(int sig);
void sig_handler4(int sig);
void* thread_func1();
void* thread_func2();
void* thread_func3();
void* thread_func4();

pthread_t tid[NUM_TEAMS]; // 4 thread teams

int main(int argc, char ** argv){
    
    pthread_attr_t attr[NUM_TEAMS];
    sigset_t set[NUM_TEAMS];
    
    int i,split;

    // EACH TEAM ASSIGNED 3 SIGNALS

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

        pthread_sigmask(SIG_BLOCK, &set[i],NULL);
        pthread_attr_init(&attr[i]);
        pthread_create(&tid[i],&attr[i],(void*) thread_func1,NULL);
    }
    
    


    // send signals to thread
    // sleep(1);
    // pthread_kill(tid[0],SIGINT);
    // pthread_kill(tid[0],SIGTSTP);
    
    // pthread_kill(tid[0],SIGABRT);


    // pthread_kill(tid[1],SIGILL);

    void* retvalue;
    int * ret;

    // CLOSE THREADS
    for(i = 0; i < 4; i++){
        pthread_join(tid[i],NULL);

    }
    
    return 0;
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

    sleep(2);

}

// TEAM 2 FUNCTION
void* thread_func2(void * arg){
    fprintf(stdout, "Thread %d created\n",(int)pthread_self());
    
    
    sleep(2);

}

// TEAM 3 FUNCTION
void* thread_func3(void * arg){
    fprintf(stdout, "Thread %d created\n",(int)pthread_self());

    
    sleep(2);

}

// TEAM 4 FUNCTION
void* thread_func4(void * arg){
    fprintf(stdout, "Thread %d created\n",(int)pthread_self());

    //Terminate the other threads
    pthread_kill(tid[0], SIGINT);
    sleep(1);
    pthread_kill(tid[0], SIGINT);
    
    pthread_kill(tid[1], SIGINT);
    sleep(1);
    pthread_kill(tid[1], SIGINT);
    
    pthread_kill(tid[2], SIGINT);
    sleep(1);
    pthread_kill(tid[2], SIGINT);
    
    pthread_kill(pthread_self(), SIGINT);
    sleep(1);
    pthread_kill(pthread_self(), SIGINT);

    sleep(2);

}