/*
 * ADC_Interface.h
 *
 *  Created on: Apr 23, 2022
 *      Author: Ziad's
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef struct
{
	u8 *arrChainChannel ;
	u8 size ;
	void (*PtrNotification)(void);
	u16 *ArrChainResult ;
} Chain_t ;

typedef struct
{
	u8 *ArrChainChannel ;
	u8 size ;
	u16 *arrChainResult ;
} Chain_Sync ;

void ADC_vidInit(void);
u16 ADC_u8StatrtConversionSynch(u8 ch , u16 *Copy_ADCReading);
u16 ADC_u8StatrtConversionAsynch(u8 ch , u16 *Copy_ADCReading ,void(*Copy_pvNotificatinFunc)(void));
u16 ADC_u8StatrtConversionChainAsynch(Chain_t *chain);
u16 ADC_u8StatrtConversionChainSynch(Chain_Sync *chain) ;

#endif /* ADC_INTERFACE_H_ */
