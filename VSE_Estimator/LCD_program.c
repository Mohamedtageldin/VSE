/*
 * LCD_program.c


 *
 *  Created on: ??þ/??þ/????
 *      Author: mosta
 */
/*________________________________________________________________
 * INCLUDES
 * _______________________________________________________________
 * */
#include "STD_TYPES.h"
#include "MCAL_DIO_config.h"
#include "MCAL_DIO_interface.h"
#include <util/delay.h>
#include "LCD_interface.h"
//*****************************************************************


/*_________________________________________________________________
 * LCD FUNCTIONS IMPLEMENTATION :-
 * ________________________________________________________________
 * */



/*______________________________________________________________________________________
 * Description:Write Command to LCD
 * Input     : Copy_u8Command(Command to LCD)
 * Output    : NA
 * _____________________________________________________________________________________
 * */
void LCD_u8WriteCommand(uint8_t Copy_u8Command)
{
	DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);    /*E=0    Stop Enable*/

	DIO_u8SetPinValue(LCD_RS_PIN,DIO_LOW);   /*RS=0  0 for Command and 1 for DATA*/

	DIO_u8SetPinValue(LCD_RW_PIN,DIO_LOW);   /*RW=0  0 for Write and 1 for Read*/

	DIO_u8SetPortValue(LCD_DATA_PORT,Copy_u8Command);      /*Command*/

	DIO_u8SetPinValue(LCD_E_PIN,DIO_HIGH);   /*E=1 Sequence Start Enable*/

	_delay_ms(2);                                          /*Delay for 2 ms*/

	DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);    /*E=0   Stop Enable*/

}
//********************************************************************************************


/*_________________________________________________________________________________________
 * Description:Send Data to LCD
 * Input     :Copy_u8Data (Data to send)
 * Output    : NA
 * _________________________________________________________________________________________
 * */
void LCD_u8WriteData(uint8_t Copy_u8Data)
{
	DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);     /*E=0    Stop Enable*/

	DIO_u8SetPinValue(LCD_RS_PIN,DIO_HIGH);   /*RS=1  0 for Command and 1 for DATA*/

	DIO_u8SetPinValue(LCD_RW_PIN,DIO_LOW);    /*RW=0  0 for Write and 1 for Read*/

	DIO_u8SetPortValue(LCD_DATA_PORT,Copy_u8Data);          /*DATA*/

	DIO_u8SetPinValue(LCD_E_PIN,DIO_HIGH);    /*E=1 Sequence Start Enable*/

	_delay_ms(2);                                           /*Delay for 2 ms*/

	DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);     /*E=0   Stop Enable*/
}
//******************************************************************************************


/*_________________________________________________________________________________________
 * Description:Initialization of LCD
 * Input     :NA
 * Output    : NA
 *_________________________________________________________________________________________
 * */
void LCD_voidInit(void)
{

	/*______________PIN Initialization_____________________________*/
	DIO_u8Init_PIN(LCD_RS_PIN,DIO_OUTPUT);
	DIO_u8Init_PIN(LCD_RW_PIN,DIO_OUTPUT);
	DIO_u8Init_PIN(LCD_E_PIN,DIO_OUTPUT);

	DIO_u8Init_PORT(LCD_DATA_PORT,255);
/*______________________________________________________________________________________________________________________*/

	_delay_ms(30);                  /*Delay 30 ms*/

	LCD_u8WriteCommand(0b00111000); /*0b0011NF00 Function Set Command N(number of lines 0 1line 1 2lines) F(Font Size 0 5x8 and 1 5x11) 0 0 (2 bits don't care)*/

	_delay_ms(1);                   /*Delay 1 ms*/

	LCD_u8WriteCommand(0b00001100); /*0b00001DCB D(display on/off) C (cursor on/off) B (cursor Blink 0 no blink 1 blink )*/

	_delay_ms(1);                   /*Delay 1 ms*/

	LCD_u8WriteCommand(0b00000001); /*LCD clr*/

	_delay_ms(2);                   /*Delay 2 ms*/


}
//******************************************************************************************



/*___________________________________________________________________________________________
 * Description:Write String on LCD
 * Input     :*Copy_u8String (Pointer to the String),Copy_SizeArray(Size of String Array)
 * Output    : NA
 *___________________________________________________________________________________________
 * */
void LCD_u8WriteString(uint8_t *Copy_u8String)
{
	uint8_t Local_LoopCtr=0;   /*Variable for Loop from 0 to Size of String*/

/*	for(Local_LoopCtr=0;Local_LoopCtr<Copy_SizeArray;Local_LoopCtr++)
	{
		LCD_u8WriteData(Copy_u8String[Local_LoopCtr]); //Write Data For each Single Char to form String
	}*/

	while(Copy_u8String[Local_LoopCtr] != NULL)
	{
		LCD_u8WriteData(Copy_u8String[Local_LoopCtr]);
		Local_LoopCtr++;
	}
}
//*******************************************************************************************


/*___________________________________________________________________________________________
 * Description:GO To Column No. and Row No.
 * Input     :Copy_u8PosY(Column No.), Copy_u8PosX(Row No.)
 * Output    : NA
 *___________________________________________________________________________________________
 * */
void LCD_voidGoToXY(uint8_t Copy_u8PosY,uint8_t Copy_u8PosX)
{
	uint8_t Local_u8Adress;     /*variable to go to address of wanted ROW and Column*/

	if(Copy_u8PosY==0)     /*if Column No =1*/
	{
		Local_u8Adress= 128 + Copy_u8PosX; /*Command starts with 10000000 and add to it address*/
	}
	else if(Copy_u8PosY==1)   /*if Column No=2*/
	{
		Local_u8Adress=128+  0x40  +Copy_u8PosX; /*Command Starts with 10000000 and add 0x40 and add address*/
	}
/*or
 * if(Copy_u8PosY<2 && Copy_u8PosX<16)
 * adress=128+Copy_u8PosX+Copy_u8PosY*0x40
 */
	LCD_u8WriteCommand(Local_u8Adress);  /*Write Command*/
}
//*******************************************************************************************


/*___________________________________________________________________________________________
 * Description:Enable LCD
 * Input     :NA
 * Output    : NA
 *___________________________________________________________________________________________
 * */
void LCD_voidEnable(void)
{
	LCD_u8WriteCommand(0b00001100); /*0b00001DCB D(display on/off) C (cursor on/off) B (cursor Blink 0 no blink 1 blink )*/
}
//*******************************************************************************************


/*___________________________________________________________________________________________
 * Description:Disable LCD
 * Input     :NA
 * Output    : NA
 *___________________________________________________________________________________________
 * */
void LCD_voidDisable(void)
{
	LCD_u8WriteCommand(0b00001000); /*0b00001DCB D(display on/off) C (cursor on/off) B (cursor Blink 0 no blink 1 blink )*/
}
//*******************************************************************************************

/*___________________________________________________________________________________________
 * Description:Disable LCD Cursor
 * Input     :NA
 * Output    : NA
 *___________________________________________________________________________________________
 **/
void LCD_voidCursorDisable(void)
{
	LCD_u8WriteCommand(0b00001100); /*0b00001DCB D(display on/off) C (cursor on/off) B (cursor Blink 0 no blink 1 blink )*/
}
//*******************************************************************************************

/*___________________________________________________________________________________________
 * Description:Enable LCD Cursor
 * Input     :NA
 * Output    : NA
 *___________________________________________________________________________________________
 **/
void LCD_voidCursorEnable(void)
{
	LCD_u8WriteCommand(0b00001110); /*0b00001DCB D(display on/off) C (cursor on/off) B (cursor Blink 0 no blink 1 blink )*/
}
//*******************************************************************************************


/*___________________________________________________________________________________________
 * Description:Enable LCD Cursor Blink
 * Input     :NA
 * Output    : NA
 *___________________________________________________________________________________________
 * */
void LCD_voidCursorBlinkEnable(void)
{
	LCD_u8WriteCommand(0b00001111); /*0b00001DCB D(display on/off) C (cursor on/off) B (cursor Blink 0 no blink 1 blink )*/
}
//*******************************************************************************************


/*___________________________________________________________________________________________
 * Description:Enable LCD Cursor Blink
 * Input     :NA
 * Output    : NA
 *___________________________________________________________________________________________
 * */
void LCD_voidCursorBlinkDisable(void)
{
	LCD_u8WriteCommand(0b00001110); /*0b00001DCB D(display on/off) C (cursor on/off) B (cursor Blink 0 no blink 1 blink )*/
}
//*******************************************************************************************

/*___________________________________________________________________________________________
 * Description:Draw Special Shape CGRAM Char Generator
 * Input     :Copy_u8NumberofData(Number of Special Characters), *Copy_u8Ptr(Pointer to send array of shape written in binary),Copy_u8PosY(column No.),Copy_u8PosX(Row No.)
 * Output    : NA
 *___________________________________________________________________________________________
 * */
void LCD_voidWriteSpecialChar(uint8_t Copy_u8NumberofData,uint8_t *Copy_u8Ptr,uint8_t Copy_u8PosY,uint8_t Copy_u8PosX)
{
	LCD_u8WriteCommand(0b01000000);      /*Move AC from DDRAM to CGRAM*/
	uint8_t Local_u8Loop=0;

	for(Local_u8Loop=0;Local_u8Loop<Copy_u8NumberofData*8;Local_u8Loop++) /*Loop from 0 to No of Special Characters *8(bit for each Character)*/
		{
			LCD_u8WriteData(Copy_u8Ptr[Local_u8Loop]); /*Write Data to CGRAM*/
		}
	LCD_voidGoToXY(Copy_u8PosY,Copy_u8PosX); /*Move AC back from CGRAM to DDRAM*/

}
//*******************************************************************************************


/*___________________________________________________________________________________________
 * Description:Write Integer on LCD
 * Input     :Copy_u8IntValue (Integer Value)
 * Output    : NA
 *___________________________________________________________________________________________
 * */
void LCD_voidWriteNumber(uint32_t Copy_u16IntValue)
{
	uint8_t Local_u8CharArr[10];            /*MAX No. of Integer Digits*/
	uint8_t Local_u8Count=1;               /*Variable to Count Digits*/
	uint8_t Local_u8Count2;
	uint8_t Local_u8Loop=0;
/*	itoa(Copy_u16IntValue , Local_u8CharArr , 10); Convert from Integer to String*/
	uint16_t Local_u16IntValue; /*Copy of integer Value as the original Value is not effected*/
	Local_u16IntValue=Copy_u16IntValue;
	while(Local_u16IntValue/10 != 0) /*while there is reminder*/
		{
			Local_u8Count++; /*increase No. of Digits by 1*/
			Local_u16IntValue =	Local_u16IntValue/10; /*Divide it by 10 to decrease Number by digit that is already counted*/
		}
	Local_u16IntValue=Copy_u16IntValue;
	 Local_u8Count2=Local_u8Count;
	while(Local_u8Count!=0)
	{
		Local_u8CharArr[Local_u8Count-1]=Local_u16IntValue%10;
		Local_u16IntValue /=10;
		Local_u8Count--;
	}
	for(Local_u8Loop=0;Local_u8Loop<Local_u8Count2;Local_u8Loop++)
	{
		LCD_u8WriteData(Local_u8CharArr[Local_u8Loop]+48);
	}

/*	LCD_u8WriteString(Local_u8CharArr,Local_u8Count); //Use it as a normal String*/
}
/********************************************************************************************/
