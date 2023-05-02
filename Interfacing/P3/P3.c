// Display a message on an LCD

// Currently not working

#include "lpc214x.h"
#include "stdint.h"
#include "string.h"

unsigned int LCDCommand[] = {0x38 /* 5*7 pixels per char & enable 2 rows */,
                             0x0E /* Display on, cursor on */,
                             0x01 /* Clear display */};

void delay_by(unsigned int delayVal)
{
    for (int i = 0; i <= delayVal; i++);
}

void init_LPC()
{
    PINSEL0 = 0x0; // P0.0,..., P0.15 -> GPIO
    IO0DIR = 0xFF;  // P0.0,..., P0.7 -> output (Data)
    PINSEL2 = 0x0; // P1.16,..., P1.31 -> GPIO
    IO1DIR = 0x7 << 16;  // P1.16,..., P1.18 -> output (Control)
}

void LCD_Command(unsigned int Command)
{
    IO0SET = Command; // Load command
    IO1SET = 0b100 << 16;   // E = 1, RS = 0 (Command)
    delay_by(500);
    IO1CLR = 0b100 << 16; // Clearing everything
    IO0CLR = Command;
}

void LCD_Data(int Data)
{
    IO0SET = Data;  // Load data
    IO1SET = 0b101 << 16; // E = 1, RS = 1 (Data)
    delay_by(500);
    IO1CLR = 0b101 << 16; // Clearing everything
    IO0CLR = Data;
}

void LCD_Display(unsigned int Msg[])
{
    for (int character = 0; character < strlen(Msg); character++)
        LCD_Data(Msg[character]);
}

void init_LCD()
{
    for (int CommandIndex = 0; CommandIndex <= 3; CommandIndex++)
        LCD_Command(CommandIndex);
    LCD_Display("LCD Initialised");
    delay_by(10000);
    LCD_Command(0x01); // clear display
}

void main()
{
    init_LPC();
    init_LCD();
    LCD_Display("Hello World");
    while (1);
}
