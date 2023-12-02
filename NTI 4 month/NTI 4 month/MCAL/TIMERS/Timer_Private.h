/*
 * Timer_Private.h
 *
 * Created: 9/15/2023 9:57:44 AM
 *  Author: yahia
 */ 


#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

/************************************************************************/
/*                           TIMER0 REG                                 */
/************************************************************************/

#define TCCR0_REG				*((volatile uint8*)0x53)
#define TCCR0_FCO0			7					// bit must =0 when operating in PWM mode , 1 for compare match
#define TCCR0_COM01			5					/*Compare match output mode bit 1*/
#define TCCR0_COM00			4					/*Compare match output mode bit 0*/
#define TCCR0_WGM00			6					/*Waveform generation mode bit 0*/
#define TCCR0_WGM01			3					/*Waveform generation mode bit 1*/
#define TCCR0_CS02			2
#define TCCR0_CS01			1
#define TCCR0_CS00			0

#define OCR0_REG			*((volatile uint8*)0x5C)			/*Output compare match register*/
#define TCNT0_REG           *((volatile uint8*)0x52)			/*Timer counter 0 register*/
#define TIFR0_REG			*((volatile uint8*)0x58)

#define TIMSK_REG			*((volatile uint8*)0x59)			/*Timer mask register*/
#define TIMSK_TOIE0		0								/*Timer0 overflow interrupt enable*/
#define TIMSK_OCIE0		1								/*Timer0 compare match interrupt enable*/

/************************************************************************/
/*                    TIMER1 REG                                        */
/************************************************************************/

#define TCCR1A_REG   *((volatile uint8*)0x4F)    /*Timer1 Control registerA*/
#define TCCR1A_COM1A1 7							/*ChannelA compare match output mode bit 1 */
#define TCCR1A_COM1A0 6							/*ChannelA compare match output mode bit 0 */
#define TCCR1A_WGM11  1							/*wave form generation mode bit1 */
#define TCCR1A_WGM10  0							/*wave form generation mode bit0 */


#define TCCR1B_REG   *((volatile uint8*)0x4E)
#define TCCR1B_ICES1	6
#define TCCR1B_WGM13  4							/*wave form generation mode bit3 */
#define TCCR1B_WGM12  3							/*wave form generation mode bit4 */
#define TCCR1B_CS12	  2							/*Prescaler bit 2*/
#define TCCR1B_CS11	  1							/*Prescaler bit 1*/
#define TCCR1B_CS10	  0							/*Prescaler bit 0*/


#define ICR1_REG     *((volatile uint16*)0x46)	/*channelA output compare match register  (16 bit bec the output 16 bit to take the two reg : high & low)*/

#define OCR1A_REG    *((volatile uint16*)0x4A)	/*Input capture register */
#define TIFR1_REG	 *((volatile uint16*)0x58)	/*Input capture reg flags */

#define OCR1B_REG	 *((volatile uint16*)0x48) 
#define TIMSK1_REG	 *((volatile uint8*)0x59) 

#define TCNT1_REG	  *((volatile uint16*)0x4C) 
#endif /* TIMER_PRIVATE_H_ */