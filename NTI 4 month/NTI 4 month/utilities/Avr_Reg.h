/*
 * Avr_Reg.h
 *
 * Created: 9/9/2023 9:06:54 AM
 *  Author: yahia
 */ 

//#include	"datatypes.h"
#ifndef AVR_REG_H_
#define AVR_REG_H_
/**************************************/
/*			DIO_REG					  */
/**************************************/
// PORTA
#define PORTA_Reg	*((volatile uint8*)0x3B);
#define DDRA_Reg	*((volatile uint8*)0x3A);
#define PINA_Reg	*((volatile uint8*)0x39);
// PORTB
#define PORTA_Reg	*((volatile uint8*)0x38);
#define DDRA_Reg	*((volatile uint8*)0x37);
#define PINA_Reg	*((volatile uint8*)0x36);
//	PORTC
#define PORTA_Reg	*((volatile uint8*)0x35);
#define DDRA_Reg	*((volatile uint8*)0x34);
#define PINA_Reg	*((volatile uint8*)0x33);


#endif /* AVR_REG_H_ */