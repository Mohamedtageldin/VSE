/*
 * SPI.c
 *
 * Created: 12/20/2019 1:26:23 PM
 *  Author: Mohamedtageldien
 */ 
/*- INCLUDES ----------------------------------------------*/
//#include <avr/interrupt.h>
#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "MCAL_DIO_interface.h"
#include "Register.h"
#include "SPI.h"
/*- LOCAL MACROS ------------------------------------------*/
#define NOTINITIATED 0
#define INITIATED 1

/*States for Mode Sending/Receiving*/
#define  SENDING 0
#define RECEIVING 1
/*- LOCAL Data types ----------------------------------------*/
/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
/*- GLOBAL STATIC VARIABLES -------------------------------*/
static uint8_t Gu8_Interrupt_Mode; 
static uint8_t Gu8_Init_Flag;
static uint8_t* Gpu8_Data;
static uint8_t Gu8_Mode_Flag;
uint8_t Gu8_ISR_Flag = 1;
/*- GLOBAL EXTERN VARIABLES -------------------------------*/
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

/*- APIs IMPLEMENTATION -----------------------------------*/
/* Description : SPI Initialization                                              */
/* Input       : Str_SPIConfiguration_t* "Pointer to Struct of SPI Configration" */
/* Output      : Error Code		                                                 */
SPI_Error_t SPI_Init (Str_SpiCfg_t * Pstr_Config)
{
	SPI_Error_t U16_Status = SPI_ERROR_INIT_OK;		/*Initialize Error Code*/
	if(NULL_POINTER != Pstr_Config)			/*Check If the pinter passed is Null*/
	{
		/*Checking the Interrupt Mode and assigning it or changing error status*/
		if ((uint8_t)INTERRUPT == Pstr_Config->Interrupt_Mode)  /*Check for Interrupt Mode*/
		{
			Gu8_Interrupt_Mode=INTERRUPT;
			SETBIT(SREG,GLOBAL_INTERRUPT);
			SETBIT(SPCR,SPIE);
			
		}
		else
		{
			if ((uint8_t)POLLING == Pstr_Config->Interrupt_Mode)
			{
				Gu8_Interrupt_Mode=POLLING;
				CLEARBIT(SPCR,SPIE);
			}
			else
			{
				U16_Status = SPI_ERROR_INIT_INTERRUPT;
			}
		}
		/* Check If Error status OK to continue*/
		if (SPI_ERROR_INIT_OK == U16_Status)
		{
			/*Checking the Order if least significant bit first and assigning registers it or changing error status*/
			if((uint8_t)LEASTFIRST == Pstr_Config->Order)
			{
				SETBIT(SPCR,DORD);
			}
			else
			{
				if ((uint8_t)MOSTTFIRST == Pstr_Config->Order)
				{
					CLEARBIT(SPCR,DORD);	
				}
				else
				{
					U16_Status = SPI_ERROR_INIT_Order;
					
				}
			}
			/*Checking for Error status*/
			if ((uint16_t)SPI_ERROR_INIT_OK == U16_Status)
			{
				/*Checking the Master Mode, assigning registers and Initialize GPIO Pins or changing error status*/
				if((uint8_t)MASTER == Pstr_Config->Master_Mode)
				{
					
					DIO_u8Init_PIN(SS,DIO_OUTPUT);
					DIO_u8Init_PIN(MOSI,DIO_OUTPUT);
					DIO_u8Init_PIN(MISO,DIO_INPUT);
					DIO_u8Init_PIN(SCK,DIO_OUTPUT);
					SETBIT(SPCR,MSTR);
					if ((uint8_t)SINGLE_SPEED == Pstr_Config->Speed_Mode)
					{
						CLEARBIT(SPSR,SPI2X);
					}
					else
					{
						/*Checking the Speed Mode entered and assigning it or changing error status*/
						if ((uint8_t)DOUBLE_SPEED == Pstr_Config->Speed_Mode)
						{
							SETBIT(SPSR,SPI2X);
						}
						else
						{
							U16_Status = SPI_ERROR_INIT_SPEED;
						}
					}
					/*Checking the error status and the prescaller and assigning registers or changing error status*/
					if((uint16_t)SPI_ERROR_INIT_OK == U16_Status)
					{
						CLEARBIT(SPCR,SPR0);
						CLEARBIT(SPCR,SPR1);
						switch( Pstr_Config->Prescaller )
						{
							case PSC_4   :  
							CLEARBIT(SPCR,SPR0);
							CLEARBIT(SPCR,SPR1);
							break;
							case PSC_16  :  
							SETBIT(SPCR,SPR0);
							CLEARBIT(SPCR,SPR1);
							break;
							case PSC_64  :  
							CLEARBIT(SPCR,SPR0);
							SETBIT(SPCR,SPR1);
							break;
							case PSC_128 :  
							SETBIT(SPCR,SPR0);
							SETBIT(SPCR,SPR1);
							break;
							default: U16_Status = SPI_ERROR_INIT_PRESCALLER;
							break;
						}
					}
					else
					{
						/*Do Nothing*/
					}
				}
				else
				{
					/*Checking the Slave Mode, assigning registers and Initialize GPIO Pins or changing error status*/
					if((uint8_t)SLAVE == Pstr_Config->Master_Mode)
					{
						DIO_u8Init_PIN(SS,DIO_INPUT);
						DIO_u8Init_PIN(MOSI,DIO_INPUT);
						DIO_u8Init_PIN(MISO,DIO_OUTPUT);
						DIO_u8Init_PIN(SCK,DIO_INPUT);
						CLEARBIT(SPCR,MSTR);
						/*Checking the Speed Mode entered and assigning it or changing error status*/
						if ((uint8_t)SINGLE_SPEED == Pstr_Config->Speed_Mode)
						{
							CLEARBIT(SPSR,SPI2X);
						}
						else
						{
							if ((uint8_t)DOUBLE_SPEED == Pstr_Config->Speed_Mode)
							{
								SETBIT(SPSR,SPI2X);
							}
							else
							{
								U16_Status = SPI_ERROR_INIT_SPEED;
							}
						}
						/*Checking the error status and the prescaller and assigning registers or changing error status*/
						if((uint16_t)SPI_ERROR_INIT_OK == U16_Status)
						{
							CLEARBIT(SPCR,SPR0);
							CLEARBIT(SPCR,SPR1);
							switch( Pstr_Config->Prescaller )
							{
								case PSC_4   :
								CLEARBIT(SPCR,SPR0);
								CLEARBIT(SPCR,SPR1);
								break;
								case PSC_16  :
								SETBIT(SPCR,SPR0);
								CLEARBIT(SPCR,SPR1);
								break;
								case PSC_64  :
								CLEARBIT(SPCR,SPR0);
								SETBIT(SPCR,SPR1);
								break;
								case PSC_128 :
								SETBIT(SPCR,SPR0);
								SETBIT(SPCR,SPR1);
								break;
								default: U16_Status = SPI_ERROR_INIT_PRESCALLER;
								break;
							}
						}
						else
						{
							/*Do Nothing*/
						}
					}
					else
					{
						U16_Status = SPI_ERROR_INIT_MASTERMODE;
					}
				}
			}else
			{
				/*Do Nothing*/
			}
		}
	}
	else
	{
		U16_Status = SPI_ERROR_INIT_NULLPOINTER;
	}
	if ((uint16_t)SPI_ERROR_INIT_OK == U16_Status)
	{
		Gu8_Init_Flag = INITIATED;
		SETBIT(SPCR,SPE); /*Enable SPI*/
	}
	else
	{
		Gu8_Init_Flag = NOTINITIATED;
	}
	return U16_Status;
}

SPI_Error_t SPI_Sendbyte(const uint8_t Data)
{
		SPI_Error_t U16_Status = SPI_ERROR_RECEIVEBYTE_OK;
		if((uint8_t)INITIATED == Gu8_Init_Flag)
		{
			if (POLLING ==Gu8_Interrupt_Mode)
			{
				CLEARBIT(SPCR,SPIE);
				SPDR = Data;
				while (READBIT(SPSR,SPIF) == 0);
				SETBIT(SPSR,SPIF);
				
			}
			else
			{
				/*INTERRUPT*/
				Gu8_Mode_Flag = SENDING;
				Gu8_ISR_Flag = 0;
				//Gu8_Data = Data;
				SPDR = Data;
			}
		}
		else
		{
			U16_Status= SPI_ERROR_SENDBYTE_NOTINIT;
		}
		return U16_Status;
}
SPI_Error_t SPI_Receivebyte(uint8_t* Data)
{
	SPI_Error_t U16_Status = SPI_ERROR_RECEIVEBYTE_OK;
	if((uint8_t)INITIATED == Gu8_Init_Flag)
	{
		if (NULL_POINTER!=Data)
		{
			if ((uint8_t)POLLING ==Gu8_Interrupt_Mode)
			{
				while (READBIT(SPSR,SPIF) == 0);
				*Data = SPDR;
				SETBIT(SPSR,SPIF);
				
			}
			else
			{
				//SETBIT(SREG,GLOBAL_INTERRUPT);
				Gu8_Mode_Flag = RECEIVING;
				//Gpu8_Data = Data;
				*Gpu8_Data = SPDR;
			}
		}
		else
		{
			U16_Status = SPI_ERROR_RECEIVEBYTE_NULLPOINTER;
		}
	}
	else
	{
		U16_Status= SPI_ERROR_RECEIVEBYTE_NOTINIT;
	}
	return U16_Status;
}
/* Interrupt Execution */
void __vector_12(void)
{
	Gu8_ISR_Flag = 1;
	/*if(SENDING== Gu8_Mode_Flag)
	{
	}
	else
	{
		if (Gpu8_Data!=NULL_POINTER)
		{
			
			//CLEARBIT(SPCR,SPIE);
		}
		else
		{
			DIO_u8Init_PIN(24,DIO_OUTPUT);
			DIO_u8SetPinValue(24,DIO_HIGH);
		}
	}*/
	
}
