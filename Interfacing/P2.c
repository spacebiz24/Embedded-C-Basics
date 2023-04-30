// 4 Digit counter

#include "lpc214x.h"
#include "stdint.h"

void delay_by(unsigned int delayVal)
{
    for (int i = 0; i <= delayVal; i++);
}

void init_LPC()
{
    PINSEL0 = 0x0; // P0.0,..., P0.15 -> GPIO
    IO0DIR = ~0x0; // P0.0,..., P0.31 -> output
    PINSEL2 = 0x0; // P1.16,..., P1.31 -> GPIO
    IO1DIR = ~0x0; // P1.16,..., P1.31 -> output
    IO1SET = ~0x0; // Disabling all displays
}

unsigned int SevenSegTable[] = {0x3F /*0*/, 0x06 /*1*/, 0x5B /*2*/,
                                0x4F /*3*/, 0x66 /*4*/, 0x6D /*5*/,
                                0x7D /*6*/, 0x07 /*7*/, 0x7F /*8*/, 0x6F /*9*/};

void display(unisgned int counterVal)
{
    int displaySel = 0b1;
    while (counterVal != 0)
    {
        int digit = counterVal % 10; // Getting right most digit
        IO0SET = SevenSegTable[digit];
        IO1CLR = displaySel; // enabling that display
        delay_by(100000);
        IO1SET = displaySel; // disabling that display
        IO0CLR = SevenSegTable[digit];
        displaySel <<= 1;    // selecting the next display
        counterVal /= 10;    // removing the right most digit
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
        if(count > 9999)
            count = 0;
    }
}