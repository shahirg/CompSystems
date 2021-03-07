#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){
    int max;
    double average;
    char *strLines = malloc(sizeof(argv[1]));
    strLines = argv[1];
    int lines = atoi(strLines);
    //free(strLines);

    printf("%d\n",lines);
    return 0;
}