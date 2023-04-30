// Keypad interfacing to a 7 segment display

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
    int Row = 0b0001;
    while (Row <= 0b1000) // 4 shifts
    {
        IO0CLR = Row << 4; // Checking that row , Row is on P0.4
        Column = IO0PIN & 0xF;
        if (Column != 0b1111) // found row
            return ((Row << 4) + Column);
        IO0SET = Row << 4; // Turning on that row
        Row <<= 1;    // Switching to next row
    }
    return NULL;
}

unsigned int SevenSegTable[] = {0x3F /*0*/, 0x06 /*1*/, 0x5B /*2*/, 0x4F /*3*/,
                                0x66 /*4*/, 0x6D /*5*/, 0x7D /*6*/, 0x07 /*7*/,
                                0x7F /*8*/, 0x6F /*9*/, 0x77 /*A*/, 0x7C /*B*/,
                                0x39 /*C*/, 0x5E /*D*/, 0x79 /*E*/, 0x71 /*F*/};

int Display(int ScanCode)
{
    int CodeIndex;
    while (ScanCode != ScanCodeTable[CodeIndex])
        CodeIndex++;
    IO0SET = SevenSegTable[CodeIndex)] << 8; // Display is on P0.8 onwards
}

void main()
{
    init_LPC();
    int ScanCode;
    while (1)
    {
        IO0CLR = 0xF0; // Sensitise the keyboard
        while ((IO0PIN & 0xF) == 0b1111); // Wait for a keypress
        IO0CLR = 0xF << 8; // Clearing the display
        ScanCode = GetScanCode();
        if (ScanCode == NULL) // Couldn't locate the Key
            continue;
        Display(ScanCode);
    }
}
