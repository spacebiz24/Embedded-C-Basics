// Blinking LEDs

#include "lpc214x.h"
#include "stdint.h"

void delay_by(unsigned int delayVal)
{
    for (int i = 0; i <= delayVal; i++);
}

void init_LPC()
{
    PINSEL0 = 0x0; // P0.0,..., P0.15 -> GPIO
    IO0DIR = 0xFF; // P0.0,..., P0.7 -> output (LED selector)
}

void main()
{
    init_LPC();
    int LEDIndex;
    while (1)
    {
        LEDIndex = 0x80;
        while(LEDIndex > 0)
        {
            IO0SET = LEDIndex;
            delay_by(10000);
            IO0CLR = LEDIndex; // Turning off that LED
            LEDIndex >>= 1;
        }
    }
}
