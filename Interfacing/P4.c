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

unsigned int ScanCodeTable[] = {0xEE /*0*/, 0xED /*1*/, 0xEB /*1*/, 0xE7 /*3*/,
                                0xDE /*4*/, 0xDD /*5*/, 0xDB /*6*/, 0xD7 /*7*/,
                                0xBE /*8*/, 0xBD /*9*/, 0xBB /*A*/, 0xB7 /*B*/,
                                0x7E /*C*/, 0x7D /*D*/, 0x7B /*E*/, 0x77 /*F*/};

int GetScancode()
{
    int Column;
    int Row = 0x10;
    while (Row <= 0x80) // 4 shifts
    {
        IO0SET = Row; // Checking that row
        Column = IO0PIN & 0xF;
        if (Column != 0b1111) // found row
            return ScanCode = (Row << 4) + Column;
        IO0CLR = Row; // Turning off that row
        Row <<= 1;    // Switching to next row
    }
    return NULL;
}

int Decode(int ScanCode)
{
    int CodeIndex;
    while (ScanCode != Scancode[CodeIndex])
        CodeIndex++;
    return code;
}

unsigned int SevenSegTable[] = {0x3F /*0*/, 0x06 /*1*/, 0x5B /*2*/, 0x4F /*3*/,
                                0x66 /*4*/, 0x6D /*5*/, 0x7D /*6*/, 0x07 /*7*/,
                                0x7F /*8*/, 0x6F /*9*/, 0x77 /*A*/, 0x7C /*B*/,
                                0x39 /*C*/, 0x5E /*D*/, 0x79 /*E*/, 0x71 /*F*/};

void main()
{
    init_LPC();
    int ScanCode;
    while (1)
    {
        IO0CLR = 0xF0; // Sensitise the keyboard
        while ((IO0PIN & 0xF) != 0b1111); // Wait for a keypress
        IO0CLR = ~0x0; // Clearing the display
        ScanCode = GetScanCode();
        if (ScanCode == NULL)
            continue;
        IO0SET = SevenSegTable[Decode(ScanCode)];
    }
}
