// Using semaphores to prevent printing

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];

sem_t BinarySemaphore; // semaphore handle

void* input_thread()
{
    while(strncmp("stop", buffer, 4) != 0)
    {
        printf("Enter text: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        sem_post(&BinarySemaphore); // returns the semaphore
        sleep(1);
    }
    pthread_exit("Input thread exited successfully\n");
}

void* convert_thread()
{
    sem_wait(&BinarySemaphore); // takes the semaphore
    while(strncmp("stop", buffer, 4) != 0)
    {
        sleep(1);
        printf("Converted text: ");
        for (int i = 0; i < strlen(buffer); i++)
            printf("%c", toupper(buffer[i]));
        sem_wait(&BinarySemaphore); // prevents multiple prints
    }
    pthread_exit("Convert thread exited successfully\n");
}

void main()
{
    void* ReturnInfo;
    sem_init(&BinarySemaphore, 0, 1);
    pthread_t InputThread, ConvertThread; // thread handles

    printf("Enter some text to convert to uppercase , if 'stop' is typed the program will exit\n");

    pthread_create(&InputThread, NULL, &input_thread, NULL);
    pthread_create(&ConvertThread, NULL, &convert_thread, NULL);

    pthread_join(InputThread, &ReturnInfo);
    printf("%s", (char*) ReturnInfo);
    pthread_join(ConvertThread, &ReturnInfo);
    printf("%s", (char*) ReturnInfo);

    sem_destroy(&BinarySemaphore);
}
