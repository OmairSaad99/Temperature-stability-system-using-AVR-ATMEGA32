/*
 * KPD_CFG.h
 *
 *  Created on: Apr 15, 2022
 *      Author: mahmo
 */

#ifndef KPD_CFG_H_
#define KPD_CFG_H_

#define KPD_PORT DIO_PORTC

#define KPD_COL0_PIN  DIO_PIN0
#define KPD_COL1_PIN  DIO_PIN1
#define KPD_COL2_PIN  DIO_PIN2
#define KPD_COL3_PIN  DIO_PIN3

#define KPD_ROW0_PIN  DIO_PIN4
#define KPD_ROW1_PIN  DIO_PIN5
#define KPD_ROW2_PIN  DIO_PIN6
#define KPD_ROW3_PIN  DIO_PIN7



#define KPD_NUM_ROWS   4
#define KPD_NUM_COLS   4

#define KPD_ARR_VAL  {{0,1,2,3} , {4,5,6,7} , {8,9,'+' , '-'} , {'E' , 'D'}}


#define KPD_NOT_PRESSED_KEY   0xff


#endif /* KPD_CFG_H_ */
