#include "lpc214x.h"
#include "stdint.h"

unsigned int delay_ms. led_val;
unsigned char index;
unsigned int mvright[] = {0x80808080, 0x40404040, 0x20202020, 0x10101010, 0x08080808, 0x04040404, 0x02020202, 0x01010101, 0x00};

void initLPC(void)
{
  PINSEL0 = 0x00L;
  IO0DIR = 0xFFFFFFFF;
}

void delay(unsigned int dms)
{
  delay_ms = dms;
  while(delay_ms > 0)
    delay_ms--;
}

void main(void)
{
  index  = 0;
  initLPC();
  while(1)
  {
    index &= 0x7;
    led_val = mvright[index++];
    IO0SET = led_val;
    delay(20000);
    IO0CLR = 0xFFFFFFFF;
  }
}
