/*
 * SleepModes.h
 *
 * Created: 12/15/2019 2:32:33 PM
 *  Author: Zeyad
 */ 


#ifndef SLEEPMODES_H_
#define SLEEPMODES_H_

#include "AVR_SLEEP_REG.h"

#define SM0 4
#define SM1 5
#define SM2 6
#define SE 7

extern void Sleep_PowerSaveMode(void);



#endif /* SLEEPMODES_H_ */
