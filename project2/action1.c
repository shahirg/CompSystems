#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

// SIGINT, SIGABRT, SIGILL, SIGCHLD 
// SIGSEGV, SIGFPE, SIGHUP, SIGTSTP

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
void thread_func1(){
    fprintf(stdout, "Thread %d created\n",(int)pthread_self());
    sleep(2);
}

// TEAM 2 FUNCTION
void thread_func2(){
    fprintf(stdout, "Thread %d created\n",(int)pthread_self());
    sleep(2);
}

// TEAM 3 FUNCTION
void thread_func3(){
    fprintf(stdout, "Thread %d created\n",(int)pthread_self());
    sleep(2);
}

// TEAM 4 FUNCTION
void thread_func4(){
    fprintf(stdout, "Thread %d created\n",(int)pthread_self());
    sleep(2);
}

int main(int argc, char ** argv){
    pthread_t tid[4]; // 4 thread teams
    pthread_attr_t attr[4];

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
    pthread_attr_init(&attr[0]);
    pthread_create(&tid[0],&attr[0],(void*) thread_func1,NULL);
    //pthread_sigmask

    //CREATE TEAM 2
    pthread_attr_init(&attr[1]);
    pthread_create(&tid[1],&attr[1],(void*) thread_func2,NULL);

    //CREATE TEAM 3
    pthread_attr_init(&attr[2]);
    pthread_create(&tid[2],&attr[2],(void*) thread_func3,NULL);

    //CREATE TEAM 4
    pthread_attr_init(&attr[3]);
    pthread_create(&tid[3],&attr[3],(void*) thread_func4,NULL);


    // send signals to thread
    sleep(1);
    pthread_kill(tid[0],SIGINT);
    pthread_kill(tid[0],SIGINT);
    
    pthread_kill(tid[0],SIGABRT);


    pthread_kill(tid[1],SIGILL);


    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);
    return 0;
}