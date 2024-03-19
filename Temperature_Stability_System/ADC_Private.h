/*
 * ADC_Private.h
 *
 *  Created on: Apr 23, 2022
 *      Author: Ziad's
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/**************************************************/
/*******************MACROS************************/
/**************************************************/

#define ADC_REF_AVCC 1
#define ADC_REF_AREF 0
#define RES_ADJ_RIGHT 0
#define RES_ADJ_LEFT 1

#define ADC_MOD_INT 1
#define ADC_MOD_Synch 0

#define ADC_Channel_Mask   0b11100000

#define DIVISION_BY_128   7
#define DIVISION_FACTOR_MASK   0b11111000

#define TRIGGER_SOURCE_MASK   0b00011111
#define AUTO_TRIGGEREd 1
#define FREE_RUNNING_MODE   0
#define EXTI_INTERRUPT   2
#define COUNTER0_COMP   3
#define COUNTER0_OVERFLOW   4

#define RESO 6
#define ADLAR 5
#define ADEN 7
#define ADSC 6
#define ADIF 4
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2

// Define Ram

#define ACSR 		*((volatile u8*) 0x28)
#define ADMUX 		*((volatile u8*) 0x27)
#define REFS1   7
#define REFS0   6

#define ADCSRA 		*((volatile u8*) 0x26)
#define ADATE   5
#define ADIE    3

#define SFIOR       *((volatile u8*) 0x50)

#define ADCL 		*((volatile u8*) 0x24)
#define SREG   		*((volatile u8*) 0x5F)
#define GICR  		*((volatile u8*) 0x5B)
#define MCUCR  		*((volatile u8*) 0x55)
#define ADCH  		*((volatile u8*) 0x25) /*if i want 8 bit Output representaion*/
#define ADC 		*((volatile u16*) 0x24)/*if i want 10 bit Output representaion*/


#define ENABLED     1
#define DISABLED   2

#define Chain_Conversion  2
#define Single_Async_Conversion  3


#endif /* ADC_PRIVATE_H_ */
