// 4 Digit counter

#include "lpc214x.h"
#include "stdint.h"

unsigned int SevenSegTable[] = {0x3F /*0*/, 0x06 /*1*/, 0x5B /*2*/,
                                0x4F /*3*/, 0x66 /*4*/, 0x6D /*5*/,
                                0x7D /*6*/, 0x07 /*7*/, 0x7F /*8*/, 0x6F /*9*/};

void delay_by(unsigned int delayVal)
{
    for (int i = 0; i <= delayVal; i++);
}

void init_LPC()
{
    PINSEL0 = 0x0; // P0.0,..., P0.15 -> GPIO
    IO0DIR = ~0x0; // P0.0,..., P0.31 -> output
    PINSEL2 = 0x0; // P1.16,..., P1.31 -> GPIO
    IO1DIR = ~0x0; // all GPIO -> output
    IO1SET = ~0x0; // Disabling all displays
}

void display(unisgned int counterVal)
{
    int displaySel = 0b1; // Initialise to right most display
    while (displaySel <= 0b1000)
    {
        int digit = counterVal % 10; // Getting right most digit
        IO0SET = SevenSegTable[digit];
        IO1CLR = displaySel; // enabling that display
        delay_by(100000);
        IO1SET = displaySel; // disabling that display
        IO0CLR = SevenSegTable[digit];
        counterVal /= 10;    // removing the right most digit
        displaySel <<= 1;    // selecting the next display
    }
}

void main()
{
    init_LPC();
    int count = 0;
    while (1)
    {
        display(count);
        count++;
    }
}
