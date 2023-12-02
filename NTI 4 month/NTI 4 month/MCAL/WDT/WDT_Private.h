/*
 * WDT_Private.h
 *
 * Created: 9/22/2023 10:53:07 AM
 *  Author: yahia
 */ 


#ifndef WDT_PRIVATE_H_
#define WDT_PRIVATE_H_

/****************************************************/
/*				WDT_REG								*/
/****************************************************/
#define MCUCSR_REG		*((volatile uint8*)0x54)

#define  WDRF	3

#define	WDTCR_REG		*((volatile uint8*)0x41)
#define WDP0	0
#define WDP1	1
#define WDP2	2
#define WDE		3
#define WDTOE	4

#endif /* WDT_PRIVATE_H_ */