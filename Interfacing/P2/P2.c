// 4 Digit counter

#include "lpc214x.h"
#include "stdint.h"

#define RightMostDisplay 0b0001
#define LeftMostDisplay 0b1000

unsigned int SevenSegTable[] = {0x3F /*0*/, 0x06 /*1*/, 0x5B /*2*/, 0x4F /*3*/,
                                0x66 /*4*/, 0x6D /*5*/, 0x7D /*6*/, 0x07 /*7*/,
                                0x7F /*8*/, 0x6F /*9*/, 0x77 /*A*/, 0x7C /*B*/,
                                0x39 /*C*/, 0x5E /*D*/, 0x79 /*E*/, 0x71 /*F*/};

void delay_by(unsigned int delayVal)
{
    for (int i = 0; i <= DelayVal; i++);
}

void init_LPC()
{
    PINSEL0 = 0x0; // P0.0,..., P0.15 -> GPIO
    IO0DIR = ~0x0; // P0.0,..., P0.31 -> output (Display data)
    PINSEL2 = 0x0; // P1.16,..., P1.31 -> GPIO
    IO1DIR = ~0x0; // all GPIO -> output (Display selector)
    IO1SET = 0xF << 16; // Disabling all 4 displays 
}

void display(unsigned int counterVal)
{
    int CurrentDisplay = RightMostDisplay; // Initialise to right most display
    while (CurrentDisplay <= LeftMostDisplay)
    {
        int digit = counterVal & 0xF; // Getting right most digit
        IO0SET = SevenSegTable[digit];
        IO1CLR = CurrentDisplay << 16; // enabling
        delay_by(1000);
        IO1SET = CurrentDisplay << 16; // disabling
        IO0CLR = SevenSegTable[digit];
        counterVal >>= 4;    // removing the right most digit
        CurrentDisplay <<= 1;    // Shifting to the next display
    }
}

void main()
{
    init_LPC();
    int count = 0;
    while (1)
    {
        for(int displayDuration = 0; displayDuration <= 50; displayDuration++)
            display(count);
        count++;
    }
}
