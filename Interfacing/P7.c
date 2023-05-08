// ADC

#include <lpc214x.h>
#include <stdint.h>
#include "LCD-16x2-8bit.h"
#include <stdio.h>
#include <string.h>

void init_LPC()
{
    PINSEL1 = 0x1000000; // P0.28 -> ADC input mode
    AD0CR = 0x200402;    // ADC opertational
}

float Analog2Digital()
{
    AD0CR |= 1 << 24; // Begin conversion command
    while ((AD0DR1 & 0x80000000) == 0); // wait till conversion done
    int result = AD0DR1 >> 6;
    result &= 0x3FF; // taking relavent data
    return ((result / 1023.0) * 3.3);
}

void Display(int voltage)
{
    char volt[18];
    LCD_Command(0x80);
    sprintf(volt, "Voltage =%.2f", voltage);
    LCD_String(volt);
    memset(volt, 0, 18);
}

void main()
{
    init_LPC();
    LCD_init();
    while (1)
        Display(Analog2Digital());
}
