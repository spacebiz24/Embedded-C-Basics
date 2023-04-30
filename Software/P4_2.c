// Ignoring a specific signal function call
// Change SIGINT to TSTP,STOP (A)

#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int main()
{
	(void)signal(SIGINT,SIG_IGN);
	while(1)
	{
		printf("Process ID: %d\n",getpid());
		sleep(1);
	}
	return 0;
}
