/*
 * AVR_TIMER_REG.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: mosta
 */

#ifndef AVR_TIMER0_REG_H_
#define AVR_TIMER0_REG_H_

#define TIMER0_TCCR0  *((volatile uint8_t*)0x53)
#define TIMER0_TCNT0  *((volatile uint8_t*)0x52)
#define TIMER0_TIMSK  *((volatile uint8_t*)0x59)
#define TIMER0_TIFR   *((volatile uint8_t*)0x58)
#define TIMER0_OCR0   *((volatile uint8_t*)0x5C)
#define SREG   *((volatile uint8_t*)0x5F)

#define TIMER0_TCCR0_WGM00 6
#define TIMER0_TCCR0_WGM01 3
#define TIMER0_TCCR0_FOC0  7
#define TIMER0_TCCR0_COM01 5
#define TIMER0_TCCR0_COM00 4

#define TIMER0_TCCR0_CS00 0
#define TIMER0_TCCR0_CS01 1
#define TIMER0_TCCR0_CS02 2

#define TIMER0_TIMSK_TOIE0 0
#define TIMER0_TIMSK_OCIE0 1

#define TIMER0_TIFR_TOV0   0
#define TIMER0_TIFR_OCF0   1


#endif /* AVR_TIMER0_REG_H_ */
