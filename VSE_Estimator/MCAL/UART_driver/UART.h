/*
 * UART.h
 *
 * Created: 12/19/2019 8:11:22 PM
 *  Author: Zeyad
 */ 


#ifndef UART_H_
#define UART_H_



/*- INCLUDES -----------------------------------------------*/
#include "UART_CONF.h"

typedef struct
{
 uint32_t u32_BaudRate;
 uint8_t u8_DataBits;  /* (5~9) bits */
 uint8_t u8_FlagAction;  /***interrupt or polling***/

}str_UartConfg_t;

typedef uint8_t UART_Error_t;

/*- FUNCTION-LIKE MACROS -----------------------------------*/
#define DISABLE       0U
#define ENABLE        1U

#define UART_ONE_STOP_BIT  0U
#define UART_TWO_STOP_BITS 1U


#define UART_POLLING 0U
#define UART_INTERRUPT 1U



#define UART_FLAG_ACTION 4U
#define UART_ALL_INTERRUPT_DISABLED 5U

#define UART_PARITY_EVEN 0U
#define UART_PARITY_ODD 1U
#define UART_NO_PARITY 2U

#define UART_5_BIT_MODE 0
#define UART_6_BIT_MODE 1
#define UART_7_BIT_MODE 2
#define UART_8_BIT_MODE 3
#define UART_9_BIT_MODE 7




 uint8_t *G_RecData ;
/*- FUNCTION DECLARATIONS ----------------------------------*/
/*************************************************************
*Description: Initialization of Uart Module
* Input     : poiter to uart configuration struct
* Output    : Error Status
* */
extern uint8_t UART_init(str_UartConfg_t * uart_config);

/*************************************************************
*Description: Sending byte of data
* Input     : u16Data to send
* Output    : Error Status
* */
extern uint8_t UART_sendByte(const uint8_t u8_Data);

/*************************************************************
*Description: Receiving byte of data
* Input     : pointer to u16Data
* Output    : Error Status
* */
extern uint8_t UART_recieveByte(uint8_t *u8_Data);


/*************************************************************
*Description: Receiving Flag used in Case of Polling
* Input     : pointer to u8Data
* Output    : No Return
* */
extern void UART_GetPollingFlag(uint8_t *u8_Data);

/*************************************************************
*Description: Call Back for function to send to ISR
* Input     : pointer to function
* Output    : ERROR Status
* */
extern uint8_t UART_TX_SetCallBack(void (*Copy_FunctionAddress)(void));
/*
*Description: Call Back for function to Receive Data
* Input     : pointer to function
* Output    : ERROR Status
* */
extern uint8_t UART_RX_SetCallBack(void (*Copy_FunctionAddress)(void));




#endif /* UART_H_ */
