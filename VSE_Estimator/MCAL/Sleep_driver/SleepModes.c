/*
 * SleepModes.c
 *
 * Created: 12/15/2019 2:32:01 PM
 *  Author: Zeyad
 */ 
#include "SleepModes.h"



extern void Sleep_PowerSaveMode(void)
{
	SET_BIT(MCUCR,SM0);
	SET_BIT(MCUCR,SM1);
	SET_BIT(MCUCR,SE);
}
