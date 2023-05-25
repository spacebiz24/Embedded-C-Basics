// Display a message on the LCD

#include "lpc214x.h"
#include "stdint.h"
#include "string.h"

unsigned int InitCommand[] = {0x38 /* 5*7 pixels per char & enable 2 rows */,
                             0x0E /* Display on, cursor on */,
                             0x01 /* Clear display & return cursor to home */};

void delay_by(unsigned int delayVal)
{
    for (int i = 0; i <= delayVal; i++);
}

void init_LPC()
{
    PINSEL0 = 0x0; // P0.0,..., P0.15 -> GPIO
    IO0DIR = 0xFF;  // P0.0,..., P0.7 -> output (Data)
    PINSEL2 = 0x0; // P1.16,..., P1.31 -> GPIO
    IO1DIR = 0b111 << 16;  // P1.16,..., P1.18 -> output (Control)
}

void LCD_command(unsigned int command)
{
    IO0SET = command; // Load command
    IO1SET = 0b100 << 16;   // E = 1, RS = 0 (Command)
    delay_by(500);
    IO1CLR = 0b100 << 16; // Clearing everything
    IO0CLR = command;
}

void LCD_data(int data)
{
    IO0SET = data;  // Load data
    IO1SET = 0b101 << 16; // E = 1, RS = 1 (Data)
    delay_by(500);
    IO1CLR = 0b101 << 16; // Clearing everything
    IO0CLR = data;
}

void LCD_display(char Msg[])
{
    int characterIndex = 0;
    while(Msg[characterIndex] != '\0')
    {
        LCD_data(Msg[characterIndex]);
        characterIndex++;
    }
}

void init_LCD()
{
    for (int commandIndex = 0; commandIndex <= 2; commandIndex++)
        LCD_command(InitCommand[commandIndex]);
    LCD_display("LCD Initialised");
    delay_by(500000);
    LCD_command(0x01); // clear display
}

void main()
{
    init_LPC();
    init_LCD();
    LCD_display("Hello World");
    while (1);
}
