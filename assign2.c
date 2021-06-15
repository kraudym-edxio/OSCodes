#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

/*
	COMP-3300: Assignment 2
	Written by: Edxio Kraudy Mora (110006224)
	Date: Thursday June 15, 2021
 */

int main() {

	pid_t pid;		//Keep track of process ID
	char message[1024];	//Store input message

	//Declaring integer arrays to be used for pipe creation
	int fd1[2];
	int fd2[2];

	//Creating two pipes
	pipe(fd1);
	pipe(fd2);

	if ((pid == fork()) == 0) { //Child

		close(fd1[0]);	//Child does not need to read from first pipe
		close(fd2[1]);	//Child does not need to write to second pipe

		//Prompt for input, scan message including newline character
		printf("Enter an input message: ");
		scanf("%[^\n]", message);
	
		//Child must write message to first pipe
		write(fd1[1], message, strlen(message) + 1);
		printf("Child has written the message to the pipe.\n");

		sleep(1);

		//Child must read from the second pipe once message has been written to fd2[1]
		read(fd2[0], message, sizeof(message));
		printf("Child has received reversed-case message from parent: %s\n", message);

		exit(0);

	}

	else {	//Parent
	
		close(fd1[1]);	//Parent does not need to write to first pipe
		close(fd2[0]);	//Parent does not need to read from second pipe 

		//Parent must read message that child wrote to fd1[1]
		read(fd1[0], message, sizeof(message));
		printf("Parent has recevied the child's message: %s\n", message);

		//Converting lowercase to uppercase, vice versa
		for (int x = 0; message[x] != '\n'; x++) {

			if (message[x] >= 'a' && message[x] <= 'z') {
				message[x] -= 32;
			}

			else if (message[x] >= 'A' && message[x] <= 'Z') {
				message[x] += 32;
			}

		}

		printf("Parent has reversed the case of each character: %s\n", message);
		
		//Parent must write reversed-case message to the second pipe
		write(fd2[1], message, strlen(message) + 1);
		
		wait(NULL); //Block parent until children have finished
	
	}

	return 0;

}
