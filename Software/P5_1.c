// Creation of 2 threads for reading from Stdin and to convert to uppercase

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<pthread.h>

#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];

void* input_thread()
{
    while(strncmp("stop", buffer, 4) != 0)
    {
        fgets(buffer, BUFFER_SIZE, stdin);
        sleep(1);
    }
    pthread_exit("Input thread exited successfully\n");
}

void* convert_thread()
{
    while(strncmp("stop", buffer, 4) != 0)
    {
        sleep(1);
        printf("Converted text: ");
        for (int i = 0; i < strlen(buffer); i++)
            printf("%c", toupper(buffer[i]));
    }   
    pthread_exit("Convert thread exited successfully\n");
}

void main()
{
    void* ReturnInfo;
    pthread_t InputThread, ConvertThread; // thread handles

    printf("Enter some text to convert to uppercase , if 'stop' is typed the program will exit\n");

    pthread_create(&InputThread, NULL, &input_thread, NULL);
    pthread_create(&ConvertThread, NULL, &convert_thread, NULL);

    pthread_join(InputThread, &ReturnInfo);
    printf("%s", (char*) ReturnInfo);
    pthread_join(ConvertThread, &ReturnInfo);
    printf("%s", (char*) ReturnInfo);
}
