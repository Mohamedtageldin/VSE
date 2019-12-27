/*
 * Timer_program.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: mosta
 */
#include "AVR_TIMER0_REG.h"
#include "AVR_TIMER1_REG.h"
#include "Timer_interface.h"


/*________________________________________________________________*/
/******************************************************************/
/*                        MACROS                                  */
/******************************************************************/
#define RESET_COUNTER 0

/*________________________________________________________________*/
/******************************************************************/
/*                        GLOBAL VARIABLES                        */
/******************************************************************/

void __vector_10(void)__attribute((signal,used));
static void (*TIMER0_CallBack)(void)=0;
//*******************************************************************************************

static uint8_t GSA_uint8_Prescaler_Timer[NO_OF_CHANNELS]={NULL,NULL,NULL};  /*Array to Copy Pre-scaler for each Timer Channel from Initialization  to Start*/
static uint8_t GSA_uint8_Mode_Timer[NO_OF_CHANNELS]={NULL,NULL,NULL};       /*Array to Copy Mode for each Timer Channel from Initialization to Start*/

/*________________________________________________________________*/
/******************************************************************/
/*                 FUNCTIONS IMPLEMENTATION                       */
/******************************************************************/


/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer/Counter Initialization
 * Input     : Timer_Configuration_S* Confg_S (Struct contain : Timer Channel, Pre-scaler, Timer mode , Mode as described in Struct)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t Timer_Init(Str_TimerConfiguration_t* Confg_S)
{
	uint8_t Local_uint8_ErrorStatus = ERROR_OK;  /*Error Status : No Error*/

	/*______________________Check Channel________________________________________________________________*/
	switch(Confg_S->Timer_Channel)                /*Check Timer Channel (Timer0 , Timer1, Timer2)*/
	{
		case TIMER0:                              /*In case Timer0*/
			/*_______________________Check Timer Mode________________________________________________________________*/
			switch(Confg_S -> Timer_Mode)         /*Check if Selected Mode is Counter or Timer*/
			{
				case TIMER_MODE :case COUNTER_MODE :
					GSA_uint8_Prescaler_Timer[TIMER0] = Confg_S ->Timer_Psc;  /*Set Pre-scaler to send it To Start Function*/
					break;
				default :
					Local_uint8_ErrorStatus = ERROR_NOK;  /*Return Error*/
					break;
			}
			/*________________________________________________________________________________________________________*/

			/*_____________________Check OverFlow Mode________________________________________________________________*/
			switch(Confg_S -> Interrupt_Mode)             /*Check If Chosen OverFlow mode is Polling or Interrupt*/
			{
				case POLLING :case INTERRUPT :
					GSA_uint8_Mode_Timer[TIMER0] = Confg_S ->Interrupt_Mode;  /*Set Mode to send it to Start Timer Function*/
					break;
				default :
					Local_uint8_ErrorStatus = ERROR_NOK;  /*Return Error*/
					break;
			}
			/*__________________________________________________________________________________________________________*/
			break;

		case TIMER1:   /*In Case Timer1*/
			/*_______________________Check Timer Mode________________________________________________________________*/
			switch(Confg_S -> Timer_Mode)         /*Check if Selected Mode is Counter or Timer*/
			{
				case TIMER_MODE :case COUNTER_MODE :
					GSA_uint8_Prescaler_Timer[TIMER1] = Confg_S ->Timer_Psc;  /*Set Pre-scaler to send it To Start Function*/
					break;

				default :
					Local_uint8_ErrorStatus = ERROR_NOK;  /*Return Error*/
					break;
			}
			/*________________________________________________________________________________________________________*/

			/*_____________________Check OverFlow Mode________________________________________________________________*/
			switch(Confg_S -> Interrupt_Mode)             /*Check If Chosen OverFlow mode is Polling or Interrupt*/
			{
				case POLLING :case INTERRUPT :
					GSA_uint8_Mode_Timer[TIMER1] = Confg_S ->Interrupt_Mode;  /*Set Mode to send it to Start Timer Function*/
					break;
				default :
					Local_uint8_ErrorStatus = ERROR_NOK;  /*Return Error*/
					break;
			}
			/*__________________________________________________________________________________________________________*/
			break;

		case TIMER2:   /* In Case Timer2*/
			/*_______________________Check Timer Mode________________________________________________________________*/
			switch(Confg_S -> Timer_Mode)         /*Check if Selected Mode is Counter or Timer*/
			{
				case TIMER_MODE :case COUNTER_MODE :
					GSA_uint8_Prescaler_Timer[TIMER2] = Confg_S ->Timer_Psc;  /*Set Pre-scaler to send it To Start Function*/
					break;
				default :
					Local_uint8_ErrorStatus = ERROR_NOK;  /*Return Error*/
					break;
			}
			/*________________________________________________________________________________________________________*/

			/*_____________________Check OverFlow Mode________________________________________________________________*/
			switch(Confg_S -> Interrupt_Mode)             /*Check If Chosen OverFlow mode is Polling or Interrupt*/
			{
				case POLLING :case INTERRUPT :
					GSA_uint8_Mode_Timer[TIMER2] = Confg_S ->Interrupt_Mode;  /*Set Mode to send it to Start Timer Function*/
					break;
				default :
					Local_uint8_ErrorStatus = ERROR_NOK;   /*Return Error*/
					break;
			}
			/*__________________________________________________________________________________________________________*/
			break;
		default :
			Local_uint8_ErrorStatus = ERROR_NOK;  /*Return Error*/
			break;
		/*___________________________________________________________________________________________________________________*/

	}

	return Local_uint8_ErrorStatus;   /*Return Error Status*/
}


/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer/Counter Start
 * Input     :  Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2), Tick Counting (Counts given by user)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t Timer_Start(uint8_t Copy_uint8_TimerChannel,uint32_t Copy_uint32_TickCounts)
{

	/*_____________________Variables________________________________________________________________________________*/
	uint8_t Local_uint8_ErrorStatus = ERROR_OK;
	/*______________________________________________________________________________________________________________*/

	switch(Copy_uint8_TimerChannel)                                       /*Check Channel Entered*/
	{
	/*_________________________________Timer Channels________________________________________________________________*/
		case TIMER0 :                                  /*In Case of Timer 0*/
			if(Copy_uint32_TickCounts < TIMER0_OVERFLOW)
			{
				/*TIMER0_COUNTER_REGISTER = TIMER0_OVERFLOW - Copy_uint32_TickCounts;*/
				switch(GSA_uint8_Mode_Timer[TIMER0])                /*Check Timer Mode*/
				{
				/*________________________________Timer Mode_____________________________________________________________*/
					case POLLING :                         /*If Selected Mode is Polling*/
						SET_BIT(TIMER0_CONTROL_REGISTER,TIMER0_CONTROL_WAVEGENERATION_1);
						TIMER0_CONTROL_REGISTER &=(uint8_t) CLR_PRE_SCALLER;                     /*Ensure Pre-scaler Bits is cleared*/
						TIMER0_CONTROL_REGISTER |=(uint8_t) GSA_uint8_Prescaler_Timer[TIMER0];  /*Use Pre-scaler Entered by user*/
						SET_BIT(TIMER0_INTERRUPT_FLAG_REGISTER,TIMER0_INTERRUPT_OVERFLOW_FLAG_BIT);
						TIMER0_OUTPUT_COMPARE_MATCH = Copy_uint32_TickCounts;
						break;
					case INTERRUPT:
						SET_BIT(TIMER0_CONTROL_REGISTER,TIMER0_CONTROL_WAVEGENERATION_1);
						CLR_BIT(TIMER0_CONTROL_REGISTER,TIMER0_CONTROL_WAVEGENERATION_0);
						/*SET_BIT(TIMER0_INTERRUPT_MASK_REGISTER,TIMER0_INTERRUPT_OVERFLOW_ENABLE_BIT);*/ /*Enable OverFlow Interrupt*/
						SET_BIT(STATUS_REGISTER,GLOBAL_INTERRUPT_BIT);   /*Enable Global Interrupt*/
						SET_BIT(TIMER0_INTERRUPT_MASK_REGISTER,TIMER0_INTERRUPT_COMPARE_MATCH_ENABLE_BIT);
						TIMER0_CONTROL_REGISTER &=(uint8_t) CLR_PRE_SCALLER;                     /*Ensure Pre-scaler Bits is cleared*/
						TIMER0_CONTROL_REGISTER |=(uint8_t) GSA_uint8_Prescaler_Timer[TIMER0];  /*Use Pre-scaler Entered by user*/
						TIMER0_OUTPUT_COMPARE_MATCH = Copy_uint32_TickCounts;
						break;
					default:
						Local_uint8_ErrorStatus = ERROR_NOK;
						break;
				/*_________________________________________________________________________________________________________________*/
				}
			}
			else
			{
				Local_uint8_ErrorStatus = ERROR_NOK; /*Error Status : Error*/
			}
		break;
		case TIMER1 :                                  /*In Case of Timer 0*/
			if(Copy_uint32_TickCounts < TIMER1_OVERFLOW)
			{
					TIMER1_COUNTER_REGISTER = TIMER1_OVERFLOW - Copy_uint32_TickCounts;
						switch(GSA_uint8_Mode_Timer[TIMER1])                /*Check Timer Mode*/
						{
						/*________________________________Timer Mode_____________________________________________________________*/
							case POLLING :                         /*If Selected Mode is Polling*/
								TIMER1_CONTROL_REGISTER_B &=(uint8_t) CLR_PRE_SCALLER;                     /*Ensure Pre-scaler Bits is cleared*/
								TIMER1_CONTROL_REGISTER_B |=(uint8_t) GSA_uint8_Prescaler_Timer[TIMER1];  /*Use Pre-scaler Entered by user*/
								SET_BIT(TIMER1_INTERRUPT_FLAG_REGISTER,TIMER1_INTERRUPT_OVERFLOW_FLAG_BIT);
								TIMER1_COUNTER_REGISTER = RESET_COUNTER;
								break;
							case INTERRUPT:
								TIMER1_CONTROL_REGISTER_B &=(uint8_t) CLR_PRE_SCALLER;                     /*Ensure Pre-scaler Bits is cleared*/
								TIMER1_CONTROL_REGISTER_B |=(uint8_t) GSA_uint8_Prescaler_Timer[TIMER1];  /*Use Pre-scaler Entered by user*/
								SET_BIT(TIMER1_INTERRUPT_MASK_REGISTER,TIMER1_INTERRUPT_OVERFLOW_ENABLE_BIT);   /*Enable OverFlow Interrupt*/
								SET_BIT(STATUS_REGISTER,GLOBAL_INTERRUPT_BIT);   /*Enable Global Interrupt*/

								break;
							default:
								Local_uint8_ErrorStatus = ERROR_NOK;
								break;
						/*_________________________________________________________________________________________________________________*/
						}
					}
					else
					{
						Local_uint8_ErrorStatus = ERROR_NOK; /*Error Status : Error*/
					}
				break;
		default:
				Local_uint8_ErrorStatus = ERROR_NOK; /*Error Status : Error*/
				break;
	}
	return Local_uint8_ErrorStatus; /*Return Error Status*/
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer/Counter Stop
 * Input     :  Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t Timer_Stop(uint8_t Copy_uint8_TimerChannel)
{
	uint8_t Local_uint8_ErrorStatus = ERROR_OK; /*Error Status : No Error*/

	switch(Copy_uint8_TimerChannel)
	{
		case TIMER0 :
			TIMER0_CONTROL_REGISTER &= (uint8_t) CLR_PRE_SCALLER; /*Stop Pre Scaler*/
			break;
		case TIMER1 :
			TIMER1_CONTROL_REGISTER_B &= (uint8_t) CLR_PRE_SCALLER; /*Stop Pre Scaler*/
			break;
		default:
			Local_uint8_ErrorStatus = ERROR_NOK; /*Error Status : Error*/

	}

	return Local_uint8_ErrorStatus; /*Return Error Status*/
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer Reset
 * Input     :  Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t Timer_Reset(uint8_t Copy_uint8_TimerChannel)
{
	uint8_t Local_uint8_ErrorStatus = ERROR_OK;  /*Error Status : No Error*/

	switch(Copy_uint8_TimerChannel)
	{
		case TIMER0 :
			TIMER0_COUNTER_REGISTER = RESET_COUNTER; /*Reset Counter */
			break;
		case TIMER1 :
			TIMER1_COUNTER_REGISTER = RESET_COUNTER; /*Reset Counter */

			break;
		default:
			Local_uint8_ErrorStatus = ERROR_NOK; /*Error Status : Error*/

	}

	return Local_uint8_ErrorStatus; /*Return Error Status*/
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: Get Timer Tick Time value to use it by user
 * Input     : Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2), *Timer_Time (Pointer to return Value)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t Timer_Get_TickTime(uint8_t Copy_uint8_TimerChannel, uint32_t *Copy_uint8Ptr_TimerTickTime)
{
	uint8_t Local_uint8_ErrorStatus = ERROR_OK;  /*Error Status :No Error*/

	if(Copy_uint8Ptr_TimerTickTime == NULL_POINTER)
	{
		Local_uint8_ErrorStatus = ERROR_NOK;   /*Error Status : Error*/
	}
	else
	{
		switch(Copy_uint8_TimerChannel)
		{
			case TIMER0 :
				if(GSA_uint8_Prescaler_Timer[TIMER0] == F_CPU_CLOCK_TIMER_0)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_SYSTEM_CLOCK_US;   /*Pre Scaler = System Clock*/
				}
				else if(GSA_uint8_Prescaler_Timer[TIMER0] == F_CPU_CLOCK_8_TIMER_0)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_8_US;   /*Pre Scaler = System Clock/8 */
				}
				else if(GSA_uint8_Prescaler_Timer[TIMER0] == F_CPU_CLOCK_64_TIMER_0)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_64_US;   /*Pre Scaler = System Clock/64 */
				}
				else if(GSA_uint8_Prescaler_Timer[TIMER0] == F_CPU_CLOCK_256_TIMER_0)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_256_US;   /*Pre Scaler = System Clock/256 */
				}
				else if(GSA_uint8_Prescaler_Timer[TIMER0] == F_CPU_CLOCK_1024_TIMER_0)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_1024_US;   /*Pre Scaler = System Clock/1024 */
				}
				else
				{
					Local_uint8_ErrorStatus = ERROR_NOK;   /*Error Status : Error*/
				}
				break;
			case TIMER1 :
				if(GSA_uint8_Prescaler_Timer[TIMER1] == F_CPU_CLOCK_TIMER_1)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_SYSTEM_CLOCK_US;   /*Pre Scaler = System Clock*/
				}
				else if(GSA_uint8_Prescaler_Timer[TIMER1] == F_CPU_CLOCK_8_TIMER_1)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_8_US;   /*Pre Scaler = System Clock/8 */
				}
				else if(GSA_uint8_Prescaler_Timer[TIMER1] == F_CPU_CLOCK_64_TIMER_1)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_64_US;   /*Pre Scaler = System Clock/64 */
				}
				else if(GSA_uint8_Prescaler_Timer[TIMER1] == F_CPU_CLOCK_256_TIMER_1)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_256_US;   /*Pre Scaler = System Clock/256 */
				}
				else if(GSA_uint8_Prescaler_Timer[TIMER1] == F_CPU_CLOCK_1024_TIMER_1)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_1024_US;   /*Pre Scaler = System Clock/1024 */
				}
				else
				{
					Local_uint8_ErrorStatus = ERROR_NOK;   /*Error Status : Error*/
				}
				break;
			default:
				Local_uint8_ErrorStatus = ERROR_NOK;     /*Error Status : Error*/
		}
	}

		return Local_uint8_ErrorStatus; /*Return Error Status*/
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: Get Timer Flag Status
 * Input     : Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2), *FlagStatus (Pointer to Flag)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t Timer_Get_FlagStatus(uint8_t Copy_uint8_TimerChannel, uint8_t *Copy_uint8Ptr_FlagStatus)
{
	uint8_t Local_uint8_ErrorStatus = ERROR_OK;        /*Error status : No Error */

	if(Copy_uint8Ptr_FlagStatus == NULL_POINTER)       /*Check if pointer points to NULL*/
	{
		Local_uint8_ErrorStatus = ERROR_NOK;
	}
	switch(Copy_uint8_TimerChannel)
	{
		case TIMER0 :
			/**Copy_uint8Ptr_FlagStatus = GET_BIT(TIMER0_INTERRUPT_FLAG_REGISTER,TIMER0_INTERRUPT_OVERFLOW_FLAG_BIT);*/ /*Read Flag*/
			*Copy_uint8Ptr_FlagStatus = GET_BIT(TIMER0_INTERRUPT_FLAG_REGISTER,TIMER0_INTERRUPT_COMPARE_MATCH_FLAG_BIT);
			break;
		case TIMER1 :
			*Copy_uint8Ptr_FlagStatus = GET_BIT(TIMER1_INTERRUPT_FLAG_REGISTER,TIMER1_INTERRUPT_OVERFLOW_FLAG_BIT); /*Read Flag*/
			break;
		default:
			Local_uint8_ErrorStatus = ERROR_NOK;  /*Error status : Error */
	}
	return Local_uint8_ErrorStatus;  /*Return Error*/
}

uint8_t TIMER_SetCallBack(uint8_t Copy_uint8_TimerChannel,void (*Copy_FunctionAddress)(void))
{
	uint8_t Local_u8ErrorState=0;              //Error State: No Error

	if(Copy_FunctionAddress==NULL_POINTER) //check if pointer points to Nothing
	{
		Local_u8ErrorState=1;             //Error State : Error
	}
	else
	{
		switch(Copy_uint8_TimerChannel)                   //Switch on INT
		{
			case TIMER0 :                                 //In Case INT0
				TIMER0_CallBack =Copy_FunctionAddress;//Send Function Address To Call Back pointer
				break;
			default :
				Local_u8ErrorState=1;  //Error State : Error
				break;

		}
	}
	return Local_u8ErrorState; //Return Error State
}
void __vector_10(void)
{
	if(TIMER0_CallBack!=0)
	{
		TIMER0_CallBack();
	}
}

