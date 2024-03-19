/*
 * TWI_Interface.h
 *
 *  Created on: Jun 26, 2023
 *      Author: HP
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum
{
	NoError,
	StartConditError ,
	RepeatedStartError,
	SendSlaveAddressWithWriteErr,
	SendSlaveAddressWithReadErr,
	WriteDataByteErr,
	ReadDataByteErr,

}TWI_ErrStatus;

/*Pass 0 if Master Will Not be Addressed*/
void TWI_VoidMasterInit (u8 Copy_u8SlaveAddress);
void TWI_VoidSlaveInit (u8 Copy_u8SlaveAddress);
TWI_ErrStatus TWI_SendStatrtCondition (void);
TWI_ErrStatus TWI_SendRepeatedStart (void);
TWI_ErrStatus TWI_SendSlaveAddressWithWrite (u8 Copy_u8SlaveAddress);
TWI_ErrStatus TWI_SendSlaveAddressWithRead (u8 Copy_u8SlaveAddress);
TWI_ErrStatus TWI_MasterWriteDataByte (u8 Copy_u8DataByte);
TWI_ErrStatus TWI_MasterReadDataByte (u8 *Copy_u8DataByte);
void TWI_SendStopCondition (void);


#endif /* TWI_INTERFACE_H_ */
