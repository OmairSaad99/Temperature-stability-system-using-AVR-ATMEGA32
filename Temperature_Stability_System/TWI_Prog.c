/*
 * TWI_Prog.c
 *
 *  Created on: Jun 26, 2023
 *      Author: HP
 */

#include "Bit_Math.h"
#include "types1.h"

#include "TWI_Ptivate.h"
#include "TWI_CFG.h"
#include "TWI_Interface.h"

void TWI_VoidMasterInit (u8 Copy_u8SlaveAddress)
{
	/*Set CLock Freq to 400kbps*/
	TWDR = 2 ;

	CLR_BIT(TWPS0 , TWSR);
	CLR_BIT(TWPS1 , TWSR);

	/*Initialize The Node Address*/
	if (Copy_u8SlaveAddress != 0)
	{
		TWAR = Copy_u8SlaveAddress << 1;
	}

	/*Enable TWI*/
	SET_BIT(TWEN , TWCR);
}
void TWI_VoidSlaveInit (u8 Copy_u8SlaveAddress)
{
	/*Initialize The Node Address*/
	TWAR = Copy_u8SlaveAddress << 1;

	/*Enable TWI*/
	SET_BIT(TWEN , TWCR);

}
TWI_ErrStatus TWI_SendStatrtCondition (void)
{
	TWI_ErrStatus Local_ErrorStatus = NoError ;

	/*Send Start Condition*/
	SET_BIT(TWSTA , TWCR);

	/*Clear The Interrupt flag To Start Previous Operation*/
	SET_BIT(TWINT , TWCR);

	/*Wait Until Interrupt Flag Is raised Again and Previous operation Is Complete*/
	while (GET_BIT(TWINT , TWCR) != 0);

	if ((TWSR & 0xf8) != 0x08)
	{
		Local_ErrorStatus = StartConditError ;
	}
	else
	{
		/*Do No Thing*/
	}



	return Local_ErrorStatus ;
}
TWI_ErrStatus TWI_SendRepeatedStart (void)
{
	TWI_ErrStatus Local_ErrorStatus = NoError ;

	/*Send Start Condition*/
	SET_BIT(TWSTA , TWCR);

	/*Clear The Interrupt flag To Start Previous Operation*/
	SET_BIT(TWINT , TWCR);

	/*Wait Until Interrupt Flag Is raised Again and Previous operation Is Complete*/
	while (GET_BIT(TWINT , TWCR) != 0);

	if ((TWSR & 0xf8) != 0x10)
	{
		Local_ErrorStatus = RepeatedStartError ;
	}
	else
	{
		/*Do No Thing*/
	}

	return Local_ErrorStatus ;
}
TWI_ErrStatus TWI_SendSlaveAddressWithWrite (u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_ErrorStatus = NoError ;

	/*Clear The Start Condition bit*/
	CLR_BIT(TWSTA , TWCR);

	/*Set Slave Address In the 7 MSB*/
	TWDR = Copy_u8SlaveAddress << 1 ;

	/*For Write Request*/
	CLR_BIT(0,TWDR);

	if ((TWSR & 0xf8) != 0x18)
	{
		Local_ErrorStatus = SendSlaveAddressWithWriteErr ;
	}
	else
	{
		/*Do No Thing*/
	}



	return Local_ErrorStatus ;
}
TWI_ErrStatus TWI_SendSlaveAddressWithRead (u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_ErrorStatus = NoError ;

	/*Clear The Start Condition bit*/
	CLR_BIT(TWSTA , TWCR);

	/*Set Slave Address In the 7 MSB*/
	TWDR = Copy_u8SlaveAddress << 1 ;

	/*For Read Request*/
	SET_BIT(0,TWDR);

	if ((TWSR & 0xf8) != 0x40)
	{
		Local_ErrorStatus = SendSlaveAddressWithReadErr ;
	}
	else
	{
		/*Do No Thing*/
	}
	return Local_ErrorStatus ;
}
TWI_ErrStatus TWI_MasterWriteDataByte (u8 Copy_u8DataByte)
{
	TWI_ErrStatus Local_ErrorStatus = NoError ;

	/*Write The Data Byte*/
	TWDR = Copy_u8DataByte ;

	/*Clear The Interrupt Flag To Start The Previous operation*/
	SET_BIT(TWINT , TWCR);

	/*Wait Until Interrupt Flag Is raised Again and Previous operation Is Complete*/
	while (GET_BIT(TWINT , TWCR) != 0);

	if ((TWSR & 0xf8) != 0x28)
	{
		Local_ErrorStatus = WriteDataByteErr ;
	}
	else
	{
		/*Do No Thing*/
	}
	return Local_ErrorStatus ;
}
TWI_ErrStatus TWI_MasterReadDataByte (u8 *Copy_u8DataByte)
{
	TWI_ErrStatus Local_ErrorStatus = NoError ;

	/*Enable Master Generating ACK Bit*/
	SET_BIT(TWEA , TWCR);

	/*Clear The Interrupt Flag To Start The Previous operation*/
	SET_BIT(TWINT , TWCR);

	/*Wait Until Interrupt Flag Is raised Again and Previous operation Is Complete*/
	while (GET_BIT(TWINT , TWCR) != 0);

	if ((TWSR & 0xf8) != 0x50)
	{
		Local_ErrorStatus = ReadDataByteErr ;
	}
	else
	{
		/*Read The Received Data*/
		*Copy_u8DataByte = TWDR ;
	}
	return Local_ErrorStatus ;
}
void TWI_SendStopCondition (void)
{
	/*Generate Stop Condition On the Bus*/
	SET_BIT(TWSTO , TWCR);

	/*Clear The Interrupt Flag To Start The Previous operation*/
	SET_BIT(TWINT , TWCR);
}

