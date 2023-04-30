// Set the 5th bit in a value

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        int value = atoi(argv[1]);
        value |= 1 << 5;
        printf("Value: %d\n", value);
    }
    return 0;
}
