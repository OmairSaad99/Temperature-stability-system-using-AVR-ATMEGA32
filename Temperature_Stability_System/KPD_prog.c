/*
  * KPD_prog.c
 *
 *  Created on: Apr 15, 2022
 *      Author: mahmo
 */
#include "types1.h"
#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/delay.h>
#include "DIO_Private.h"
#include "DIO_Interface.h"
#include "KPD_interface.h"
#include "KPD_CFG.h"
#include "KPD_private.h"



u8 KPD_GetKeyPressed(void)
{
	u8 pressed_key =KPD_NOT_PRESSED_KEY;
	u8 row,col , Local_State;

	static u8 KPD_Arr[KPD_NUM_ROWS][KPD_NUM_COLS] = KPD_ARR_VAL;

	static u8 KPD_COL_Arr[KPD_NUM_COLS] = {KPD_COL0_PIN , KPD_COL1_PIN ,  KPD_COL2_PIN , KPD_COL3_PIN};
	static u8 KPD_ROW_Arr[KPD_NUM_ROWS] = {KPD_ROW0_PIN ,KPD_ROW1_PIN ,KPD_ROW2_PIN  ,KPD_ROW3_PIN};
	for(col=0 ; col<KPD_NUM_COLS ; col++)
	{
		/*Activate Current Col*/
		DIO_vidSetPinVal(KPD_PORT,KPD_COL_Arr[col],DIO_LOW);

		for(row= 0 ; row < KPD_NUM_ROWS ; row++)
		{
			/*Read Current Row*/
			DIO_u8GetPinVal(KPD_PORT,KPD_ROW_Arr[row] , &Local_State) ;

			if (DIO_LOW == Local_State)
			{
				pressed_key = KPD_Arr[row][col];

				/*Polling if he still push button read it again*/
				while(DIO_LOW == Local_State)
				{
					DIO_u8GetPinVal(KPD_PORT,KPD_ROW_Arr[row] , &Local_State);
				}
				return pressed_key;

			}
		}
		/*Deactivate Current Col*/
		DIO_vidSetPinVal(KPD_PORT,KPD_COL_Arr[col],DIO_HIGH);
	}
	return pressed_key;
}

