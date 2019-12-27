/*
 * AVR_TIMER1_REG.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: mosta
 */

#ifndef AVR_TIMER1_REG_H_
#define AVR_TIMER1_REG_H_

#define TIMER1_TCCR1A  *((volatile uint8_t*)0x4F)
#define TIMER1_TCCR1B *((volatile uint8_t*)0x4E)
//#define TCNT1H  *((volatile u8*)0x4D)
#define TIMER1_TCNT1  *((volatile uint16_t*)0x4C)
//#define TCNT1H
//#define TCNT1L

//#define OCR1AH  *((volatile u8*)0x4B)
#define TIMER1_OCR1A  *((volatile uint16_t*)0x4A)
//#define OCR1AH
//#define OCR1AL

#define TIMER1_OCR1B  *((volatile uint16_t*)0x48)
//#define OCR1BH
//#define OCR1BL

#define TIMER1_ICR1  *((volatile uint16_t*)0x46)
//#define ICR1H
//#define ICR1L

#define TIMER1_TIMSK  *((volatile uint8_t*)0x59)

#define TIMER1_TIFR  *((volatile uint8_t*)0x58)

#define TIMER1_TCCR1A_COM1A1 7
#define TIMER1_TCCR1A_COM1A0 6
#define TIMER1_TCCR1A_COM1B1 5
#define TIMER1_TCCR1A_COM1B0 4
#define TIMER1_TCCR1A_FOC1A 3
#define TIMER1_TCCR1A_FOC1B 2
#define TIMER1_TCCR1A_WGM11 1
#define TIMER1_TCCR1A_WGM10 0

#define TIMER1_TCCR1B_ICNC1 7
#define TIMER1_TCCR1B_ICES1 6
#define TIMER1_TCCR1B_WGM13 4
#define TIMER1_TCCR1B_WGM12 3
#define TIMER1_TCCR1B_CS12 2
#define TIMER1_TCCR1B_CS11 1
#define TIMER1_TCCR1B_CS10 0

#define TIMER1_TIMSK_TICIE1 5
#define TIMER1_TIMSK_OCIE1A 4
#define TIMER1_TIMSK_OCIE1B 3
#define TIMER1_TIMSK_TOIE1 2

#define TIMER1_TIFR_ICF1 5
#define TIMER1_TIFR_OCF1A 4
#define TIMER1_TIFR_OCF1B 3
#define TIMER1_TIFR_TOV1 2

#endif /* AVR_TIMER1_REG_H_ */
