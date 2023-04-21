#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

#define BUFF_SIZE 1024

char buff[BUFF_SIZE];

void *read_thread()
{
    while (strncmp("stop", buff, 4) != 0)
    {
        printf("Enter text: ");
        fgets(buff, BUFF_SIZE, stdin);
        sleep(1);
    }
    pthread_exit("Read thread successful");
}

void *convert_thread()
{
    int i;
    while (strncmp("Stop", buff, 4) != 0)
    {
        sleep(1);
        printf("Converted Text: ");
        for (i = 0; i < strlen(buff); i++)
            printf("%c", toupper(buff[i]));
    }
    pthread_exit("Convert Thread Successful");
}

int main()
{
    int result;
    pthread_t rthread, cthread;
    void *thread_result;
    printf("Enter text: ");
    pthread_create(&rthread, NULL, read_thread, NULL);
    pthread_create(&cthread, NULL, convert_thread, NULL);
    pthread_join(rthread, &thread_result);
    printf("Read thread joined, %s\n", (char *)thread_result);
    pthread_join(cthread, &thread_result);
    printf("Convert thread joined, %s\n", (char *)thread_result);
    return 0;
}
