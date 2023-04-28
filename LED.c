#include "lpc214x.h"
#include "stdint.h"

void delay_by(unsigned int delayVal)
{
    for (int i = 0; i <= delayVal; i++);
}

void init_LPC()
{
    PINSEL0 = 0x0;   // P0.0,..., P0.15 -> GPIO
    IO0DIR = ~(0x0); // All GPIO -> outputs
}

void main()
{
    init_LPC();
    int LEDIndex = 0;
    while (1)
    {
        if (!LEDIndex) 
            LEDIndex = 0x80;
        IO0SET = LEDIndex;
        delay_by(20000);
        IO0CLR = LEDIndex; // Turning off that LED
        LEDIndex >>= 1;
    }
}
