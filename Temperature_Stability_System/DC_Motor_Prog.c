/*
 * DC_Motor_Prog.c
 *
 *  Created on: Jan 1, 2023
 *      Author: HP
 */

#include "types1.h"
#include "Bit_Math.h"

#include "DIO_interface.h"
#include "DC_Motor_Interface.h"
#include "DC_Motor_CFG.h"
#include "DC_Motor_Private.h"
#include "PWM_interface.h"
#include "PWM_CFG.h"
#include "PWM_private.h"
#include "ADC_Interface.h"

u8 Set_Morot_Direction(u8 Copy_Direction , u8 Copy_MotorState)
{
	u8 Local_ErrorState = OK ;
	if(Copy_Direction == CW)
	{
		if (Select_Port_Value == DIO_PORTA)
		{
			DIO_vidSetPortDir(Select_Port_Value , 0b11111111);
			if(Copy_MotorState == ON)
			{
				if(Select_CW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000001);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000010);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000100);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00001000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00010000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00100000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b01000000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b10000000);
				}
			}
			else if(Copy_MotorState == OFF)
			{
				if(Select_CW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
			}
			else
			{
				Local_ErrorState = NOK ;
			}
		}
		else if (Select_Port_Value == DIO_PORTB)
		{
			DIO_vidSetPortDir(Select_Port_Value , 0b11111111);
			if(Copy_MotorState == ON)
			{
				if(Select_CW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000001);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000010);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000100);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00001000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00010000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00100000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b01000000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b10000000);
				}
			}
			else if(Copy_MotorState == OFF)
			{
				if(Select_CW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
			}
			else
			{
				Local_ErrorState = NOK ;
			}
		}
		else if (Select_Port_Value == DIO_PORTC)
		{
			DIO_vidSetPortDir(Select_Port_Value , 0b11111111);
			if(Copy_MotorState == ON)
			{
				if(Select_CW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000001);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000010);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000100);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00001000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00010000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00100000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b01000000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b10000000);
				}
			}
			else if(Copy_MotorState == OFF)
			{
				if(Select_CW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
			}
			else
			{
				Local_ErrorState = NOK ;
			}

		}
		else if (Select_Port_Value == DIO_PORTD)
		{
			DIO_vidSetPortDir(Select_Port_Value , 0b11111111);
			if(Copy_MotorState == ON)
			{
				if(Select_CW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000001);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000010);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000100);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00001000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00010000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00100000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b01000000);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b10000000);
				}
			}
			else if(Copy_MotorState == OFF)
			{
				if(Select_CW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
			}
			else
			{
				Local_ErrorState = NOK ;
			}
		}
	}
	else if (Copy_Direction == CCW)
	{
		if (Select_Port_Value == DIO_PORTA)
		{
			DIO_vidSetPortDir(Select_Port_Value , 0b11111111);
			if(Copy_MotorState == ON)
			{
				if(Select_CCW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000001);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000010);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000100);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00001000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00010000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00100000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b01000000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b10000000);
				}
			}
			else if(Copy_MotorState == OFF)
			{
				if(Select_CCW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
			}
			else
			{
				Local_ErrorState = NOK ;
			}

		}
		else if (Select_Port_Value == DIO_PORTB)
		{
			DIO_vidSetPortDir(Select_Port_Value , 0b11111111);
			if(Copy_MotorState == ON)
			{
				if(Select_CCW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000001);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000010);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000100);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00001000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00010000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00100000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b01000000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b10000000);
				}
			}
			else if(Copy_MotorState == OFF)
			{
				if(Select_CCW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
			}
			else
			{
				Local_ErrorState = NOK ;
			}
		}
		else if (Select_Port_Value == DIO_PORTC)
		{
			DIO_vidSetPortDir(Select_Port_Value , 0b11111111);
			if(Copy_MotorState == ON)
			{
				if(Select_CCW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000001);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000010);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000100);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00001000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00010000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00100000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b01000000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b10000000);
				}
			}
			else if(Copy_MotorState == OFF)
			{
				if(Select_CCW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
			}
			else
			{
				Local_ErrorState = NOK ;
			}

		}
		else if (Select_Port_Value == DIO_PORTD)
		{
			DIO_vidSetPortDir(Select_Port_Value , 0b11111111);
			if(Copy_MotorState == ON)
			{
				if(Select_CCW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000001);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000010);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00000100);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00001000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00010000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b00100000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b01000000);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0b10000000);
				}
			}
			else if(Copy_MotorState == OFF)
			{
				if(Select_CCW_Pin_Valu == DIO_PIN0)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN1)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN2)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN3)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN4)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN5)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN6)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
				else if(Select_CCW_Pin_Valu == DIO_PIN7)
				{
					DIO_vidSetPortVal(Select_Port_Value , 0);
				}
			}
			else
			{
				Local_ErrorState = NOK ;
			}
		}
	}
	else if (Copy_Direction == One_Direction)
	{
		DIO_vidSetPortDir(Select_Port_Value , 0b11111111);
		if(Copy_MotorState == ON)
		{
			if(Select_One_Direction_PIN_Valu == DIO_PIN0)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0b00000001);
			}
			else if(Select_One_Direction_PIN_Valu == DIO_PIN1)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0b00000010);
			}
			else if(Select_One_Direction_PIN_Valu == DIO_PIN2)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0b00000100);
			}
			else if(Select_One_Direction_PIN_Valu == DIO_PIN3)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0b00001000);
			}
			else if(Select_One_Direction_PIN_Valu == DIO_PIN4)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0b00010000);
			}
			else if(Select_One_Direction_PIN_Valu == DIO_PIN5)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0b00100000);
			}
			else if(Select_One_Direction_PIN_Valu == DIO_PIN6)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0b01000000);
			}
			else if(Select_One_Direction_PIN_Valu == DIO_PIN7)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0b10000000);
			}
		}
		else if(Copy_MotorState == OFF)
		{
			if(Select_One_Direction_PIN_Valu == DIO_PIN0)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0);
			}
			else if(Select_One_Direction_PIN_Valu == DIO_PIN1)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0);
			}
			else if(Select_One_Direction_PIN_Valu == DIO_PIN2)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0);
			}
			else if(Select_One_Direction_PIN_Valu == DIO_PIN3)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0);
			}
			else if(Select_One_Direction_PIN_Valu == DIO_PIN4)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0);
			}
			else if(Select_One_Direction_PIN_Valu == DIO_PIN5)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0);
			}
			else if(Select_One_Direction_PIN_Valu == DIO_PIN6)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0);
			}
			else if(Select_One_Direction_PIN_Valu == DIO_PIN7)
			{
				DIO_vidSetPortVal(Select_Port_Value , 0);
			}
		}
		else
		{
			Local_ErrorState = NOK ;
		}

	}
	else
	{
		Local_ErrorState = NOK ;
	}

	return Local_ErrorState ;
}

u8 Control_Motor_Intensisty(u8 Copy_u8SelectControlPortIntensisty,u8 Copy_u8Direction , u8 Copy_u8Speed)
{
	u8 Local_u8ErrorState = OK ;
	if (Copy_u8Direction == CW)
	{
		if(Copy_u8SelectControlPortIntensisty == DIO_PORTB)
		{
			DIO_vidSetPinDir(Copy_u8SelectControlPortIntensisty , DIO_PIN3 , DIO_OUTPUT);
			TIMR0_VidSetCompMatchVal(Copy_u8Speed);
		}
		else if(Copy_u8SelectControlPortIntensisty == DIO_PORTD)
		{
#if Select_Timer1_OC_PIN == OCA
			DIO_vidSetPinDir(Copy_u8SelectControlPortIntensisty , Select_Timer1_OC_PIN , DIO_OUTPUT);
			SetTimer1_ICRval(256);
			TIMR1_VidSetCompMatchOCAVal(Copy_u8Speed);
#elif Select_Timer1_OC_PIN == OCB
			DIO_vidSetPinDir(Copy_u8SelectControlPortIntensisty , Select_Timer1_OC_PIN , DIO_OUTPUT);
			SetTimer1_ICRval(256);
			TIMR1_VidSetCompMatchOCBVal(Copy_u8Speed);
#endif

		}
		else
		{
			Local_u8ErrorState = NOK ;
		}
	}
	else if (Copy_u8Direction == CCW)
	{
		if(Copy_u8SelectControlPortIntensisty == DIO_PORTB)
		{
			DIO_vidSetPinDir(Copy_u8SelectControlPortIntensisty , DIO_PIN3 , DIO_OUTPUT);
			TIMR0_VidSetCompMatchVal(Copy_u8Speed);
		}
		else if(Copy_u8SelectControlPortIntensisty == DIO_PORTD)
		{
#if Select_Timer1_OC_PIN == OCA
			DIO_vidSetPinDir(Copy_u8SelectControlPortIntensisty , Select_Timer1_OC_PIN , DIO_OUTPUT);
			SetTimer1_ICRval(256);
			TIMR1_VidSetCompMatchOCAVal(Copy_u8Speed);
#elif Select_Timer1_OC_PIN == OCB
			DIO_vidSetPinDir(Copy_u8SelectControlPortIntensisty , Select_Timer1_OC_PIN , DIO_OUTPUT);
			SetTimer1_ICRval(256);
			TIMR1_VidSetCompMatchOCBVal(Copy_u8Speed);
#endif
		}
		else
		{
			Local_u8ErrorState = NOK ;
		}
	}
	else
	{
		Local_u8ErrorState = NOK ;
	}

	return Local_u8ErrorState ;
}
