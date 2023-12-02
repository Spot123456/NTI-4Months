/*
 * SPI_Private.h
 *
 * Created: 9/22/2023 12:03:48 PM
 *  Author: yahia
 */ 


#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

/************************************************************************/
/*                          SPI REG                                     */
/************************************************************************/

#define SPDR_REG	*((volatile uint8*)0x2F)

#define SPSR_REG	*((volatile uint8*)0x2E)
#define SPSR_SPIF	7
#define SPSR_WCOL	6	/*write collision flag*/
#define SPSR_SPI2X	0	/*prescaler and double speed*/
#define SPCR_REG	*((volatile uint8*)0x2D)

#define SPCR_SPIE	7	/*interrupt enable*/
#define SPCR_SPE	6	/*spi enable*/
#define SPCR_DORD	5	/*data order : send LSB or MSB first*/
#define SPCR_MSTR	4	/*select master or slave*/
#define SPCR_CPOL	3	/*CLK polarity*/
#define SPCR_CPHA	2	/*CLK phase:send-receive or receive-send*/
#define SPCR_SPR1	1	/*Prescaler selection*/
#define SPCR_SPR0	0	/**/



/********************************/

/*			error type			*/

#define stack_full		1
#define stack_empty		0
#define stack_fine		2





#endif /* SPI_PRIVATE_H_ */