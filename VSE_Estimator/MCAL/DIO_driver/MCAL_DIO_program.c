/**************************************************************************
 * Author:   : Mostafa Nasser
 * File Name : DIO_program.c
 * Component : DIO function Implementation
 * Version   : 1
 ****************************************************************************/

/*File Includes*/

#include "STD_TYPES.h"

#include "BIT_MATH.h"

#include"MCAL_DIO_interface.h"

/*______________________________________________________________________
 * *********************************************************************
 * Function Implementations
 *  _____________________________________________________________________
 * *********************************************************************/

/*Description: Set PORT Direction (INPUT or OUTPUT)
 * Input     : Copy_u8PortNB (PORT Number) ,  Copy_u8Dir (PORT Direction)
 * Output    : Return Error Status (Error or NO Error)
 * */
extern uint8_t DIO_u8Init_PORT(uint8_t Copy_u8PortNB,uint8_t Copy_u8Dir)
{
	uint8_t Local_u8Error=NO_ERROR;          /*Local Error State*/
	
	if(Copy_u8Dir < DIO_INPUT || Copy_u8Dir > DIO_ALL) /*Check if entered direction is not available (negative value or more than 255(8 bit))*/
	{
		Local_u8Error=ERROR; /*Error Status : Error*/
	}
	else
	{	
		switch (Copy_u8PortNB)       /*Switch case on PORT Number*/
		{
			case DIO_PORT_0 :            /*InCase PORTA*/
				DIRECTION_PORT0 = Copy_u8Dir;    /*PORTA DATA Direction*/
					break;
			case DIO_PORT_1 :            /*InCase PORTB*/
				DIRECTION_PORT1 = Copy_u8Dir;    /*PORTB DATA Direction*/
					break;
			case DIO_PORT_2 :            /*InCase PORTC*/
				DIRECTION_PORT2 = Copy_u8Dir;    /*PORTC DATA Direction*/
					break;
			case DIO_PORT_3 :            /*InCase PORTD*/
				DIRECTION_PORT3 = Copy_u8Dir;    /*PORTD DATA Direction*/
					break;
			default :                   /*Other Case Wrong PORT NO*/
					Local_u8Error=ERROR;    /*Error Flag*/
					break;
		}
	}
	/*Return Error State*/
	return Local_u8Error;    /*if ERROR exist it return 1 if NO ERROR return 0*/
}


/*Description: Set PIN Direction (INPUT or OUTPUT)
 * Input     :Copy_u8PinNB (PIN Number) ,  Copy_u8Dir (PIN Direction)
 * Output    : Return Error Status (Error or NO Error)
 * */
extern uint8_t DIO_u8Init_PIN(uint8_t Copy_u8PinN,uint8_t Copy_u8Dir)
{
	uint8_t Local_u8Error=NO_ERROR;              /*Local Error State*/

	if(Copy_u8PinN > MAX_PIN_NO)     /*Check if Entered PIN NO. is more Than 7*/
	{
		Local_u8Error=ERROR;            /*Return ERROR*/
	}
	else if(Copy_u8Dir != DIO_INPUT && Copy_u8Dir != DIO_OUTPUT) /*Check if entered PIN Direction is not INPUT or OUTPUT*/
	{
		Local_u8Error=ERROR;           /*Return ERROR*/
	}
	else                          /*Entered PIN NO is not more than 7 and Direction is INPUT or OUTPUT*/
	{
		if(Copy_u8PinN>=0 && Copy_u8PinN<PIN_PER_PORT)
		{		/*InCase PORTA*/
			ASSIGN_BIT(DIRECTION_PORT0,Copy_u8PinN,Copy_u8Dir);  /*ASSIGN PIN NO to entered Direction*/
		}
		else if(Copy_u8PinN>=PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_1+1)*PIN_PER_PORT)
		{
			                                /*InCase PORTB*/
				ASSIGN_BIT(DIRECTION_PORT1,(Copy_u8PinN-PIN_PER_PORT),Copy_u8Dir);      /*ASSIGN PIN NO to entered Direction*/
		}
		else if(Copy_u8PinN>=2*PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_2+1)*PIN_PER_PORT)
		{
			                               /*InCase PORTC*/
				ASSIGN_BIT(DIRECTION_PORT2,(Copy_u8PinN-(2*PIN_PER_PORT)),Copy_u8Dir);      /*ASSIGN PIN NO to entered Direction*/
		}
		else if(Copy_u8PinN>=3*PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_3+1)*PIN_PER_PORT)
		{
			                               /*InCase PORTD*/
				ASSIGN_BIT(DIRECTION_PORT3,(Copy_u8PinN-(3*PIN_PER_PORT)),Copy_u8Dir);      /*ASSIGN PIN NO to entered Direction*/
		}
		else
		{
			/*Other Case Wrong PORT NO*/
				Local_u8Error=ERROR;                         /*Error Flag*/
		}			

	}

	return Local_u8Error;  /*if ERROR exist it return 1 if NO ERROR return 0*/
}


/*Description: Set PORT Value (from 0 to 255)
 * Input     : Copy_u8PortNB (PORT Number) , Copy_u8Value (Value)
 * Output    : Return Error Status (Error or NO Error)
 * */
uint8_t DIO_u8SetPortValue(uint8_t Copy_u8PortNB,uint8_t Copy_u8Value)
{
	uint8_t Local_u8Error=NO_ERROR;                 /*Local Error State*/
		
	if(Copy_u8Value < DIO_HIGH || Copy_u8Value > DIO_ALL) /*Check if entered Value is not available (negative value or more than 255(8 bit))*/
	{
		Local_u8Error=ERROR; /*Error Status : Error*/
	}
	else
	{
		switch (Copy_u8PortNB)               /*Switch case on PORT Number*/
		{
			case DIO_PORT_0 :                    /*InCase PORTA*/
				VALUE_PORT0= Copy_u8Value;         /*Set PORTA Value*/
					break;
			case DIO_PORT_1 :                    /*InCase PORTB*/
				VALUE_PORT1= Copy_u8Value;         /*Set PORTB Value*/
					break;
			case DIO_PORT_2 :                    /*InCase PORTC*/
				VALUE_PORT2= Copy_u8Value;         /*Set PORTC Value*/
					break;
			case DIO_PORT_3 :                    /*InCase PORTD*/
				VALUE_PORT3= Copy_u8Value;         //Set PORTD Value*/
					break;
			default :                           /*Other Case Wrong PORT NO*/
					Local_u8Error=ERROR;            /*Error Flag*/
					break;
		}
	}
		/*Return Error State*/
		return Local_u8Error;              /*if ERROR exist it return 1 if NO ERROR return 0*/
}

/*Description: Set PIN Value (HIGH or LOW)
 * Input     : Copy_u8PinNB (PIN Number) , Copy_u8Value (Value)
 * Output    : Return Error Status (Error or NO Error)
 * */
extern uint8_t DIO_u8SetPinValue(uint8_t Copy_u8PinN,uint8_t Copy_u8Value)
{
	uint8_t Local_u8Error=NO_ERROR;                 /*Local Error State*/

		if(Copy_u8PinN>MAX_PIN_NO)      /*Check if Entered PIN NO. is more Than 7*/
		{
			Local_u8Error=ERROR;           /*Return ERROR*/
		}
		else if(Copy_u8Value != DIO_LOW && Copy_u8Value != DIO_HIGH)   /*Check if entered PIN Direction is not INPUT or OUTPUT*/
		{
			Local_u8Error=ERROR;             /*Return ERROR*/
		}
		else                            /*Entered PIN NO is not more than 7 and Direction is INPUT or OUTPUT*/
		{
			
			if(Copy_u8PinN>=0 && Copy_u8PinN<PIN_PER_PORT)
			{		/*InCase PORTA*/
				ASSIGN_BIT(VALUE_PORT0,Copy_u8PinN,Copy_u8Value);  /*ASSIGN PIN NO to entered Direction*/
			}
			else if(Copy_u8PinN>=PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_1+1)*PIN_PER_PORT)
			{
												/*InCase PORTB*/
				ASSIGN_BIT(VALUE_PORT1,(Copy_u8PinN-PIN_PER_PORT),Copy_u8Value);       /*ASSIGN PIN NO to entered Direction*/
			}
			else if(Copy_u8PinN>=2*PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_2+1)*PIN_PER_PORT)
			{
											   /*InCase PORTC*/
				ASSIGN_BIT(VALUE_PORT2,(Copy_u8PinN-(2*PIN_PER_PORT)),Copy_u8Value);     /*ASSIGN PIN NO to entered Direction*/
			}
			else if(Copy_u8PinN>=3*PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_3+1)*PIN_PER_PORT)
			{
											   /*InCase PORTD*/
				ASSIGN_BIT(VALUE_PORT3,(Copy_u8PinN-(3*PIN_PER_PORT)),Copy_u8Value);       /*ASSIGN PIN NO to entered Direction*/
			}
			else
			{
				/*Other Case Wrong PORT NO*/
				Local_u8Error=ERROR;                         /*Error Flag*/
			}			
		}

		return Local_u8Error;   /*if ERROR exist it return 1 if NO ERROR return 0*/
}

/*Description: Get PORT Value
 * Input     :  Copy_u8PortNB (PORT Number),*Copy_u8Value (Pointer to send value to it)
 * Output    : Return Error Status (Error or NO Error)
 * */
uint8_t DIO_u8GetPortValue(uint8_t Copy_u8PortNB,uint8_t *Copy_u8Value)
{
	uint8_t Local_u8Error=NO_ERROR;              /*Local Error State : NO ERROR*/

	if(Copy_u8Value ==NULL_POINTER)  /*Check if Pointer points to Nothing*/
	{
		Local_u8Error=ERROR;             /*if it points to Nothing ERROR State : ERROR*/
	}
	else
	{
		switch(Copy_u8PortNB)            /*Switch case on PORT Number*/
		{
			case DIO_PORT_0 :            /*InCase PORTA*/
				(*Copy_u8Value)=READ_PORT0;    /*Make Pointer Point Value of PORTA*/
				break;
			case DIO_PORT_1 :            /*InCase PORTB*/
				(*Copy_u8Value)=READ_PORT1;    /*Make Pointer Point Value of PORTB*/
				break;
		    case DIO_PORT_2 :            /*InCase PORTC*/
		    	(*Copy_u8Value)=READ_PORT2;    /*Make Pointer Point Value of PORTC*/
				break;
			case DIO_PORT_3 :            /*InCase PORTD*/
				(*Copy_u8Value)=READ_PORT3;    /*Make Pointer Point Value of PORTD*/
				break;
			default :                   /*Other Case Wrong PORT NO*/
				Local_u8Error=ERROR;        /*Error Flag*/
			    break;
		}
		
	}
	return Local_u8Error;   /*if ERROR exist it return 1 if NO ERROR return 0*/
}

/*Description: Get PIN Value (HIGH or LOW)
 * Input     : Copy_u8PinN (PIN Number) ,*Copy_u8Value (Pointer to send value to it)
 * Output    : Return Error Status (Error or NO Error)
 * */
uint8_t DIO_u8GetPinValue(uint8_t Copy_u8PinN,uint8_t *Copy_u8Value)
{
	uint8_t Local_u8Error=NO_ERROR;        /*Local Error State : NO ERROR*/

		if(Copy_u8Value ==NULL_POINTER) /*Check if Pointer points to Nothing*/
		{
			Local_u8Error=ERROR;            /*if it points to Nothing ERROR State : ERROR*/
		}
		else if(Copy_u8PinN>MAX_PIN_NO)  /*Check if Entered PIN NO. is more Than 7*/
		{
			Local_u8Error=ERROR;            /*Return ERROR*/
		}
		else                           /*Pointer is Pointing to Value and PIN NO entered is not more than 7*/
		{
			
			if(Copy_u8PinN>=0 && Copy_u8PinN<PIN_PER_PORT)
			{		/*InCase PORTA*/
				(*Copy_u8Value)=GET_BIT(READ_PORT0,Copy_u8PinN);  /*ASSIGN PIN NO to entered Direction*/
			}
			else if(Copy_u8PinN>=PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_1+1)*PIN_PER_PORT)
			{
												/*InCase PORTB*/
				(*Copy_u8Value)=GET_BIT(READ_PORT1,(Copy_u8PinN-(PIN_PER_PORT)));      /*ASSIGN PIN NO to entered Direction*/
			}
			else if(Copy_u8PinN>=2*PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_2+1)*PIN_PER_PORT)
			{
											   /*InCase PORTC*/
				(*Copy_u8Value)=GET_BIT(READ_PORT2,(Copy_u8PinN-(2*PIN_PER_PORT)));     /*ASSIGN PIN NO to entered Direction*/
			}
			else if(Copy_u8PinN>=3*PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_3+1)*PIN_PER_PORT)
			{
											   /*InCase PORTD*/
				(*Copy_u8Value)=GET_BIT(READ_PORT3,(Copy_u8PinN-(3*PIN_PER_PORT)));     /*ASSIGN PIN NO to entered Direction*/
			}
			else
			{
				/*Other Case Wrong PORT NO*/
				Local_u8Error=ERROR;                         /*Error Flag*/
			}			
		}
		return Local_u8Error;   /*if ERROR exist it return 1 if NO ERROR return 0*/
}

/*Description: Set PORT Type in case of INPUT Direction (PULL UP or FLOATING)
 * Input     :  Copy_u8PortNB (PORT Number),Copy_u8InputType(1 for PULL UP and 0 for FLOATING)
 * Output    : Return Error Status (Error or NO Error)
 * */
uint8_t DIO_u8SetPortInputType(uint8_t Copy_u8PortNB,uint8_t Copy_u8InputType)
{
	/*Local Error State*/
	uint8_t Local_u8Error=NO_ERROR ,Copy_LocalStatus = NO_ERROR,Copy_LocalValue = DIO_OUTPUT;	/* check if any error happened. 0 fail/1 success*/
	/* Copy_LocalValue = 255 in case the port number wrong*/

	/* Get the value of the port direction*/
	switch (Copy_u8PortNB)
	{
	case DIO_PORT_0:
		Copy_LocalValue = DIRECTION_PORT0;
		break;
	case DIO_PORT_1:
		Copy_LocalValue = DIRECTION_PORT1;
		break;
	case DIO_PORT_2:
		Copy_LocalValue = DIRECTION_PORT2;
		break;
	case DIO_PORT_3:
		Copy_LocalValue = DIRECTION_PORT3;
		break;
	default:
		Copy_LocalStatus = ERROR;
		break;
	}

	/* check if the port has the same value of Copy_u8InputType*/
	if ((Copy_LocalValue != NO_ERROR))
	{
		Local_u8Error = ERROR;
		Copy_LocalStatus = ERROR;
	}
	if (Copy_LocalStatus != ERROR)
	{
		if ((Copy_u8InputType >= DIO_INPUT) && (Copy_u8InputType <= DIO_ALL))
		{
			switch (Copy_u8PortNB)                /*Switch case on PORT Number*/
			{
				case DIO_PORT_0 :                 /*InCase PORTA*/
					VALUE_PORT0= Copy_u8InputType;          /*Set PORTA Value*/
					break;
				case DIO_PORT_1 :                 /*InCase PORTB*/
					VALUE_PORT1= Copy_u8InputType;          /*Set PORTB Value*/
					break;
				case DIO_PORT_2 :                 /*InCase PORTC*/
					VALUE_PORT2= Copy_u8InputType;          /*Set PORTC Value*/
					break;
				case DIO_PORT_3 :                 /*InCase PORTD*/
					VALUE_PORT3= Copy_u8InputType;          /*Set PORTD Value*/
					break;
				default :                        /*Other Case Wrong PORT NO*/
				Local_u8Error=ERROR;                 /*Error Flag*/
				break;
			}
		}
		else
		{
			Local_u8Error=ERROR;
		}
	}
	else
	{
		Local_u8Error=ERROR;
	}

	/*Return Error State*/
	return Local_u8Error;       /*if ERROR exist it return 1 if NO ERROR return 0*/

}


/*Description: Set PORT Type in case of INPUT Direction (PULL UP or FLOATING)
 * Input     :  Copy_u8PortNB (PORT Number),Copy_u8PinN(PIN NO) ,Copy_u8InputType(1 for PULL UP and 0 for FLOATING)
 * Output    : Return Error Status (Error or NO Error)
 * */
uint8_t DIO_u8SetPinInputType(uint8_t Copy_u8PinN,uint8_t Copy_u8InputType)
{
	uint8_t Local_u8Error=NO_ERROR,Copy_LocalStatus = NO_ERROR,Copy_LocalValue = DIO_OUTPUT;	/* check if any error happened. 0 fail/1 success*/
	/* Copy_LocalValue = 1 in case the port number wrong*/


	if(Copy_u8PinN>=0 && Copy_u8PinN<PIN_PER_PORT)
	{		/*InCase PORTA*/
		Copy_LocalValue = GET_BIT(DIRECTION_PORT0,Copy_u8PinN);  /*ASSIGN PIN NO to read direction*/
	}
	else if(Copy_u8PinN>=PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_1+1)*PIN_PER_PORT)
	{
										/*InCase PORTB*/
		Copy_LocalValue = GET_BIT(DIRECTION_PORT1,(Copy_u8PinN-(PIN_PER_PORT)));      /*ASSIGN PIN NO to read direction*/
	}
	else if(Copy_u8PinN>=2*PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_2+1)*PIN_PER_PORT)
	{
									   /*InCase PORTC*/
		Copy_LocalValue = GET_BIT(DIRECTION_PORT2,(Copy_u8PinN-(2*PIN_PER_PORT)));     /*ASSIGN PIN NO to read direction*/
	}
	else if(Copy_u8PinN>=3*PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_3+1)*PIN_PER_PORT)
	{
									   /*InCase PORTD*/
		Copy_LocalValue = GET_BIT(DIRECTION_PORT3,(Copy_u8PinN-(3*PIN_PER_PORT)));     /*ASSIGN PIN NO to read direction*/
	}
	else
	{
		/*Other Case Wrong PORT NO*/
		Copy_LocalStatus=ERROR;                         /*Error Flag*/
	}


	/* check if the port has the same value of Copy_u8InputType*/
	if (Copy_LocalValue != NO_ERROR)
	{
		Local_u8Error = ERROR;
		Copy_LocalStatus = ERROR;
	}    
	/*Local Error State*/
	if (Copy_LocalStatus != ERROR)
	{

			if(Copy_u8PinN>MAX_PIN_NO)    /*Check if Entered PIN NO. is more Than 7*/
			{
				Local_u8Error=ERROR;         /*Return ERROR*/
			}
			else if(Copy_u8InputType != DIO_LOW && Copy_u8InputType != DIO_HIGH)  /*Check if entered PIN Direction is not INPUT or OUTPUT*/
			{
				Local_u8Error=ERROR;      /*Return ERROR*/
			}
			else                     /*Entered PIN NO is not more than 7 and Direction is INPUT or OUTPUT*/
			{
				if(Copy_u8PinN>=0 && Copy_u8PinN<PIN_PER_PORT)
				{		/*InCase PORTA*/
					ASSIGN_BIT(VALUE_PORT0,Copy_u8PinN,Copy_u8InputType); /*ASSIGN PIN NO to read direction*/
				}
				else if(Copy_u8PinN>=PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_1+1)*PIN_PER_PORT)
				{
													/*InCase PORTB*/
					ASSIGN_BIT(VALUE_PORT1,(Copy_u8PinN-(PIN_PER_PORT)),Copy_u8InputType);      /*ASSIGN PIN NO to read direction*/
				}
				else if(Copy_u8PinN>=2*PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_2+1)*PIN_PER_PORT)
				{
												   /*InCase PORTC*/
					ASSIGN_BIT(VALUE_PORT2,(Copy_u8PinN-(2*PIN_PER_PORT)),Copy_u8InputType);     /*ASSIGN PIN NO to read direction*/
				}
				else if(Copy_u8PinN>=3*PIN_PER_PORT && Copy_u8PinN<(DIO_PORT_3+1)*PIN_PER_PORT)
				{
												   /*InCase PORTD*/
					ASSIGN_BIT(VALUE_PORT3,(Copy_u8PinN-(3*PIN_PER_PORT)),Copy_u8InputType);    /*ASSIGN PIN NO to read direction*/
				}
				else
				{
					/*Other Case Wrong PORT NO*/
					Copy_LocalStatus=ERROR;                         /*Error Flag*/
				}
			}
	}
	else
	{
		Local_u8Error=ERROR;
	}

			return Local_u8Error;  /*if ERROR exist it return 1 if NO ERROR return 0*/
}
