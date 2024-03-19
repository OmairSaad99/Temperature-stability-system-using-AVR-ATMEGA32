/*
 * Temp_APP.h
 *
 *  Created on: Jan 8, 2023
 *      Author: HP
 */

#ifndef TEMP_APP_INTERFACE_H_
#define TEMP_APP_INTERFACE_H_

void TWI_VoidMasterInit (u8 Copy_u8SlaveAddress) ;

void Temp_App_Init(void) ;

void App_Start_Message(void) ;

void Read_Temperature(void) ;

void App_Main_Menu(void) ;

void App_Select_Mode(void);

void EEPROM_voidSendDataByte (u8 Copy_u8Data ,u16 Copy_u16Address) ;

void EEPROM_voidReadDataByte (u8 *Copy_u8Data ,u16 Copy_u16Address) ;

#endif /* TEMP_APP_INTERFACE_H_ */
