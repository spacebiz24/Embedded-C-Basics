// Display a message on an LCD
// Check LCD-16x2-8bit.h definition

#include "lpc214x.h"
#include "stdint.h"
#include "string.h"

unsigned int LCDCommand[] = {0x38 /* 5*7 pixels per char & enable 2 rows */,
                             0x0E /* Display on, cursor on */,
                             0x01 /* Clear display */,
                             0x06 /* Automatically increment cursor (after data entry) */};

void delay_by(unsigned int delayVal)
{
    for (int i = 0; i <= delayVal; i++);
}

void init_LPC()
{
    PINSEL0 = 0x0; // P0.0,..., P0.15 -> GPIO
    IO0DIR = 0xFF;  // P0.0,..., P0.7 -> output
    PINSEL2 = 0x0; // P1.16,..., P1.31 -> GPIO
    IO1DIR = 0xF;  // P1.16,..., P1.23 -> output
}

void LCD_Command(unsigned int Command)
{
    IO0SET = Command; // Load command
    IO1SET = 0b100;   // E = 1, RS = 0 (Command)
    delay_by(500);
    IO1CLR = 0b100; // Clearing everything
    IO0CLR = Command;
}

void LCD_Data(unsigned int Data)
{
    if (Data == " ")
        Data = 0x20;
    IO0SET = Data;  // Load data
    IO1SET = 0b101; // E = 1, RS = 1 (Data)
    delay_by(500);
    IO1CLR = 0b101; // Clearing everything
    IO0CLR = Data;
}

void LCD_Display(char Msg[])
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
    while (1)
        LCD_Display("Hello World");
}
