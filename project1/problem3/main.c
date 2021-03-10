#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

/* Auxiliary function; Structure to define the process tree */
struct processInfo
{
	char processName;
	int numChild;
	char children[5];
	int retValue;
};

/* Process tree */
struct processInfo process[] = 
{
	{ 'A', 2, {'B', 'C'}, 2},
	{ 'B', 1, {'D'}, 4 },
	{ 'C', 0, { }, 6 },
	{ 'D', 0, { }, 10 },
};

char myId = 'A'; /* Process id */
int retVal;
void processfunction()
{
	int i, j;
	int n = sizeof(process) / sizeof(struct processInfo);
	printf("Started Process %c, pid=%d\n", myId, getpid());
	
	/* Get the children details */
	for(i = 0; i < n; i++)
	{
    	if(myId == process[i].processName) /* Process details found */
        	break;
	}
	
	if(i < n) /* Entry found */
	{
    	retVal = process[i].retValue; /* Update return value */
    	pid_t pid[5]; /* Create forked children */
    	
    	for(j = 0; j < process[i].numChild; j++)
    	{
        	pid[j] = fork();
        	if(pid[j] < 0)
        	{
            	printf("Process %c, pid=%d: Fork failed\n", myId, getpid());
        	}
        	
        	if(pid[j] == 0)
        	{
            	/* Child process */
            	myId = process[i].children[j]; /* 1. Update id */
            	processfunction(); /* 2. Call the processfunction, and return */
            	return;
        	}
        	
        	else
        	{
            	printf("Process %c, pid=%d: Forked %c, pid=%d\n", myId, getpid(), process[i].children[j], pid[j]);
        	}
    	}
    	
    	/* Children forked, wait for children to end */
    	printf("Process %c, pid=%d: Waiting for children termination\n", myId, getpid());
    	for(j = 0; j < process[i].numChild; j++)
    	{
        	int status;
        	if(pid[j] > 0) /* Child was successfully forked */
        	{
            	waitpid(pid[j], &status, 0);
            	printf("Process %c, pid=%d: Child allowing its own terminating with status %d\n", myId, getpid(), WEXITSTATUS(status));
        	}
    	}
	}
	
	/* Sleep for sometime */
	sleep(10);
	printf("Process %c, pid=%d: Ending process\n", myId, getpid());
}

int main()
{
	processfunction();
	exit(retVal);
}

