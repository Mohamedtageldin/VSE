/*
 * SPI.h
 *
 * Created: 12/20/2019 1:26:46 PM
 *  Author: Mohamedtageldien
 */


#ifndef SPI_H_
#define SPI_H_

#include "SPI_Retval.h"

#define POLLING 0
#define INTERRUPT 1

#define LEASTFIRST 0
#define MOSTTFIRST 0

#define MASTER 0
#define SLAVE 1

#define SINGLE_SPEED 0
#define DOUBLE_SPEED 1

#define PSC_4 0
#define PSC_16 1
#define PSC_64 2
#define PSC_128 3

#define SS 12
#define MOSI 13
#define MISO 14
#define SCK 15

typedef struct Str_SpiCfg{
	uint8_t Prescaller;
	uint8_t Speed_Mode;
	uint8_t Interrupt_Mode;
	uint8_t Master_Mode;
	uint8_t Order;
}Str_SpiCfg_t;

extern uint8_t Gu8_ISR_Flag;

SPI_Error_t SPI_Init (Str_SpiCfg_t * Pstr_Config);
SPI_Error_t SPI_Sendbyte(const uint8_t Data);
SPI_Error_t SPI_Receivebyte(uint8_t* Data);


#endif /* SPI_H_ */
