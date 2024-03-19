/*
 * DC_Motor_Interface.h
 *
 *  Created on: Jan 1, 2023
 *      Author: HP
 */

#ifndef DC_MOTOR_INTERFACE_H_
#define DC_MOTOR_INTERFACE_H_



#define CW 1

#define CCW 2

#define One_Direction 3

#define ON 4

#define OFF 5

u8 Set_Morot_Direction(u8 Copy_Direction , u8 Copy_MotorState) ;
u8 Control_Motor_Intensisty(u8 Copy_u8SelectControlPortIntensisty,u8 Copy_u8Direction , u8 Copy_u8Speed) ;

#endif /* DC_MOTOR_INTERFACE_H_ */
