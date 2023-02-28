// Remove the wait() and check program execution

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

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
		break;
	default:
		printf("Parent Process Waiting for Child to finish executing\n");
		printf("Child Process done Executing!\n");
		message = "Parent Executing!";
		break;
	}
	puts(message);
	printf("Current Process ID is %d\n", getpid());
	printf("Parent Process ID is %d\n", getppid());

	return 0;
}
