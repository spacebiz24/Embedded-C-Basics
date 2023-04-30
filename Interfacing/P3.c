// Display a message on an LCD

#include "lpc214x.h"
#include "stdint.h"
#include "string.h"

unsigned int LCDCommand[] = {0x38 /* 5*7 pixels/char & enable 2 rows */,
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
    IO0DIR = 0xF;  // P0.0,..., P0.7 -> output
    PINSEL2 = 0x0; // P1.16,..., P1.31 -> GPIO
    IO1DIR = 0xF;  // All GPIO -> output
}

void LCD_Command(unsigned int Command)
{
    IO0SET = Command; // Load the command
    IO1SET = 0b100;   // E = 1, RS = 0 (Command)
    delay_by(500);
    IO1CLR = 0b100; // Clearing everything
    IO0CLR = Command;
}

void LCD_Data(unsigned int Data)
{
    if (Data == " ")
        Data = 0x20;
    IO0SET = Data;  // Load the data
    IO1SET = 0b101; // E = 1, RS = 1 (Data)
    delay_by(500);
    IO1CLR = 0b101; // Clearing everything
    IO0CLR = Data;
}

void init_LCD()
{
    for (int CommandIndex = 0; CommandIndex <= 3; CommandIndex++)
        LCD_Command(CommandIndex);
}

void DisplayMsg(char Msg[])
{
    for (int character = 0; character <= strlen(Msg); character++)
        LCD_Data(character);
}

void main()
{
    init_LPC();
    init_LCD();
    while (1)
        DisplayMsg("Hello World");
}
