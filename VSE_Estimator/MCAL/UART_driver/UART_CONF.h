/*
 * UART_CONF.h
 *
 * Created: 12/20/2019 1:35:01 AM
 *  Author: Zeyad
 */ 

#ifndef UART_CONF_H_
#define UART_CONF_H_
#include "UART.h"
/*****************freq.****************/
#define UART_FCPU 8000000UL

/***********interrupts******************/
#define UART_TX_INTTERTUPT   DISABLE    /*ENABLE OR DISABLE**/
#define UART_RX_INTTERTUPT  DISABLE  /*ENABLE OR DISABLE**/
#define UART_UDRE_INTTERTUPT DISABLE  /*ENABLE OR DISABLE**/

#define UART_SYNCHRONOUS DISABLE
#define UART_ASYNCHRONOUS ENABLE

#define UART_PARITY_CHOICE UART_NO_PARITY

#define UART_STOP_BITS  UART_ONE_STOP_BIT  /* 0/1 */


/********************parity*********************/

#endif /* UART CONF_H_ */
