// Create a child process and find the PID of the current and its parent process

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(void)
{
	char *message;
	pid_t Creating_Process = fork();
	
	switch (Creating_Process)
	{
		case -1:
			printf("Fork Creation Failed\n");
			exit(1);
			
		case 0:
			message = "Child Executing";
			break;
			
		default:
			printf("Parent process waiting for child to finish executing\n");
			wait (NULL);
			printf("Child process has finished executing\n");
			message = "Parent Executing";
			break;
	}
	
	puts(message);
	printf("Current Process ID is %d\n", getpid());
	printf("Parent Process ID is %d\n", getppid());
	
	return 0;
}
