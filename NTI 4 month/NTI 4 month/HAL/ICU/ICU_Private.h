/*
 * ICU_Private.h
 *
 * Created: 9/16/2023 11:34:11 AM
 *  Author: yahia
 */ 


#ifndef ICU_PRIVATE_H_
#define ICU_PRIVATE_H_


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

#define falling 0
#define rising	1


#endif /* ICU_PRIVATE_H_ */