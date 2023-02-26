// Call fork() three times and check the number of processes running

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    fork();
    fork();
    fork();
    printf("Fork testing Code\n");
    printf("Current Process ID: %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());
    printf("\n");
    return 0;
}
