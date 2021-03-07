#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]){
	//printf("%d\n",argc);
	//check arguements
	if(argc <3){
		perror("Not enough input args");
		exit(1);
	}


	//check if input files exits aand are readable
	for(int i=1; i< (argc>=3 ? argc-1:argc) ; i++){
		printf("%s\n",argv[i]);
		//open the file
		if (access(argv[i], R_OK)){
			perror("Reading error");
			exit(1);
		}
	}

	char *outputFile = argc>3 ? argv[argc-1]:"myfile.out";
	printf("%s\n",outputFile);

	// copy files one at time into new file

	// int fd[2];
	// char buf[24];
	// int n=0;
	// while((n=read(STDIN_FILENO, buf, sizeof(buf))) != 0) {
    // 	write(STDOUT_FILENO, buf, n);
  	// }
	
	printf("hi");
	printf("hi");
	return 0;
}


// void WriteInFile (int fd, const char *buff, int len){
	
// }

// void CopyFile (int fd, const char *file_in){
	
// }
