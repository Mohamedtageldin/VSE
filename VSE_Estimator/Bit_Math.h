/*
 * MACRO.h
 *
 * Created: 1/9/2018 3:08:59 AM
 *  Author: dell
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SETBIT(reg,bit) (reg|=(1<<bit))
#define CLEARBIT(reg,bit) (reg &= ~(1<<bit))
#define TOGGLE(reg,bit) (reg ^=(1<<bit))
#define READBIT(reg,bit) ((reg &(1<<bit))>>bit)
#define IS_BIT_SET(reg,bit) ((((reg &(1<<bit))>>bit)==1)?(1):(0))
#define IS_BIT_CLEARED(reg,bit) ((((reg &(1<<bit))>>bit)==1)?(0):(1))
#define CIRCULAR_SHIFT_RIGHT(reg,bit) ((reg>>bit)|(reg<<(8-bit)))
#define CIRCULAR_SHIFT_LEFT(reg,bit) ((reg<<bit)|(reg>>(8-bit)))
#define ASSIGN_BIT(VAR,BIT_NO,VALUE)  VAR=(VAR &(~(1<<BIT_NO))) | (VALUE<<BIT_NO)  //ASSIGHN BIT_NO in variable to HIGH or LOW*/




#endif /* BIT_MATH_H_ */