#include <lpc214x.h>
#include <stdint.h>

void init_LPC()
{
    PINSEL0 = 0b0101; // P0.0 -> UART_Tx, P0.1 -> UART_Rx
    U0LCR = 0x83;     // Enable DLAB (DLAB = 1)
    U0DLL = 0x61;     // Set baud rate (for 8-bit data)
    U0DLM = 0x00;
    U0LCR = 0x03;
}

void write(int Data)
{
    while ((U0LSR & 0x20) == 0); // Wait for UART to be ready
    U0THR = Data;
}

unsigned int read()
{
    while ((U0LSR & 0x1) == 0); // Wait for data
    return U0RBR;
}

void main()
{
    init_LPC();

    write(0x75);

    int data = read();
}
