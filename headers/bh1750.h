#ifndef BH1750_H
#define BH1750_H

#include "twi_interrupts.h"

#define BH1750_ADDR_L 0x23
#define BH1750_ADDR_H 0x5C
#define BH1750_DEF_MTREG 0x45

#define BH1750_POWER_DOWN 0x00
#define BH1750_POWER_ON 0x01
#define BH1750_RESET 0x07
#define BH1750_CONTINUOUSLY_H_RES_MODE 0x10
#define BH1750_CONTINUOUSLY_H_RES_MODE2 0x11
#define BH1750_CONTINUOUSLY_L_RES_MODE 0x13
#define BH1750_ONE_TIME_H_RES_MODE 0x20
#define BH1750_ONE_TIME_H_RES_MODE2 0x21
#define BH1750_ONE_TIME_L_RES_MODE 0x23

//3 MSB bits are taken
#define BH1750_CHANGE_MTREG_H(x) (0x40 | (x & 0xD0))

//5 LSB bits are taken
#define BH1750_CHANGE_MTREG_L(x) (0x60 | (x & 0x1F))

uint8_t bh1750_send_command(uint8_t opecode);

uint8_t bh1750_change_mtreg(uint8_t new_mtreg);

uint8_t bh1750_read_data(uint8_t * l_byte_dest, uint8_t * h_byte_dest);

#endif