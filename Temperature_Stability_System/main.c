/*
 * main.c
 *
 *  Created on: Jan 3, 2023
 *      Author: HP
 */

#include "types1.h"
#include "Bit_Math.h"

#include "Temp_APP_Interface.h"
#include "DIO_interface.h"

#include "avr/delay.h"

void main(void)
{
	u8 Local_u8ReceivedData ;

	Temp_App_Init();

	App_Start_Message();

	EEPROM_voidReadDataByte(&Local_u8ReceivedData , 5);
	if (Local_u8ReceivedData != 1) /*Read High and Low temp at First Time Opening project*/
	{
		EEPROM_voidSendDataByte(1 , 5);
		_delay_ms(10);
		Read_Temperature();
	}
	else
	{
		App_Main_Menu();
		App_Select_Mode();
	}

	while (1)
	{
		/*Super Loop To prevent PC TO Count To End Of Memory*/
	}
}
