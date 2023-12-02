/*
 * ADC_private.h
 *
 * Created: 9/16/2023 10:33:22 AM
 *  Author: yahia
 */ 


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


/******************************************/
/*              ADC REG                  */
/******************************************/

#define ADMUX_REG			*((volatile uint8*) 0x27)
#define REFS1		7       //this two bit Responsible for Vref of ADC
#define REFS0		6
#define ADLAR		5		// set (1) when work at 8 bit (read conversation) | set(0)for 10 bit
#define MUX4		4
#define MUX3		3
#define MUX2		2		// these 5 bit responsible for analog channel and Gain selection Bits
#define MUX1		1
#define MUX0		0


#define ADCSRA_REG			*((volatile uint8*)0x26)
#define ADEN		7		// ADC Enable
#define ADSC		6		// ADC Star Conversion
#define ADATE		5		// ADC Auto Trigger Enable (we don t need now)
#define ADIF		4		// ADC Interrupt Flag (clear by set it one manually or use interrupt for clear Auto)
#define ADIE		3		// ADC Interrupt Enable
#define ADPS2		2
#define ADPS1		1		// Prescaler Select Bits
#define ADPS0		0

#define SFIOR		*((volatile uint8*)0x50)					// special Function Register
#define ADTS2		7
#define ADTS1		6		//	ADC Auto trigger source (we don't use this now)
#define ADTS0		5

//for reading from ADLAR
#define ADCH		*((volatile uint8*)0x25)
#define ADCL		*((volatile uint8*)0x24)

#define ADC_T		*((volatile uint16*)0x24)

#define SFIOR_Reg	*((volatile uint8 *)0x50)
#define ADTS0		5
#define ADTS1		6
#define ADTS2		7

#endif /* ADC_PRIVATE_H_ */