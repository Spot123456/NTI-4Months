/*
 * ADC_Interface.h
 *
 * Created: 9/16/2023 10:32:39 AM
 *  Author: yahia
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


void ADC_init();
uint8 ADC_Start_Conversion(uint8 channel);

uint8 ADC_Start_Conversion_SYN(uint8 channel,uint8*reading);

uint8 ADC_Start_Conversion_ASYN(uint8 channel,uint16*reading,void(*notificationfun)(void));

uint8 ADC_Start_Chain_Conversion_ASYN(Chain_t* Copy_chain);



#endif /* ADC_INTERFACE_H_ */