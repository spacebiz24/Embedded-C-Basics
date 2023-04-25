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

unsigned int mvright[8] = {0x80808080, 0x40404040, 0x20202020, 0x10101010, 0x08080808, 0x04040404, 0x02020202, 0x01010101};

void main()
{
    init_LPC();
    int index = 0;
    while (1)
    {
        if (index > 7)
            index = 0;
        IO0SET = mvright[index++];
        Delay(20000);
        IO0CLR = 0xFFFFFFFF; // does 0xFL work? Long 'F'
    }
}
