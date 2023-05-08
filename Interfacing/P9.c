#include <lpc214x.h>
#include <stdint.h>

#define EN (1 << 6)
#define STA (1 << 5)
#define STO (1 << 4)
#define SI (1 << 3)
#define AA (1 << 2)


void init_LPC()
{
    PINSEL0 = 0b0101 << 4; // P0.2 -> SCL0, P0.3 -> SDA0
    I2C0SCLH = 50;
    I2C0SCLL = 50;
    I2C0CONCLR = EN | STA | STO | SI | AA; // Clear all flags
    I2C0CONSET = EN;                       // Enable I2C communication interface
}

void start(int SlaveAddress)
{
    I2C0CONSET = STA; // Start transmission
    while ((I2C0CONSET & SI) == 0); // Wait for state to change
    I2C0CONCLR = SI;

    I2C0DAT = SlaveAddress; // Send the slave address on the line
    while ((I2C0CONSET & AA) == 0); // Wait for slave to acknowledge
    I2C0CONCLR = STA | AA; // Clear start condition
}

void write(int Data)
{
    I2C0DAT = Data;
    while ((I2C0CONSET & AA) == 0); // Wait for slave to acknowledge
    I2C0CONCLR = AA;
}

unsigned int read()
{
    I2C0CONSET = AA; 
    while ((I2C0CONSET & SI) == 0); // Wait for data
    I2C0CLR = SI;
    return I2C0DAT; 
}

void stop()
{
    I2C0CONSET = STO; // Stop transmission
    while (I2C0CONSET & STO); // Wait for Stop bit to be cleared
}

void main()
{
    init_LPC();
    
    start(0x50);
    write(0x75);
    stop();

    start(0x50);
    int data = read();
    stop();
}
