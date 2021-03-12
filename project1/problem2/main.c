#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

void oneProcess(int numlines, int numKeys, char* fileName){
    
    // char buf[128];
    // printf("%s",&fileName);
    // int fd;
    // fd = open(&fileName, O_RDONLY);
    // if(fd == -1){
    //     printf("Failed to open %s\n", fileName);
    //     exit(1);//
    // }
    // read(fd, buf, sizeof(buf));
    // //for(int i = 0)

    // printf("%s\n",buf);
    int num, keysFound=0,linesread = 0, max = -10,total = 0;
    double avg;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(fileName, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        linesread++;
        num = atoi(line);
        total += num;
        max = num > max ? num:max;
        if(num == -10){
            keysFound++;
            printf("HI I am process %d and I found a hidden key in position A[%d]\n",getppid(),linesread);
        }
        if(keysFound >=numKeys)
            break;
        //printf("%s", line);
    }
    avg = total/linesread;
    fclose(fp);
    if (line)
        free(line);
    printf("Max= %d Avg= %f\n",max,avg);
    exit(EXIT_SUCCESS);


}
void vesrionTwo(int numbers[],int L, int H){

}


int main(int argc, char **argv){
    //argv[1] = L
    //argv[2] = H
    //argv[3] = filename
    //argv[4] = mode 
    if(argc != 5){
        return(EXIT_FAILURE);
    }

    int L = atoi(argv[1]);
    int H = atoi(argv[2]);
    int mode = atoi(argv[4]);
    //populate array
    int numbers[L];
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0,num;
    fp = fopen(argv[3], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        num = atoi(line);
        printf("num = %d\n",num);
        numbers[i]= num;
        printf("num = %d\n",num);
        i++;
    }
    close(fp);
    for(i=0; i<L; i++){
        printf("%d\n",numbers[i]);
    }
    //oneProcess(lines,argv[2],numKeys);
    return 0;
    //
}

