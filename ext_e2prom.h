#ifndef __EXT_E2PROM_H__
#define __EXT_E2PROM_H__

void ext_e2prom_init(void);
unsigned char read_ext_e2prom (unsigned int address);
void write_ext_e2prom(unsigned int address, unsigned char data);


#endif // __EXT_E2PROM_H__
