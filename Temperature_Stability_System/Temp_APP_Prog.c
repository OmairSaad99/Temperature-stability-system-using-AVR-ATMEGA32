/*
 * Temp_APP_Prog.c
 *
 *  Created on: Jan 8, 2023
 *      Author: HP
 */

#include "types1.h"
#include "Bit_Math.h"

#include "DIO_interface.h"
#include "ADC_Interface.h"
#include "PWM_interface.h"
#include "EXTI_Interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "DC_Motor_Interface.h"
#include "Global_interface.h"
#include "Temp_APP_Interface.h"
#include "Temp_APP_CFG.h"
#include "Temp_APP_Private.h"
#include "TWI_Ptivate.h"
#include "TWI_CFG.h"
#include "TWI_Interface.h"
#include "avr/delay.h"

u16 Milli_Volt , Temperature , ADC_Reading ;
void Read_Temperature(void) ;
void Reset_System_INT2_Fun(void);
void App_Select_Mode(void);
void Represent_Temperature(void) ;

u8 Reset_TempApp_Flag = 0 ;
static u8 flag = 0;
static u8 counter = 13 ; /*counter for Location for First Number*/
static u8 Temperature_Flag = 0;
u16 Temp_key ; /*temp Variable for First Number*/
u16 Temp2_key ; /*temp Variable for Second Number*/
u8 arrOfChainChannel[2] = {0,1};
u8 arrOfResult[2] ;


Chain_t chain = {arrOfChainChannel , 2 , &Represent_Temperature , arrOfResult} ;

void Temp_App_Init(void)
{
	/*Set Data Port As Output*/
	DIO_vidSetPortDir(DIO_PORTD , 0b11111111);
	/*Set Control Port As Output*/
	DIO_vidSetPinDir(DIO_PORTA , DIO_PIN5 , DIO_OUTPUT);
	DIO_vidSetPinDir(DIO_PORTA , DIO_PIN6 , DIO_OUTPUT);
	DIO_vidSetPinDir(DIO_PORTA , DIO_PIN7 , DIO_OUTPUT);

	/*Make Col As output and Rows as Input*/
	DIO_vidSetPortDir(DIO_PORTC , 0b00001111);

	/*Initial Value for Keypad*/
	DIO_vidSetPortVal(DIO_PORTC , 0b11111111);

	/*Make PINA0 for LM35 AS Input*/
	DIO_vidSetPinDir(DIO_PORTA , DIO_PIN0 , DIO_INPUT);

	/*Make PORTA Direction as Output For LEDs*/
	DIO_vidSetPinDir(DIO_PORTA , DIO_PIN1 , DIO_OUTPUT);
	DIO_vidSetPinDir(DIO_PORTA , DIO_PIN2 , DIO_OUTPUT);
	DIO_vidSetPinDir(DIO_PORTA , DIO_PIN3 , DIO_OUTPUT);

	/*Set OCR PIN As OUTPUT*/
	DIO_vidSetPinDir(DIO_PORTB , DIO_PIN3 , DIO_OUTPUT);

	/*Set PORTA PIN4 for Buzzer as OUTPUT*/
	DIO_vidSetPinDir(DIO_PORTA , DIO_PIN4 , DIO_OUTPUT);

	/*Set PORTB PIN2 for Button As Input for reset*/
	DIO_vidSetPinDir(DIO_PORTB , DIO_PIN2 , DIO_INPUT);

	/*Activate PULL UP*/
	DIO_vidSetPinVal(DIO_PORTB , DIO_PIN2 , DIO_HIGH);

	/*Initialize LCD*/
	CLCD_voidInit();

	/*Initialize ADC*/
	ADC_vidInit();

	/*INT2 Call Back Function*/
	EXTI_INT2SetCallBack(&Reset_System_INT2_Fun);

	/*Initialize Timer0 Fast PWM*/
	Timer0_FastPWM_Mode();

	/*Initialize Interrupt2*/
	EXTI_Int2_Inti();

	/*Enable Global Interrupt*/
	Enable_Global_Interrupt();
}

void App_Start_Message(void)
{
	CLCD_vidSendString("Welcome On LCD") ;
	_delay_ms(2000);
	CLCD_voidSendCommand(1);
	_delay_ms(2000);
	CLCD_vidSendString("TEMP CTRL SYSTEM") ;
	_delay_ms(1000);
	CLCD_GoToXY(1,0);
	CLCD_vidSendString("Eng:Omair Saad");
	_delay_ms(3000);
	CLCD_voidSendCommand(1);

}

void App_Main_Menu(void)
{
	u8 key ;
	CLCD_vidSendString("1 - Start");
	CLCD_GoToXY(1 , 0);
	CLCD_vidSendString("2-Enter 2 Temp");
	while(1)
	{
		do
		{
			key = KPD_GetKeyPressed();
		}while(key == 0xff);

		if (key == '+' && flag == 0)
		{
			CLCD_voidSendCommand(1);
			CLCD_vidSendString("3-Show Temp");
		}
		else if (key == '-' && flag == 0)
		{
			CLCD_voidSendCommand(1);
			CLCD_vidSendString("1 - Start");
			CLCD_GoToXY(1 , 0);
			CLCD_vidSendString("2-Enter 2 Temp");
		}
		else if(key == 'D')
		{
			App_Select_Mode();
			break ;
		}
		else
		{
			flag = 0;
			CLCD_voidSendCommand(1);
			CLCD_vidSendString("Wrong Option !");
			_delay_ms(2000);
			CLCD_voidSendCommand(1);
			CLCD_vidSendString("1 - Start");
			CLCD_GoToXY(1 , 0);
			CLCD_vidSendString("2-Enter 2 Temp");
		}

	}
}


void Read_Temperature(void)
{
	u8 key ;
	static u8 Local_u8Counter = 0 ; /*Increament If low Temp Entered*/
	static u8 Temperature_Flag = 0;

	CLCD_voidSendCommand(1);

	CLCD_vidSendString("Enter Temp H:");
	CLCD_GoToXY(0 , 12);

	while(1)
	{

		do{
			if(Reset_TempApp_Flag == 1)
			{
				Local_u8Counter = 0 ;
				Reset_TempApp_Flag = 0 ;
				flag = 0 ;
				Temperature_Flag = 0 ;
				counter = 13 ;
				DIO_vidSetPinVal(DIO_PORTA , DIO_PIN3 , DIO_LOW);
				DIO_vidSetPinVal(DIO_PORTA , DIO_PIN2 , DIO_LOW);
				DIO_vidSetPinVal(DIO_PORTA , DIO_PIN1 , DIO_LOW);
				TIMR0_VidSetCompMatchVal(0);
				CLCD_voidSendCommand(1);
				App_Main_Menu();
				break ;
			}
			else
			{
				key = KPD_GetKeyPressed();
			}
		}while(key == 0xff);

		if(key == 0)
		{
			if(Temperature_Flag == 0)
			{

				CLCD_GoToXY(0,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp_key = key ;
				}
				else
				{
					Temp_key = (Temp_key * 10) + key ;
				}
				counter ++ ;
			}
			else if(Temperature_Flag == 1)
			{
				CLCD_GoToXY(1,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp2_key = key ;
				}
				else
				{
					Temp2_key = (Temp2_key * 10) + key ;
				}
				counter ++ ;
			}
		}
		else if (key == 1)
		{
			if(Temperature_Flag == 0)
			{
				CLCD_GoToXY(0,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp_key = key ;
				}
				else
				{
					Temp_key = (Temp_key * 10) + key ;
				}
				counter ++ ;
			}
			else if(Temperature_Flag == 1)
			{

				CLCD_GoToXY(1,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp2_key = key ;
				}
				else
				{
					Temp2_key = (Temp2_key * 10) + key ;
				}
				counter ++ ;
			}
		}
		else if (key == 2)
		{
			if(Temperature_Flag == 0)
			{

				CLCD_GoToXY(0,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp_key = key ;
				}
				else
				{
					Temp_key = (Temp_key * 10) + key ;
				}
				counter ++ ;
			}
			else if(Temperature_Flag == 1)
			{

				CLCD_GoToXY(1,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp2_key = key ;
				}
				else
				{
					Temp2_key = (Temp2_key * 10) + key ;
				}
				counter ++ ;
			}
		}
		else if (key == 3)
		{
			if(Temperature_Flag == 0)
			{

				CLCD_GoToXY(0,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp_key = key ;
				}
				else
				{
					Temp_key = (Temp_key * 10) + key ;
				}
				counter ++ ;
			}
			else if(Temperature_Flag == 1)
			{

				CLCD_GoToXY(1,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp2_key = key ;
				}
				else
				{
					Temp2_key = (Temp2_key * 10) + key ;
				}
				counter ++ ;
			}
		}
		else if (key == 4)
		{
			if(Temperature_Flag == 0)
			{

				CLCD_GoToXY(0,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp_key = key ;
				}
				else
				{
					Temp_key = (Temp_key * 10) + key ;
				}
				counter ++ ;
			}
			else if(Temperature_Flag == 1)
			{

				CLCD_GoToXY(1,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp2_key = key ;
				}
				else
				{
					Temp2_key = (Temp2_key * 10) + key ;
				}
				counter ++ ;
			}
		}
		else if (key == 5)
		{
			if(Temperature_Flag == 0)
			{

				CLCD_GoToXY(0,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp_key = key ;
				}
				else
				{
					Temp_key = (Temp_key * 10) + key ;
				}
				counter ++ ;
			}
			else if(Temperature_Flag == 1)
			{

				CLCD_GoToXY(1,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp2_key = key ;
				}
				else
				{
					Temp2_key = (Temp2_key * 10) + key ;
				}
				counter ++ ;
			}
		}
		else if (key == 6)
		{
			if(Temperature_Flag == 0)
			{

				CLCD_GoToXY(0,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp_key = key ;
				}
				else
				{
					Temp_key = (Temp_key * 10) + key ;
				}
				counter ++ ;
			}
			else if(Temperature_Flag == 1)
			{

				CLCD_GoToXY(1,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp2_key = key ;
				}
				else
				{
					Temp2_key = (Temp2_key * 10) + key ;
				}
				counter ++ ;
			}
		}
		else if (key == 7)
		{
			if(Temperature_Flag == 0)
			{

				CLCD_GoToXY(0,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp_key = key ;
				}
				else
				{
					Temp_key = (Temp_key * 10) + key ;
				}
				counter ++ ;
			}
			else if(Temperature_Flag == 1)
			{

				CLCD_GoToXY(1,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp2_key = key ;
				}
				else
				{
					Temp2_key = (Temp2_key * 10) + key ;
				}
				counter ++ ;
			}
		}
		else if (key == 8)
		{
			if(Temperature_Flag == 0)
			{

				CLCD_GoToXY(0,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp_key = key ;
				}
				else
				{
					Temp_key = (Temp_key * 10) + key ;
				}
				counter ++ ;
			}
			else if(Temperature_Flag == 1)
			{

				CLCD_GoToXY(1,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp2_key = key ;
				}
				else
				{
					Temp2_key = (Temp2_key * 10) + key ;
				}
				counter ++ ;
			}
		}
		else if (key == 9)
		{
			if(Temperature_Flag == 0)
			{

				CLCD_GoToXY(0,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp_key = key ;
				}
				else
				{
					Temp_key = (Temp_key * 10) + key ;
				}
				counter ++ ;
			}
			else if(Temperature_Flag == 1)
			{

				CLCD_GoToXY(1,counter) ;
				CLCD_voidSendData(key + '0');
				if (counter == 13)
				{
					Temp2_key = key ;
				}
				else
				{
					Temp2_key = (Temp2_key * 10) + key ;
				}
				counter ++ ;
			}
		}
		else if(key == 'E')/*Enter Low Temperature*/
		{
			if (Local_u8Counter == 0)
			{
				Local_u8Counter ++ ;
				Temperature_Flag = 1 ;
				CLCD_GoToXY(1 , 0);
				CLCD_vidSendString("Enter Temp L:");
				counter = 13;
			}
			else
			{
				Local_u8Counter = 0 ;
				Reset_TempApp_Flag = 0 ;
				flag = 0 ;
				Temperature_Flag = 0 ;
				counter = 13 ;

				EEPROM_voidSendDataByte(Temp_key , 0); // High
				_delay_ms(10);
				EEPROM_voidSendDataByte(Temp2_key , 1); // Low
				_delay_ms(10);

				CLCD_voidSendCommand(1);
				App_Main_Menu();
				break ;
			}
		}
	}
}

void Represent_Temperature(void)
{
	u8 local_u8LedState = 0b00000000 , Local_u8ReceivedTempHighData , Local_u8ReceivedTempLowData ;
	do
	{
		if(Reset_TempApp_Flag == 1) /*Reset System*/
		{
			Reset_TempApp_Flag = 0 ;
			flag = 0 ;
			Temperature_Flag = 0 ;
			counter = 13 ;
			DIO_vidSetPinVal(DIO_PORTA , DIO_PIN3 , DIO_LOW);
			DIO_vidSetPinVal(DIO_PORTA , DIO_PIN2 , DIO_LOW);
			DIO_vidSetPinVal(DIO_PORTA , DIO_PIN1 , DIO_LOW);
			TIMR0_VidSetCompMatchVal(0);
			CLCD_voidSendCommand(1);
			App_Main_Menu();
			break ;
		}
		else
		{
			EEPROM_voidReadDataByte(&Local_u8ReceivedTempHighData , 0);
			EEPROM_voidReadDataByte(&Local_u8ReceivedTempLowData , 1);

			if (Temperature <= Local_u8ReceivedTempLowData)
			{
				CLCD_voidSendCommand(1) ;
				CLCD_vidSendString("Low Temp");
				_delay_ms(1000);
				TIMR0_VidSetCompMatchVal(0);
				DIO_vidSetPinVal(DIO_PORTA , DIO_PIN3 , DIO_HIGH);
				DIO_vidSetPinVal(DIO_PORTA , DIO_PIN2 , DIO_LOW);
				DIO_vidSetPinVal(DIO_PORTA , DIO_PIN1 , DIO_LOW);
			}
			else if (Temperature > Local_u8ReceivedTempLowData && Temperature <= Local_u8ReceivedTempHighData)
			{
				CLCD_voidSendCommand(1) ;
				CLCD_vidSendString("Normal");
				_delay_ms(1000);
				TIMR0_VidSetCompMatchVal(128);
				DIO_vidSetPinVal(DIO_PORTA , DIO_PIN3 , DIO_LOW);
				DIO_vidSetPinVal(DIO_PORTA , DIO_PIN2 , DIO_HIGH);
				DIO_vidSetPinVal(DIO_PORTA , DIO_PIN1 , DIO_LOW);
			}
			else if (Temperature > Local_u8ReceivedTempHighData)
			{
				CLCD_voidSendCommand(1) ;
				CLCD_vidSendString("DANGEROUS!");
				_delay_ms(1000);
				TIMR0_VidSetCompMatchVal(255);
				DIO_vidSetPinVal(DIO_PORTA , DIO_PIN3 , DIO_LOW);
				DIO_vidSetPinVal(DIO_PORTA , DIO_PIN2 , DIO_LOW);
				for (u8 i=0 ; i<6 ; i++)
				{
					if (Reset_TempApp_Flag == 1)
					{
						break ;
					}
					else
					{
						TOGG_BIT(0,local_u8LedState);
						DIO_vidSetPinVal(DIO_PORTA , DIO_PIN2 , local_u8LedState);
						_delay_ms(1000);
					}
				}

			}
		}
	}while(1);
}

void App_Select_Mode(void)
{
	u8 key ;
	CLCD_voidSendCommand(1);
	CLCD_vidSendString("Enter Mode:") ;
	CLCD_GoToXY(0,12);
	while (1)
	{
		do
		{
			if(Reset_TempApp_Flag == 1)
			{
				Reset_TempApp_Flag = 0 ;
				flag = 0 ;
				Temperature_Flag = 0 ;
				counter = 13 ;
				DIO_vidSetPinVal(DIO_PORTA , DIO_PIN3 , DIO_LOW);
				DIO_vidSetPinVal(DIO_PORTA , DIO_PIN2 , DIO_LOW);
				DIO_vidSetPinVal(DIO_PORTA , DIO_PIN1 , DIO_LOW);
				TIMR0_VidSetCompMatchVal(0);
				CLCD_voidSendCommand(1);
				App_Main_Menu();
				break ;
			}
			else
			{
				key = KPD_GetKeyPressed();
			}
		}while(key == 0xff);

		if(key == 1) /*Start The System*/
		{
			CLCD_write_Number(key);
			_delay_ms(1000);
			CLCD_voidSendCommand(1);
			CLCD_vidSendString("Processing...") ;
			_delay_ms(1000);
			CLCD_voidSendCommand(1);
			Represent_Temperature();
			flag = 1 ;
		}
		else if(key == 2) /*Enter Temperature*/
		{
			CLCD_write_Number(key);
			_delay_ms(1000);
			Read_Temperature();
			flag = 1 ;
		}
		else if(key == 3) /*Show Current Temp*/
		{
			CLCD_write_Number(key);
			_delay_ms(1000);
			CLCD_voidSendCommand(1);
			while (1)
			{
				if (Reset_TempApp_Flag == 1)
				{
					break ;
				}
				else
				{
					ADC_u8StatrtConversionSynch(0 , &ADC_Reading);
					Milli_Volt = (u16)((u32)ADC_Reading * 500) / 256 ;
					Temperature = Milli_Volt / 10 ;

					CLCD_vidSendString("Curr Temp:");
					CLCD_GoToXY(0,11);
					CLCD_write_Number(Temperature);
					_delay_ms(1000);
					CLCD_voidSendCommand(1);
					flag = 1 ;
				}
			}
		}
		else
		{
			CLCD_voidSendCommand(1);
			CLCD_vidSendString("Wrong Option!");
			_delay_ms(2000);
			CLCD_voidSendCommand(1);
			CLCD_vidSendString("Enter Mode:") ;
			CLCD_GoToXY(0,12);
		}
	}
}

void Reset_System_INT2_Fun(void)
{
	Reset_TempApp_Flag = 1 ;
}

void EEPROM_voidSendDataByte (u8 Copy_u8Data ,u16 Copy_u16Address)
{
	TWI_SendStatrtCondition();

	TWI_SendSlaveAddressWithWrite(0b1010000 | A2 << 2 | Copy_u16Address >> 8);
	TWI_MasterWriteDataByte((u8)Copy_u16Address);
	TWI_MasterWriteDataByte(Copy_u8Data);

	TWI_SendStopCondition();
}

void EEPROM_voidReadDataByte (u8 *Copy_u8Data ,u16 Copy_u16Address)
{
	TWI_SendStatrtCondition();

	TWI_SendSlaveAddressWithWrite(0b1010000 | A2 << 2 | Copy_u16Address >> 8);
	TWI_MasterWriteDataByte((u8)Copy_u16Address);

	TWI_SendRepeatedStart();

	TWI_SendSlaveAddressWithRead(0b1010000 | A2 << 2 | Copy_u16Address >> 8);
	TWI_MasterReadDataByte(Copy_u8Data);

	TWI_SendStopCondition();
}
