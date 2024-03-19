/*
 * ADC_Prog.c

 *
 *  Created on: Apr 23, 2022
 *      Author: Ziad's
 */
#include "types1.h"
#include "Bit_Math.h"
#define F_CPU 8000000UL

#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_CFG.h"

u8 Busy_State = IDLE;

static u16* ADC_u8Reading = NULL;
static void(*GlobalCallBackFun)(void) = NULL;

static u8* GlobalarrChainchannel = NULL;
static u8 GlobalSize;
static void(* GlobalNotificationFun)(void)  = NULL;
static u16* GlobalArrRes  = NULL;

static u8 index ;
static u8 ADC_u8ISRsource ;

void ADC_vidInit(void){

	/*VREF Choice*/
#if ADC_REF == ADC_REF_AVCC
	CLR_BIT(REFS1 , ADMUX);
	SET_BIT(REFS0 , ADMUX);
#elif ADC_REF == ADC_REF_AREF
	CLR_BIT(REFS1 , ADMUX);
	CLR_BIT(REFS0 , ADMUX);
#endif



	/*Result Adjust*/
#if RES_ADJ == RES_ADJ_RIGHT

	CLR_BIT(ADLAR , ADMUX);
#elif RES_ADJ == RES_ADJ_LEFT

	SET_BIT(ADLAR , ADMUX);
#endif

	/*Auto Triggre Enable*/
	if (ADC_MOD == AUTO_TRIGGEREd)
	{
		SET_BIT(ADATE,ADCSRA);
		if (TRIGGER_SOURCE == FREE_RUNNING_MODE)
		{
			SFIOR&=TRIGGER_SOURCE_MASK ;
			SFIOR|=TRIGGER_SOURCE;
		}
		else if (TRIGGER_SOURCE == EXTI_INTERRUPT)
		{
			SFIOR&=TRIGGER_SOURCE_MASK ;
			SFIOR|=TRIGGER_SOURCE;
		}
		else if (TRIGGER_SOURCE == COUNTER0_OVERFLOW)
		{
			SFIOR&=TRIGGER_SOURCE_MASK ;
			SFIOR|=TRIGGER_SOURCE;
		}
		else if (TRIGGER_SOURCE == COUNTER0_COMP)
		{
			SFIOR&=TRIGGER_SOURCE_MASK ;
			SFIOR|=TRIGGER_SOURCE;
		}

	}
	else if (ADC_MOD == ADC_MOD_Synch)
	{
		CLR_BIT(ADATE,ADCSRA);
	}

	/*Select Prescaller*/
	ADCSRA&=DIVISION_FACTOR_MASK;
	ADCSRA|=DIVISION_BY_128;

	/*ADC Enable*/
	SET_BIT(ADEN,ADCSRA);


}
u16 ADC_u8StatrtConversionSynch(u8 ch , u16 *Copy_ADCReading){

	u32 Local_u32Counter = 0 ;
	u8 Local_ErrorState = OK ;
	if (Busy_State == IDLE)
	{
		Busy_State = BUSY ;
		/*Select ADC Channel Bit*/
		ADMUX&=ADC_Channel_Mask ;
		ADMUX|=ch;

		/*Start Conversion*/
		SET_BIT(ADSC,ADCSRA);

		while(GET_BIT(ADIF,ADCSRA) == 0 && Local_u32Counter != ADC_TimeOut)
		{
			Local_u32Counter ++ ;
		}

		if (Local_u32Counter == ADC_TimeOut)
		{
			Local_ErrorState = NOK;
		}
		else
		{
			/*Clear ADC Conversion flag*/
			SET_BIT(ADIF,ADCSRA);
		}

		/*Result Adjust*/
#if RES_ADJ == RES_ADJ_RIGHT
		*Copy_ADCReading = ADC ;
		Busy_State = IDLE ;

#elif RES_ADJ == RES_ADJ_LEFT
		*Copy_ADCReading = ADCH ;
		Busy_State = IDLE ;
#endif
	}
	else
	{
		Local_ErrorState = BUSY_FUNC ;
	}

	return Local_ErrorState ;
}


u16 ADC_u8StatrtConversionAsynch(u8 ch , u16 *Copy_ADCReading ,void(*Copy_pvNotificatinFunc)(void))
{
	u8 Local_ErrorState = OK;
	if(Busy_State == IDLE)
	{
		if (Copy_ADCReading == NULL || Copy_pvNotificatinFunc == NULL)
		{
			Local_ErrorState = NULL;
		}
		else
		{
			Busy_State = BUSY;

			ADC_u8Reading = Copy_ADCReading;

			GlobalCallBackFun = Copy_pvNotificatinFunc;

			ADC_u8ISRsource = Single_Async_Conversion;

			/*Select ADC Channel Bit*/
			ADMUX&=ADC_Channel_Mask ;
			ADMUX|=ch;

			/*Start Conversion*/
			SET_BIT(ADSC,ADCSRA);


			/*Enable ADC Interrupt*/
			SET_BIT(ADIE,ADCSRA);
		}
	}

	else
	{
		Local_ErrorState = BUSY_FUNC;
	}
	return Local_ErrorState;

}



u16 ADC_u8StatrtConversionChainAsynch(Chain_t *chain)
{
	u8 Local_ErrorState = OK;

	if (chain == NULL)
	{
		Local_ErrorState = NULL;
	}
	else
	{
		if (Busy_State == IDLE)
		{
			Busy_State = BUSY;

			ADC_u8ISRsource = Chain_Conversion ;

			GlobalarrChainchannel = chain->arrChainChannel;
			GlobalSize = chain->size;
			GlobalNotificationFun = chain->PtrNotification;
			GlobalArrRes = chain->ArrChainResult;

			index = 0 ;

			/*Select ADC Channel Bit*/
			ADMUX&=ADC_Channel_Mask ;
			ADMUX|=GlobalarrChainchannel[index];

			/*Start Conversion*/
			SET_BIT(ADSC,ADCSRA);


			/*Enable ADC Interrupt*/
			SET_BIT(ADIE,ADCSRA);
		}
		else
		{
			Local_ErrorState = BUSY_FUNC;
		}

	}
	return Local_ErrorState;
}

u16 ADC_u8StatrtConversionChainSynch(Chain_Sync *chain)
{
	u8 Local_ErrorState = OK ;
	u32 Local_u32Counter = 0 ;

	if (chain == NULL)
	{
		Local_ErrorState = NOK ;
	}
	else
	{
		if(Busy_State == IDLE)
		{
			Busy_State = BUSY ;

			index = 0 ;

			while (index < chain->size)
			{
				/*Select ADC Channel Pin*/
				ADMUX &=ADC_Channel_Mask ;
				ADMUX|= chain->ArrChainChannel[index] ;

				/*Start Conversion*/
				SET_BIT(ADSC,ADCSRA);

				/*Waiting for ADC Conversion Complete Flag To Set*/
				while(GET_BIT(ADIF , ADCSRA) == 0 && Local_u32Counter != ADC_TimeOut)
				{
					Local_u32Counter ++ ;
				}

				if (Local_u32Counter == ADC_TimeOut)
				{
					Local_ErrorState = NOK ;
				}
				else
				{
					/*Clear ADC Conversion Complete Flag*/
					SET_BIT(ADIF,ADCSRA);

					/*ADC Conversion Result*/
					if(RES_ADJ == RES_ADJ_LEFT)
					{
						chain->arrChainResult[index] = ADCH ;
					}
					else if (RES_ADJ == RES_ADJ_RIGHT)
					{
						chain->arrChainResult[index] = ADC ;
					}

					/*Increment ADC Channel Index*/
					index ++ ;
				}
			}
			Busy_State = IDLE ;
		}
		else
		{
			Local_ErrorState = BUSY_FUNC ;
		}
	}

	return Local_ErrorState ;
}

void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	if (ADC_u8ISRsource == Single_Async_Conversion)
	{
		Busy_State = IDLE;
		/*Result Adjust*/
		if (RES_ADJ == RES_ADJ_RIGHT)
		{
			*ADC_u8Reading = ADC ;
		}
		else if (RES_ADJ == RES_ADJ_LEFT)
		{
			*ADC_u8Reading = ADCH ;
		}

		/*Calling Notification Function*/
		GlobalCallBackFun();

		/*Disable Interrupt*/
		CLR_BIT(ADIE,ADCSRA);
	}
	else if (ADC_u8ISRsource == Chain_Conversion)
	{
		/*Result Adjust*/
		if (RES_ADJ == RES_ADJ_RIGHT)
		{
			GlobalArrRes[index] = ADC ;
		}
		else if (RES_ADJ == RES_ADJ_LEFT)
		{
			GlobalArrRes[index] = ADCH ;
		}

		/*Increament Index*/
		index ++;

		if (index == GlobalSize)
		{
			/*Makes Conversion Idle*/
			Busy_State = IDLE ;


			/*calling Notification Function*/
			GlobalNotificationFun();

			/*Disable Interrupt*/
			CLR_BIT(ADIE,ADCSRA);


		}
		else
		{
			/*Select ADC Channel Bit*/
			ADMUX&=ADC_Channel_Mask ;
			ADMUX|=GlobalarrChainchannel[index];

			/*Start ADC Conversion Complete*/
			SET_BIT(ADSC,ADCSRA);

		}
	}
}

//	return ADC_REG;

