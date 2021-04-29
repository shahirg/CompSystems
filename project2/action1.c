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
    sigset_t set[4];

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

    // BLOCKS ALL SIGNALS WHICH NOT ASSIGNED TO IT
    sigemptyset(&set[0]);
    sigaddset(&set[0],SIGCHLD);
    sigaddset(&set[0],SIGSEGV);
    sigaddset(&set[0],SIGFPE);
    sigaddset(&set[0],SIGHUP);
    sigaddset(&set[0],SIGTSTP);
    pthread_sigmask(SIG_BLOCK, &set[0],NULL);
    pthread_attr_init(&attr[0]);
    pthread_create(&tid[0],&attr[0],(void*) thread_func1,NULL);


    //CREATE TEAM 2

    // BLOCKS ALL SIGNALS WHICH NOT ASSIGNED TO IT
    sigemptyset(&set[1]);
    sigaddset(&set[1],SIGINT);
    sigaddset(&set[1],SIGSEGV);
    sigaddset(&set[1],SIGFPE);
    sigaddset(&set[1],SIGHUP);
    sigaddset(&set[1],SIGTSTP);
    pthread_sigmask(SIG_BLOCK, &set[0],NULL);
    pthread_attr_init(&attr[1]);
    pthread_create(&tid[1],&attr[1],(void*) thread_func2,NULL);

    //CREATE TEAM 3

    // BLOCKS ALL SIGNALS WHICH NOT ASSIGNED TO IT
    sigemptyset(&set[2]);
    sigaddset(&set[2],SIGINT);
    sigaddset(&set[2],SIGABRT);
    sigaddset(&set[2],SIGILL);
    sigaddset(&set[2],SIGCHLD);
    sigaddset(&set[2],SIGTSTP);
    pthread_sigmask(SIG_BLOCK, &set[2],NULL);
    pthread_attr_init(&attr[2]);
    pthread_create(&tid[2],&attr[2],(void*) thread_func3,NULL);

    //CREATE TEAM 4

    // BLOCKS ALL SIGNALS WHICH NOT ASSIGNED TO IT
    sigemptyset(&set[3]);
    sigaddset(&set[3],SIGINT);
    sigaddset(&set[3],SIGABRT);
    sigaddset(&set[3],SIGILL);
    sigaddset(&set[3],SIGCHLD);
    sigaddset(&set[3],SIGSEGV);
    pthread_sigmask(SIG_BLOCK, &set[3],NULL);

    pthread_attr_init(&attr[3]);
    pthread_create(&tid[3],&attr[3],(void*) thread_func4,NULL);


    // send signals to thread
    sleep(1);
    pthread_kill(tid[0],SIGINT);
    pthread_kill(tid[0],SIGTSTP);
    
    pthread_kill(tid[0],SIGABRT);


    pthread_kill(tid[1],SIGILL);

    // CLOSE THREADS
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);
    return 0;
}