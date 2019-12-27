/*
 * Register.h
 *
 * Created: 12/20/2019 2:18:57 PM
 *  Author: Mohamedtageldien
 */ 


#ifndef REGISTER_H_
#define REGISTER_H_


#define SPCR *(volatile  uint8_t *)0x2D
#define SPSR *(volatile  uint8_t *)0x2E
#define SPDR *(volatile  uint8_t *)0x2F
#define SREG *(volatile  uint8_t *)0x5F

#define SPIE 7
#define SPE 6
#define DORD 5
#define MSTR 4
#define CPOL 3
#define CPHA 2
#define SPR1 1
#define SPR0 0

#define SPIF 7
#define WCOL 6
#define SPI2X 0

#define GLOBAL_INTERRUPT 7

#endif /* REGISTER_H_ */
