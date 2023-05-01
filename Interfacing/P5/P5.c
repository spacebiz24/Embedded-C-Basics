// Signal generator using DAC

#include "lpc214x.h"
#include "stdint.h"

void delay_by(unsigned int delayVal)
{
    for (int i = 0; i <= delayVal; i++);
}

void init_LPC()
{
    PINSEL0 = 0x0; // P0.0,..., P0.15 -> GPIO
    IO0DIR = 0x0; // All GPIO -> input (Wave selection)
    PINSEL1 = 0x80000; // P0.25 -> DAC output mode
}

unsigned int SineTable[] = {0, 6, 25, 55, 97, 151, 211, 216, 282, 359, 436, 512,
                            591, 665, 742, 808, 873, 926, 968, 998, 1017, 1023};
int sampleIndex;

void SineGen()
{
    for (sampleIndex = 0; sampleIndex <= 22; sampleIndex++)
    {
        DACR = SineTable[sampleIndex] << 6;
        delay_by(100);
    }
    for (sampleIndex = 22; sampleIndex >= 0; sampleIndex--)
    {
        DACR = SineTable[sampleIndex] << 6;
        delay_by(100);
    }
}

int sampleVal;

void TraingleGen()
{
    for (sampleVal = 0; sampleVal <= 1023; sampleVal++)
        DACR = sampleVal << 6;
    for (sampleVal = 0; sampleVal >= 1023; sampleVal--)
        DACR = sampleVal << 6;
}

void SawtoothGen()
{
    for (sampleVal = 0; sampleVal <= 1023; sampleVal++)
        DACR = sampleVal << 6;
}

void SquareGen()
{
    sampleVal = 0;
    DACR = sampleVal << 6;
    delay_by(200);
    sampleVal = 1023;
    DACR = sampleVal << 6;
    delay_by(200);
}

void main()
{
    init_LPC();
    int WaveSel;
    while (1)
    {
        WaveSel = IO0PIN & 0b11; // Obtaining values at P0.0 & 1
        if (WaveSel == 0)
            SineGen();
        else if (WaveSel == 1)
            TraingleGen();
        else if (WaveSel == 2)
            SawtoothGen();
        else
            SquareGen();
    }
}
