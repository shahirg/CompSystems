#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]){
	//printf("%d\n",argc);
	//check arguements
	if(argc <3){
		perror("Not enough input args");
		exit(1);
	}
	int numInputs = argc>3 ? argc-1:argc;
	//printf("numinputs = %d\n",numInputs);

	//get output file name
	const char *outputFile = argc>3 ? argv[argc-1]:"myfile.out";

	//set up file descriptors
	int fd[numInputs];

	//All input fd set to read only
	for(int i =0; i < numInputs-1; i++){
		fd[i] = open(argv[i+1], O_RDONLY);
		if(fd[i] == -1){
			printf("Failed to open %s\n", argv[i+1]);
			exit(1);//
		}
	}

	//output fd set to write only
	fd[numInputs-1] = open(outputFile, O_WRONLY | O_CREAT | O_APPEND, 0666);

	//create buffer and copy files into the buffer
	char buf[128];
	
	int nread;
	for(int i=0; i < numInputs-1; i++){
		nread = 0;
		while((nread = read(fd[i], buf, sizeof(buf)) != 0)){
			//printf("read: '%s'\n", buf);
			write(fd[numInputs-1], buf, sizeof(char)*(strlen(buf)));
		}
		close(fd[i]);
	}
	return 0;
}



