#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>


void oneProcess(int numbers[], int L, int H){
    int found = 0;
    for(int i = 0; i < L; i++){
        if(numbers[i]== -10){
            printf("Hi I am process %d and I found a hidden key at A[%d]\n",getpid(),i);
            found++;
        }
        if(found ==H)
            break;
        
    }
}

int searchBlock(int numbers[], int start, int end, int L , int H, int* foundKeys){
    int foundCount = 0;

	size_t i;

	for (i = start; i < L && i < end; i++)
	{
		// Key check.
		if (numbers[i] == -10)
		{
			foundKeys[foundCount++] = i;
			printf("I am process %d and I found the key at %d\n", getpid(), foundKeys[foundCount - 1]);
		}
		// All found check.
		if (foundCount == H){
			break;
		}
	}
	// Return number of keys found.
	return foundCount;
}

void versionTwo(int numbers[],int L, int H){
    
    int numFound = 0,searchResult,j =0;
    int splitSize = L/H;
    
    int *foundIndexes = (int*)malloc(H*sizeof(int));
    int *keyIndexes = (int*)malloc(H*sizeof(int));
    pid_t p, root,start,end;
    int pipefd[2];
    if((pipe(pipefd)) == -1){
        printf("Pipe creation failure");
        exit(EXIT_FAILURE);
    }

    root = getpid();

    for(int i =0; i < H;i++){
        start = splitSize*i;
        end = (i+1) * splitSize;
        if((p = fork()) < 0){
            printf("Fork failed\n");
            exit(1);
        }
        //child
        else if(p == 0){
            printf("I am process %d, my parent is %d\n", getpid(), getppid());
            if(i == H){
                
				// Next send number of found indexes 
				write(pipefd[1], &numFound, sizeof(int));
				// Now, pipe each found index (should be none).
				for (j = 0; j < numFound; j++){
					write(pipefd[1], &(keyIndexes[j]), sizeof(int));
				}
            }
        }
        //parent
        else if(p > 0){
			// Just search, then break.
			searchResult = searchBlock(numbers,start,end,L,H,keyIndexes);

			for (j = 0; j < searchResult; j++)
			{
				foundIndexes[j] = keyIndexes[j];
				numFound++;
			}


			waitpid(p, NULL, 0);
			int readFoundCount, readFoundIndex;

			// Next read number of found indexes.
			read(pipefd[0], &readFoundCount, sizeof(int));

			for (j = 0; j < readFoundCount; j++)
			{
				read(pipefd[0], &readFoundIndex, sizeof(int));
				foundIndexes[numFound++] = readFoundIndex;

			}

	

			
			if (!(getpid() == root))
			{
				write(pipefd[1], &numFound, sizeof(int));
				// Now, pipe each found index.
				for (j = 0; j < numFound; j++)
				{
					write(pipefd[1], &(foundIndexes[j]), sizeof(int));		
				}
			}
            break;

        }
    }
    free(foundIndexes);
	free(keyIndexes);
    exit(EXIT_SUCCESS);
}


int main(int argc, char **argv){
    //argv[1] = L
    //argv[2] = H
    //argv[3] = filename
    //argv[4] = mode 
    if(argc != 5){
        exit(EXIT_FAILURE);
    }

    int L = atoi(argv[1]),H = atoi(argv[2]),mode = atoi(argv[4]);
    //populate array
    int numbers[L];
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0, num, max = -10, total=0;
    fp = fopen(argv[3], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        num = atoi(line);
        numbers[i]= num;
        total +=num;
        max = num > max ? num: max;
        i++;
    }
    printf("Max = %d, Average = %f\n", max, (total*1.0/L));
    close(fp);
    //test system crash
    int processes = 1;
    while(1){
        processes++;
        printf("%d\n",processes);
        if(fork()){
            waitpid(getpid(),NULL,0);
        }
        
    }
    if(mode == 1)
        oneProcess(numbers,L,H);
    if(mode == 2)
        versionTwo(numbers,L,H);
    return 0;
    
}





