// Create a child process of a child process

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	char *message;
	pid_t Creating_Process = fork();
	switch (Creating_Process)
	{
	case -1:
		printf("Fork Creation Failed!!\n");
		exit(1);
	case 0:
		message = "Child Executing!";
		fork();
		wait(NULL);
		break;
	default:
		printf("Parent Process Waiting for Child to finish executing\n");
		wait(NULL);
		printf("Child Process done Executing!\n");
		message = "Parent Executing!";
		break;
	}
	puts(message);
	printf("Current Process ID is %d\n", getpid());
	printf("Parent Process ID is %d\n", getppid());
	printf("\n");
	return 0;
}
