#include "lpc214x.h"
#include "stdint.h"

void Delay(unsigned int delay)
{
    for (int i = 0; i <= delay; i++);
}

void init_LPC()
{
    PINSEL0 = 0x00L;      // P0.0,..., P0.15 -> GPIO
    IO0DIR = 0xFFFFFFFFL; // All GPIO -> outputs
}

void main()
{
    init_LPC();
    int index = 0; // give a better name
    while (1)
    {
        if (!index)
            index = 0x80;
        IO0SET = index;
        Delay(20000);
        IO0CLR = 0xFFFFFFFF; // does 0xFL work? Long 'F'
        index >>= 1;
    }
}
