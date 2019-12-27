/*- INCLUDES ----------------------------------------------*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART.h"
#include "AVR_UART_REG.h"
#include "UART_Retval.h"
/*- LOCAL MACROS ------------------------------------------*/
#define UART_BAUD_CHECK 300

#define UART_UBRR_CALCULATE_CONST 16U

#define SHIFT_8_BITS 8U

/*- LOCAL Dataypes ----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
static UART_Error_t UART_CheckSync(void);
static UART_Error_t UART_CheckParity(void);
static UART_Error_t UART_CheckStopBit(void);


void __vector_13(void)__attribute((signal,used));
void __vector_14(void)__attribute((signal,used));
void __vector_15(void)__attribute((signal,used));

/*- GLOBAL STATIC VARIABLES -------------------------------*/
static uint8_t G_UartMode= 0;

static uint8_t G_sendData = 0 ;

static void (*UART_TX_CallBack)(void)=0;
static void (*UART_RX_CallBack)(void)=0;
/*************************************************************
*Description: Initialization of Uart Module
* Input     : poiter to uart configuration struct
* Output    : Error Status
* */
UART_Error_t UART_init(str_UartConfg_t * Uart_Config)
{
	UART_Error_t Local_u8_ErrorStatus = UART_ERROR_OK;  /*Check Error*/
	uint16_t Local_UBRR_Value ;  /*Baud Rate Cal*/

	if(Uart_Config ->u32_BaudRate % UART_BAUD_CHECK ==0)  /*Check if Entered BaudRate is Correct*/
	{
		if(Uart_Config ->u8_DataBits >=  UART_5_BIT_MODE && Uart_Config->u8_DataBits <= UART_9_BIT_MODE)  /*Check Entered Bit Numbers*/
		{
			if(Uart_Config ->u8_DataBits == UART_5_BIT_MODE)
			{
				CLR_BIT(UCSRC,UCSRC_UCSZ0);  /*In Case 5 Bits*/
				CLR_BIT(UCSRC,UCSRC_UCSZ1);
				CLR_BIT(UCSRB,UCSRB_UCSZ2);
			}
			else if(Uart_Config ->u8_DataBits == UART_6_BIT_MODE)
			{
				SET_BIT(UCSRC,UCSRC_UCSZ0);   /*In Case 6 Bits*/
				CLR_BIT(UCSRC,UCSRC_UCSZ1);
				CLR_BIT(UCSRB,UCSRB_UCSZ2);
			}
			else if(Uart_Config ->u8_DataBits == UART_7_BIT_MODE)
			{
				CLR_BIT(UCSRC,UCSRC_UCSZ0);   /*In Case 7 Bits*/
				SET_BIT(UCSRC,UCSRC_UCSZ1);
				CLR_BIT(UCSRB,UCSRB_UCSZ2);
			}
			else if(Uart_Config ->u8_DataBits == UART_8_BIT_MODE)
			{
				SET_BIT(UCSRC,UCSRC_UCSZ0);     /*In Case 8 Bits*/
				SET_BIT(UCSRC,UCSRC_UCSZ1);
				CLR_BIT(UCSRB,UCSRB_UCSZ2);
			}
			else
			{
				SET_BIT(UCSRC,UCSRC_UCSZ0);    /*In Case 9 Bits*/
				SET_BIT(UCSRC,UCSRC_UCSZ1);
				SET_BIT(UCSRB,UCSRB_UCSZ2);
			}

			if(Uart_Config ->u8_FlagAction == UART_POLLING || Uart_Config -> u8_FlagAction == UART_INTERRUPT)
			{
				Local_u8_ErrorStatus =  UART_CheckSync();   /*Check if it is Sync or Async*/

				G_UartMode = Uart_Config ->u8_FlagAction;
				if(UART_ERROR_OK==Local_u8_ErrorStatus)
				{
					Local_u8_ErrorStatus = UART_CheckParity();  /*Check Parity Type */
					if(UART_ERROR_OK==Local_u8_ErrorStatus)
					{
						Local_u8_ErrorStatus = UART_CheckStopBit();

						if(UART_ERROR_OK == Local_u8_ErrorStatus)
						{
							if(Uart_Config->u8_FlagAction == UART_INTERRUPT)  /*Check INTERRUPT or polling */
							{
								SET_BIT(UCSRC,UCSRC_URSEL);
								Local_UBRR_Value = (uint16_t) ((UART_FCPU/(UART_UBRR_CALCULATE_CONST * (Uart_Config ->u32_BaudRate))) - 1U);
								SET_BIT(UCSRB,UCSRB_TXEN);  /*Enable Transmit*/
								SET_BIT(UCSRB,UCSRB_RXEN);  /*Enable Receive */

								UBBRRH = (uint8_t) (Local_UBRR_Value >> SHIFT_8_BITS);  /*But UBBRRH for Suitable Baud Rate*/

								UBBRRL = (uint8_t)  Local_UBRR_Value;
								SET_BIT(SREG,7);   /*Enable Global INTERRUPT */

							}
							else
							{
								/*Polling*/
								SET_BIT(UCSRC,UCSRC_URSEL);
								Local_UBRR_Value = (uint16_t) ((UART_FCPU/(UART_UBRR_CALCULATE_CONST * (Uart_Config ->u32_BaudRate))) - 1U);
								SET_BIT(UCSRB,UCSRB_TXEN); /*Enable Transmit*/
								SET_BIT(UCSRB,UCSRB_RXEN); /*Enable Receive */

								UBBRRH = (uint8_t) (Local_UBRR_Value >> SHIFT_8_BITS);

								UBBRRL = (uint8_t)  Local_UBRR_Value;

							}
						}
						else
						{
							/*Do Nothing */
						}
					}
					else
					{
						/*Do Nothing*/
					}
				}
				else
				{
					/*Do Nothing*/
				}
			}
			else
			{
				Local_u8_ErrorStatus = UART_FLAG_ACTION;  /*If Not Interrupt or Polling */
			}
		}
		else
		{
			Local_u8_ErrorStatus = UART_ERROR_DATA_NUMBER;  /*If wrong Number of bits entered */
		}
	}
	else
	{
		Local_u8_ErrorStatus = UART_ERROR_BAUD_RATE;   /*If wrong Baud Rate is entered */
	}
	return Local_u8_ErrorStatus;
}

static UART_Error_t UART_CheckSync(void)
{
	UART_Error_t Local_u8_ErrorStatus = UART_ERROR_OK;    /*Check Configuration File if entered State is Sync or Async or other */
	#if(UART_ASYNCHRONOUS == ENABLE)
		CLR_BIT(UCSRC,UCSRC_UMSEL);
	#elif(UART_SYNCHRONOUS == ENABLE)
		SET_BIT(UCSRC,UCSRC_UMSEL);
	#else
		Local_u8_ErrorStatus = UART_ERROR_SYNCHRONIZATION;
	#endif

	return Local_u8_ErrorStatus;
}

static UART_Error_t UART_CheckParity(void)
{
	UART_Error_t Local_u8_ErrorStatus = UART_ERROR_OK;   /*Check Configuration File if parity is even or odd or other*/
	#if(UART_PARITY_CHOICE == UART_PARITY_EVEN)
		SET_BIT(UCSRC,UCSRC_UPM1);
		CLR_BIT(UCSRC,UCSRC_UPM0);
	#elif(UART_PARITY_CHOICE == UART_PARITY_ODD)
		SET_BIT(UCSRC,UCSRC_UPM1);
		CLR_BIT(UCSRC,UCSRC_UPM0);
	#elif(UART_PARITY_CHOICE == UART_NO_PARITY)
		CLR_BIT(UCSRC,UCSRC_UPM1);
		CLR_BIT(UCSRC,UCSRC_UPM0);
	#else
		Local_u8_ErrorStatus = UART_ERROR_PARITY;
	#endif
		return Local_u8_ErrorStatus;
}

static UART_Error_t UART_CheckStopBit(void)  /*Check Configuration File if stop bit is one  or two or other*/
{
	UART_Error_t Local_u8_ErrorStatus = UART_ERROR_OK;
	#if(STOP_BITS == UART_ONE_STOP_BIT)
		CLR_BIT(UCSRC,UCSRC_USBS);
	#elif(STOP_BITS == UART_TWO_STOP_BITS)
		SET_BIT(UCSRC,UCSRC_USBS);
	#else
		Local_u8_ErrorStatus = UART_ERROR_STOPBIT;
	#endif
		return Local_u8_ErrorStatus;
}


/*************************************************************
*Description: Sending byte of data
* Input     : u16Data to send
* Output    : Error Status
* */
UART_Error_t UART_sendByte(const uint8_t u8_Data)
{
	UART_Error_t Local_u8_ErrorStatus = UART_ERROR_OK;
	uint8_t Local_u8_ValueUDRE;

	if(G_UartMode == UART_POLLING)   /*In Case of Polling*/
	{

		Local_u8_ValueUDRE = GET_BIT(UCSRA,UCSRA_UDRE) ;

		if(Local_u8_ValueUDRE == 1)
		{
			UDR = u8_Data;
		}
	}
	else
	{
		if(G_sendData == 0)
		{

			if((GET_BIT(UCSRA,UCSRA_DOR)) == 0)  /*check Detect over Run */
			{
				G_sendData = u8_Data;

				SET_BIT(UCSRB,UCSRB_UDRIE);
			}
			else
			{
				/*Nothing*/
			}
		}
		else
		{
			/*Nothing*/
		}
	}

		return Local_u8_ErrorStatus;
}


/*************************************************************
*Description: Receiving byte of data
* Input     : pointer to u16Data
* Output    : Error Status
* */
UART_Error_t UART_recieveByte(uint8_t *u8_Data)
{
	UART_Error_t Local_u8_ErrorStatus = UART_ERROR_OK;

	if(G_UartMode == UART_POLLING)
	{
		if((GET_BIT(UCSRA,7)) ==1)  /*In Case Of polling*/
		{
			*u8_Data=UDR;
		}
	}
	else
	{
		 G_RecData = u8_Data;
		SET_BIT(UCSRB,UCSRB_RXCIE); /*Enable Interrupt*/

	}

	return Local_u8_ErrorStatus;

}

/*************************************************************
*Description: Receiving Flag used in Case of Polling
* Input     : pointer to u8Data
* Output    : No Return
* */
void UART_GetPollingFlag(uint8_t *u8_Data)
{
	uint8_t Local_u8_ValueTX;

	Local_u8_ValueTX = GET_BIT(UCSRA,UCSRA_TXC); /*Get Value of Transmit Flag*/
	if(Local_u8_ValueTX == 1)
	{
		SET_BIT(UCSRA,6);
		*u8_Data = 1;  /*Add One to return */
	}
	else
	{
		*u8_Data  = 0;  /*Add Zero To Return */
	}
}

uint8_t UART_TX_SetCallBack(void (*Copy_FunctionAddress)(void))
{
	uint8_t Local_u8ErrorState=1;              //Error State: No Error

	if(Copy_FunctionAddress==NULL_POINTER) //check if pointer points to Nothing
	{
		Local_u8ErrorState=0;             //Error State : Error
	}
	else
	{
       	UART_TX_CallBack =Copy_FunctionAddress;//Send Function Address To Call Back pointer
	}

	return Local_u8ErrorState; //Return Error State
}

uint8_t UART_RX_SetCallBack(void (*Copy_FunctionAddress)(void))
{
	uint8_t Local_u8ErrorState=1;              //Error State: No Error

	if(Copy_FunctionAddress==NULL_POINTER) //check if pointer points to Nothing
	{
		Local_u8ErrorState=0;             //Error State : Error
	}
	else
	{
       	UART_RX_CallBack =Copy_FunctionAddress;//Send Function Address To Call Back pointer
	}

	return Local_u8ErrorState; //Return Error State
}

void __vector_14(void)
{
	if((GET_BIT(UCSRA,UCSRA_UDRE))==1  && (GET_BIT(UCSRA,UCSRA_DOR))==0 ) /*Check if UDR is Empty and overRun Error*/
	{
		UDR = G_sendData;   /*Move Data to UDR*/

		G_sendData = 0;
		SET_BIT(UCSRB,UCSRB_TXCIE);
	}

	CLR_BIT(UCSRB,UCSRB_UDRIE); /*Disable Interrupt*/
}

void __vector_13(void)
{

	if((GET_BIT(UCSRA,UCSRA_UDRE))==1)  /*Check if UDR is Empty*/
	{
		*G_RecData = UDR;   /*Getting Value in UDR*/

		if(UART_RX_CallBack!=0)
		{
			 	UART_RX_CallBack();
		}

	}

	CLR_BIT(UCSRB,UCSRB_RXCIE); /*Disable Interrupt*/

}

void __vector_15(void)
{
	if(UART_TX_CallBack!=0)
	{
 		UART_TX_CallBack();
 	}

 CLR_BIT(UCSRB,UCSRB_TXCIE);
}

