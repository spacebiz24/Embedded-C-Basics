#include "lpc214x.h"
#include "stdint.h"

void delay_by(unsigned int delayVal)
{
    for (int i = 0; i <= delayVal; i++);
}

void init_LPC()
{
    PINSEL0 = 0x0;  // P0.0,..., P0.15 -> GPIO
    IO0DIR = 0xFF0; // P0.0,..., P0.3 -> input, P0.4,...,P0.15 -> output
}

int leadKey(unsigned int columnVal)
{
    int base = 0;
    int TempColumn = 0x0b1110; // initiating the first column
    while (TempColumn != columnVal)
    {
        TempColumn = (TempColumn << 1) + 1;
        base++;
    }
    return base;
}

int RowVal()
{
    int offset = 0;
    int column;
    while (offset < 4)
    {
        column = IO0PIN & 0xF;
        if (column != 0b1111)
            return offset; // found the row
        offset += 4;
        IO0PIN << = 1;
    }
}

unsigned int SevenSegTable[] = {0x3F /*0*/, 0x06 /*1*/, 0x5B /*2*/,
                                0x4F /*3*/, 0x66 /*4*/, 0x6D /*5*/,
                                0x7D /*6*/, 0x07 /*7*/, 0x7F /*8*/, 0x6F /*9*/};

void main()
{
    init_LPC();
    int column;
    while (1)
    {
        IO0CLR = 0xF0; // sentisising the keyboard
        column = IO0PIN & 0xF;
        if (column != 0b1111)
            IO0SET = SevenSegTable[leadKey(column) + RowVal()];
    }
}
