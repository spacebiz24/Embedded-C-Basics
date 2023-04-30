// Clear a bit

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        int value = atoi(argv[1]);
        int ShiftValue = atoi(argv[2]);
        int ref = ~(1 << ShiftValue);
        printf("\nOriginal Value: %d", value);
        printf("\nModified Value: %d", value & ref);
    }
    return 0;
}
