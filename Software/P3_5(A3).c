// Parent waiting for a specific child process to complete

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int Process_ID, status;
char *message;

void checkProcess(pid_t Process)
{
	switch(Process)
	{
		case -1:
			printf("Fork Creation Failed!!\n");
			break;
		case 0:
			message = "Child Executing!";
			break;
		default:
			printf("Parent Process Waiting for Child to finish executing\n");
			waitpid(Process_ID, &status, 0);
			printf("Child Process done Executing!\n");
			message = "Parent Executing!";
			break;
	}
}

int main()
{
	pid_t Fork_1 = fork();
	checkProcess(Fork_1);
	Process_ID = getpid();
	fork();
	printf("Fork testing Code\n");
	printf("Current Process ID: %d\n", getpid());
	printf("Parent Process ID: %d\n", getppid());
	printf("\n");
	return 0;
}
