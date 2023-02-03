// Invert every bit

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        int value = atoi(argv[1]);
        printf("Value: %d\n", value);
        printf("Toggled Value: %d\n", value ^ 0xF);
    }
    return 0;
}
