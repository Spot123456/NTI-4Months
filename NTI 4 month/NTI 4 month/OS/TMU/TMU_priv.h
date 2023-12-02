/*
 * TMU_priv.h
 *
 *  Created on: Oct 7, 2023
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef TMU_TMU_PRIV_H_
#define TMU_TMU_PRIV_H_

typedef struct 
{
    void(*schedTask)(void);
    uint16 u16Periodicty;
}TCB_t;

//Timer0
#define TCCR0               *((uint8*)0x53)
#define TCNT0               *((uint8*)0x52)
#define OCR0                *((uint8*)0x5C)
#define TIMSK               *((uint8*)0x59)
#define TIFR                *((uint8*)0x58)
//Timer1
#define TCCR1A	        	*((volatile uint8*)0x4F)
#define TCCR1B	        	*((volatile uint8*)0x4E)
#define TCNT1H	        	*((volatile uint8*)0x4D)
#define TCNT1L	        	*((volatile uint8*)0x4C)
#define OCR1AH	        	*((volatile uint8*)0x4B)
#define OCR1AL	        	*((volatile uint8*)0x4A)
#define OCR1BH	        	*((volatile uint8*)0x49)
#define OCR1BL	        	*((volatile uint8*)0x48)
//Timer2
#define TCCR2               *((uint8*)0x45)
#define TCNT2               *((uint8*)0x44)
#define OCR2                *((uint8*)0x43)

#endif /* TMU_TMU_PRIV_H_ */
