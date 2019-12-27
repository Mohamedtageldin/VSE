/*
 * LCD_interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: mosta
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
/*_________________________________________________________________
 *
 * LCD DRIVER INTERFACE FILE
 *
 * ________________________________________________________________
 ******************************************************************/


/*__________________________________________________________________
 * LCD Defines :-
 * _________________________________________________________________
 */
#define LCD_DATA_PORT   DIO_PORT_2   /*LCD DATA PORT D0->D7 PORTA*/
#define LCD_RS_PIN     DIO_PIN_NO_26    /*RS(Register Select)(Command or Data) Connected to PIN 0 PORTD*/
#define LCD_RW_PIN      DIO_PIN_NO_27      /*RW(Read/Write) Connected to PIN 1 PORTD*/
#define LCD_E_PIN       DIO_PIN_NO_28      /*Enable Connected to PIN 2 PORTD*/
//*****************************************************************



/*Description:Write Command to LCD
 * Input     : Copy_u8Command(Command to LCD)
 * Output    : NA
 * */
void LCD_u8WriteCommand(uint8_t Copy_u8Command);



/*Description:Send Data to LCD
 * Input     :Copy_u8Data (Data to send)
 * Output    : NA
 * */
void LCD_u8WriteData(uint8_t Copy_u8Data);


/*Description:Initialization of LCD
 * Input     :NA
 * Output    : NA
 * */
void LCD_voidInit(void);


/*Description:Write String on LCD
 * Input     :*Copy_u8String (Pointer to the String),Copy_SizeArray(Size of String Array)
 * Output    : NA
 * */
void LCD_u8WriteString(uint8_t *Copy_u8String);


/*Description:GO To Column No. and Row No.
 * Input     :Copy_u8PosY(Column No.), Copy_u8PosX(Row No.)
 * Output    : NA
 * */
void LCD_voidGoToXY(uint8_t Copy_u8PosY,uint8_t Copy_u8PosX);



/*Description:Draw Special Shape CGRAM Char Generator
 * Input     :Copy_u8NumberofData(Number of Special Characters), *Copy_u8Ptr(Pointer to send array of shape written in binary),Copy_u8PosY(column No.),Copy_u8PosX(Row No.)
 * Output    : NA
 * */
void LCD_voidWriteSpecialChar(uint8_t Copy_u8NumberofData,uint8_t *Copy_u8Ptr,uint8_t Copy_u8PosY,uint8_t Copy_u8PosX);


/*Description:Write Integer on LCD
 * Input     :Copy_u8IntValue (Integer Value)
 * Output    : NA
 * */
void LCD_voidWriteNumber(uint32_t Copy_u8IntValue);


/*Description:Enable LCD
 * Input     :NA
 * Output    : NA
 * */
void LCD_voidEnable(void);


/*Description:Disable LCD
 * Input     :NA
 * Output    : NA
 * */
void LCD_voidDisable(void);

/*Description:Enable LCD Cursor
 * Input     :NA
 * Output    : NA
 * */
void LCD_voidCursorEnable(void);

/*Description:Enable LCD Cursor
 * Input     :NA
 * Output    : NA
 * */
void LCD_voidCursorDisable(void);

/*Description:Enable LCD Cursor Blink
 * Input     :NA
 * Output    : NA
 * */
void LCD_voidCursorBlinkEnable(void);

/*Description:Enable LCD Cursor Blink
 * Input     :NA
 * Output    : NA
 * */
void LCD_voidCursorBlinkDisable(void);


#endif /* LCD_INTERFACE_H_ */
