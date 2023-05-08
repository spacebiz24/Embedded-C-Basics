// Keypad interfacing to a 7 segment display

// Currently not working

#include "lpc214x.h"
#include "stdint.h"

#define TopRow 0b0001
#define BottomRow 0b1000

unsigned int ScanCodeTable[] = {0xEE /*0*/, 0xED /*1*/, 0xEB /*2*/, 0xE7 /*3*/,
                                0xDE /*4*/, 0xDD /*5*/, 0xDB /*6*/, 0xD7 /*7*/,
                                0xBE /*8*/, 0xBD /*9*/, 0xBB /*A*/, 0xB7 /*B*/,
                                0x7E /*C*/, 0x7D /*D*/, 0x7B /*E*/, 0x77 /*F*/};

unsigned int SevenSegTable[] = {0x3F /*0*/, 0x06 /*1*/, 0x5B /*2*/, 0x4F /*3*/,
                                0x66 /*4*/, 0x6D /*5*/, 0x7D /*6*/, 0x07 /*7*/,
                                0x7F /*8*/, 0x6F /*9*/, 0x77 /*A*/, 0x7C /*B*/,
                                0x39 /*C*/, 0x5E /*D*/, 0x79 /*E*/, 0x71 /*F*/};

void delay_by(unsigned int delayVal)
{
    for (int i = 0; i <= delayVal; i++);
}

void init_LPC()
{
    PINSEL0 = 0x0;  // P0.0,..., P0.15 -> GPIO
    IO0DIR = 0xFF0; // P0.0,..., P0.3 -> input (Column), P0.4,..., P0.15 -> output(Row + Display)
}

int GetScancode()
{
    IO0SET = 0xF << 4; // Insensitise all the rows
    int CurrentRow = TopRow;
    while (CurrentRow <= BottomRow)
    {
        IO0CLR = CurrentRow << 4; // Checking that row , Row is from P0.4 onwards
        delay_by(2);
        if ((IO0PIN & 0xF) != 0b1111) // found row
            return IO0PIN & 0xFF;
        IO0SET = CurrentRow << 4; // Turning on that row
        CurrentRow <<= 1;  // Going to the next row
    }
    return 1;
}

void Display(int ScanCode)
{
    int CodeIndex = 0;
    while (ScanCodeTable[CodeIndex] != ScanCode)
        CodeIndex++;
    IO0SET = SevenSegTable[CodeIndex] << 8; // Display is from P0.8 onwards
}

void main()
{
    init_LPC();
    int ScanCode;
    while (1)
    {
        IO0CLR = 0xF << 4; // Sensitise the keyboard, Rows are from P0.4 onwards
        while ((IO0PIN & 0xF) == 0b1111); // Wait for a keypress
        IO0CLR = 0xFF << 8; // Clearing the display, Display is from P0.8 onwards
        ScanCode = GetScanCode();
        if (ScanCode == 1) // Couldn't locate the Key
            continue;
        Display(ScanCode);
    }
}
