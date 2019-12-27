/**************************************************************************
 * Author:   : Mostafa Nasser
 * File Name : MCAL_DIO_interface.h
 * Component : DIO Driver
 * Version   : 1
 ****************************************************************************/
/*_______________________________________________________________________

Define DIO Registers for ATMEGA32
________________________________________________________________________
*/
#ifndef MCAL_DIO_INTERFACE_H_
#define MCAL_DIO_INTERFACE_H_


#include"AVR_MCAL_DIO_REG.h"

#include"MCAL_DIO_config.h"


/*____________________________________________________________________

  PORT NUMBERS (4 PORTS) :-
  _____________________________________________________________________
 *********************************************************************/
#define DIO_PORT_0  0        /*PORTA*/
#define DIO_PORT_1  1        /*PORTB*/
#define DIO_PORT_2  2        /*PORTC*/
#define DIO_PORT_3  3        /*PORTD*/
/**********************************************************************/

/*________________________________________________________________________

  DIRECTION (PORT or PIN) :-
  ________________________________________________________________________
 *************************************************************************/
#define DIO_INPUT 0         /*INPUT*/
#define DIO_OUTPUT 1        /*OUTPUT*/
/*************************************************************************/

/*_______________________________________________________________________

  VALUES (PORTS or PINS) :-
 _______________________________________________________________________
 ************************************************************************/
#define DIO_LOW 0
#define DIO_HIGH 1
#define DIO_ALL 255
/*************************************************************************/

/*________________________________________________________________________
ERROR HANDLING :-
 _______________________________________________________________________
 ************************************************************************/
#define NO_ERROR  0   //No error
#define ERROR  1     //error


/*______________________________________________________________________________________________*/
/*Description: Set PORT Direction (INPUT or OUTPUT)
 * Input     : Copy_u8PortNB (PORT Number) ,  Copy_u8Dir (PORT Direction)
 * Output    : Return Error Status (Error or NO Error)
 * */
extern uint8_t DIO_u8Init_PORT(uint8_t Copy_u8PortNB,uint8_t Copy_u8Dir);
/*______________________________________________________________________________________________*/

/*Description: Set PIN Direction (INPUT or OUTPUT)
 * Input     :Copy_u8PinNB (PIN Number) ,  Copy_u8Dir (PIN Direction)
 * Output    : Return Error Status (Error or NO Error)
 * */
extern uint8_t DIO_u8Init_PIN(uint8_t Copy_u8PinN,uint8_t Copy_u8Dir);
/*______________________________________________________________________________________________*/

/*Description: Set PORT Value (from 0 to 255)
 * Input     : Copy_u8PortNB (PORT Number) , Copy_u8Value (Value)
 * Output    : Return Error Status (Error or NO Error)
 * */
extern uint8_t DIO_u8SetPortValue(uint8_t Copy_u8PortNB,uint8_t Copy_u8Value);

/*______________________________________________________________________________________________*/
/*Description: Set PIN Value (HIGH or LOW)
 * Input     : Copy_u8PinNB (PIN Number) , Copy_u8Value (Value)
 * Output    : Return Error Status (Error or NO Error)
 * */
extern uint8_t DIO_u8SetPinValue(uint8_t Copy_u8PinN,uint8_t Copy_u8Value);

/*______________________________________________________________________________________________*/
/*Description: Get PORT Value
 * Input     :  Copy_u8PortNB (PORT Number),*Copy_u8Value (Pointer to send value to it)
 * Output    : Return Error Status (Error or NO Error)
 * */
extern uint8_t DIO_u8GetPortValue(uint8_t Copy_u8PortNB,uint8_t *Copy_u8Value);

/*______________________________________________________________________________________________*/
/*Description: Get PIN Value (HIGH or LOW)
 * Input     : Copy_u8PinN (PIN Number) ,*Copy_u8Value (Pointer to send value to it)
 * Output    : Return Error Status (Error or NO Error)
 * */
extern uint8_t DIO_u8GetPinValue(uint8_t Copy_u8PinN,uint8_t *Copy_u8Value);

/*______________________________________________________________________________________________*/
/*Description: Set PORT Type in case of INPUT Direction (PULL UP or FLOATING)
 * Input     :  Copy_u8PortNB (PORT Number),Copy_u8InputType(1 for PULL UP and 0 for FLOATING)
 * Output    : Return Error Status (Error or NO Error)
 * */
extern uint8_t DIO_u8SetPortInputType(uint8_t Copy_u8PortNB,uint8_t Copy_u8InputType);

/*______________________________________________________________________________________________*/
/*Description: Set PORT Type in case of INPUT Direction (PULL UP or FLOATING)
 * Input     : Copy_u8PinN(PIN NO) ,Copy_u8InputType(1 for PULL UP and 0 for FLOATING)
 * Output    : Return Error Status (Error or NO Error)
 * */
extern uint8_t DIO_u8SetPinInputType(uint8_t Copy_u8PinN,uint8_t Copy_u8InputType);

/*______________________________________________________________________________________________*/
#endif /* DIO_INTERFACE_H_ */
