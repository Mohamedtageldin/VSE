/*
 * main.c

 *
 *  Created on: ??þ/??þ/????
 *      Author: mosta
 */

/*________________________________________________________________*/
/******************************************************************/
/*                        INCLUDES                                */
/******************************************************************/
#include "STD_TYPES.h"         /*Standard Types*/

#include "BIT_MATH.h"          /*Bit Operations*/

#include "MCAL_DIO_interface.h"

#include "LCD_interface.h"     /*LCD Driver*/

#include "UART.h"

#include "Register.h"

#include "SPI.h"

str_UartConfg_t ObjUart = {9600 ,UART_8_BIT_MODE , UART_INTERRUPT};
/*________________________________________________________________*/
/******************************************************************/
/*                        MAIN                                    */
/******************************************************************/
int main(void)
{
	uint8_t Local_uint8_Button1;
	uint8_t Local_uint8_Value=0;
	uint8_t Local_uint8_Value2=0;
	uint8_t Local_uint8_Value3[4] = {0};
	uint8_t loop=0,start=0;

	/*__________DRIVERS INIT __________________________________*/

	DIO_u8Init_PIN(DIO_PIN_NO_20,0);

	DIO_u8SetPinInputType(DIO_PIN_NO_20,1);

	Str_SpiCfg_t Str_cfg;
	Str_cfg.Prescaller = (uint8_t)PSC_64;
	Str_cfg.Speed_Mode = (uint8_t)SINGLE_SPEED;
	Str_cfg.Interrupt_Mode=POLLING;
	Str_cfg.Master_Mode=SLAVE;
	Str_cfg.Order=LEASTFIRST;
   SPI_Init(&Str_cfg);



	UART_init(&ObjUart);



	/*___________________________________________________________*/
	while(1)
	{

		SPI_Receivebyte(&Local_uint8_Value);
		//SPI_Sendbyte(2);
		//Local_uint8_Value = SPDR;

//
//		DIO_u8GetPinValue(DIO_PIN_NO_20,&Local_uint8_Button1);
//
//
////		if(Local_uint8_Button1 == DIO_LOW)
////		{
//
			Local_uint8_Value2 = Local_uint8_Value/2;

			while(Local_uint8_Value2 / 10 != 0)
			{
				Local_uint8_Value3[loop] = (Local_uint8_Value2 % 10)+48;
				Local_uint8_Value2 /= 10;
				loop++;
			}
			Local_uint8_Value3[loop] =( Local_uint8_Value2 % 10)+48;

			for(start=loop;start>0;start--)
			{
				UART_sendByte(Local_uint8_Value3[start]);
			}

			UART_sendByte(Local_uint8_Value3[start]);

			loop=0;
//
////			LCD_voidWriteNumber(Local_uint8_Value;
//
////			while(Local_uint8_Button1 == DIO_LOW)
////			{
////				DIO_u8GetPinValue(DIO_PIN_NO_20,&Local_uint8_Button1);
////			}
////		}


	}
}




