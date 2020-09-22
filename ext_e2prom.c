#include "ext_e2prom.h"
#include "i2c.h"
#include "main.h"

#define GET_NINTH_BIT(add) ((add&0x0100)>>8)
#define GET_BYTE_ADDRESS(add) (add&0x00FF)

void ext_e2prom_init(void)
{
    TRISC &= ~0x08;
    i2c_init();
}

unsigned char read_ext_e2prom (unsigned int address)
{
   unsigned char ret;
   unsigned char ninth_bit;
   unsigned char byte_add;

   ninth_bit = GET_NINTH_BIT(address);
   byte_add = GET_BYTE_ADDRESS(address);

   i2c_start();

   if (ninth_bit)
   {
       i2c_wb(0xA2);
   }
   else
   {
      i2c_wb(0xA0);
   }
   i2c_wb(byte_add);

   i2c_start();

    if (ninth_bit)
   {
       i2c_wb(0xA3);
   }
   else
   {
      i2c_wb(0xA1);
   }
   ret = i2c_rb(1);
   i2c_stop();

   return ret;
}


void write_ext_e2prom(unsigned int address, unsigned char data)
{
     unsigned int tmp;
     unsigned char ninth_bit;
     unsigned char byte_add;
     unsigned char i = 0;

     tmp = data;
     ninth_bit = GET_NINTH_BIT(address);
     byte_add = GET_BYTE_ADDRESS(address);

     do
     {
        i2c_start();
        if (ninth_bit)
        {
           i2c_wb(0xA2);
        }
        else
        {
            i2c_wb(0xA0);
        }
        i2c_wb(byte_add);
        i2c_wb(tmp);

        i2c_stop();

        i++;
     } while((tmp != read_ext_e2prom(address))&& (i < 10));
}
