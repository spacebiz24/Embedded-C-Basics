// Stepper motor

#include "lpc214x.h"
#include "stdint.h"

void delay_by(unsigned int delayVal)
{
    for (int i = 0; i <= delayVal; i++);
}

void init_LPC()
{
    PINSEL0 = 0x0; // P0.0,..., P0.15 -> GPIO
    IO0DIR = 0xF;  // P0.0,..., P0.3 -> output (Coil magnetiser)
    IO0CLR = 0xF;  // P0.0,..., P0.3 -> 0
}

void ClockwiseRotation(int ActiveCoil)
{
    while (ActiveCoil <= 0b1000)
    {
        IO0SET = ActiveCoil;
        delay_by(10000);
        IO0CLR = ActiveCoil;
        ActiveCoil <<= 1;
    }
}

void AntiClockwiseRotation(int ActiveCoil)
{
    while (ActiveCoil >= 0b0001)
    {
        IO0SET = ActiveCoil;
        delay_by(10000);
        IO0CLR = ActiveCoil;
        ActiveCoil >>= 1;
    }
}

void main()
{
    init_LPC();
    int TotalRotations = 550;
    int ActiveCoil = 0b001;
    while (1)
    {
        for (int Rotation = 0; Rotation <= TotalRotations; Rotation++)
            ClockwiseRotation(ActiveCoil);
        for (int Rotation = 0; Rotation <= TotalRotations; Rotation++)
            AntiClockwiseRotation(ActiveCoil);
    }
}
