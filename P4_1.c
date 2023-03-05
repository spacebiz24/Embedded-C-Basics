// Manipulation of signal function calls to run a custom function
// Change SIGINT to TSTP, QUIT, ALRM

#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void my_handler(int signal)
{
	printf("Problem encountered, %d was pressed", signal);
}

int main()
{
	(void)signal(SIGINT, my_handler);

	while(1)
	{
		printf("Hello");
		sleep(1);
	}
	return 0;
}
