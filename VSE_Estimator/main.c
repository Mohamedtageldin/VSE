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

#include "SPI.h"



str_UartConfg_t ObjUart = {9600 ,UART_8_BIT_MODE , UART_INTERRUPT};
/*________________________________________________________________*/
/******************************************************************/
/*                        MAIN                                    */
/******************************************************************/
int main(void)
{
	uint8_t Local_uint8_Value = '\0';
	uint8_t Local_uint8_Value2 = 0;
	uint8_t flag=0;
	uint8_t Local_uint8_Button1;
	uint8_t Local_uint8_Button2;


	/*__________DRIVERS INIT __________________________________*/

	DIO_u8Init_PIN(DIO_PIN_NO_20,0);
	DIO_u8Init_PIN(DIO_PIN_NO_10,0);
	DIO_u8SetPinInputType(DIO_PIN_NO_20,1);
	DIO_u8SetPinInputType(DIO_PIN_NO_10,1);

	DIO_u8Init_PORT(0,255);
	Str_SpiCfg_t Str_cfg;
	Str_cfg.Prescaller = (uint8_t)PSC_64;
	Str_cfg.Speed_Mode = (uint8_t)SINGLE_SPEED;
	Str_cfg.Interrupt_Mode=POLLING;
	Str_cfg.Master_Mode=MASTER;
	Str_cfg.Order=LEASTFIRST;
	SPI_Init(&Str_cfg);



	UART_init(&ObjUart);

	/*___________________________________________________________*/
	while(1)
	{
		//SPI_Sendbyte(2);
		//SPI_Receivebyte(&Local_uint8_Value);
//

//		SPI_Sendbyte(Local_uint8_Value2);
		UART_recieveByte(&Local_uint8_Value);
		if(0 == flag)
		{
			if(Local_uint8_Value =='\n' )
			{
				SPI_Sendbyte(Local_uint8_Value2);
				Local_uint8_Value = '\0';
				flag=1;


			}
			else if(Local_uint8_Value != '\0')
			{
	//			LCD_u8WriteCommand(0b00000001);
				Local_uint8_Value2 = (Local_uint8_Value2 * 10) + (Local_uint8_Value-48);
				Local_uint8_Value = '\0';
			}
		}
		else
		{

			DIO_u8GetPinValue(DIO_PIN_NO_20,&Local_uint8_Button1);
			DIO_u8GetPinValue(DIO_PIN_NO_10,&Local_uint8_Button2);

			if(Local_uint8_Button1 == DIO_LOW)
			{
				Local_uint8_Value2++;
				SPI_Sendbyte(Local_uint8_Value2);

				while(Local_uint8_Button1 == DIO_LOW)
				{
					DIO_u8GetPinValue(DIO_PIN_NO_20,&Local_uint8_Button1);
				}
			}
			else if(Local_uint8_Button2 == DIO_LOW)
			{
				Local_uint8_Value2--;
			SPI_Sendbyte(Local_uint8_Value2);
				while(Local_uint8_Button2 == DIO_LOW)
				{
					DIO_u8GetPinValue(DIO_PIN_NO_10,&Local_uint8_Button2);
				}
			}

		}

	}
}




