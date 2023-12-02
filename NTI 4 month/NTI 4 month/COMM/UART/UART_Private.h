/*
 * UART_Private.h
 *
 * Created: 9/18/2023 11:17:51 AM
 *  Author: Ahmed Nour
 */ 


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/************************************************************************/
/*                        UART REG                                              */
/************************************************************************/

#define UDR_REG		*((volatile uint8*)0x2C)

#define UCSRA_REG	*((volatile uint8*)0x2B)

#define UCSRA_RXC	7
#define UCSRA_TXC	6
#define UCSRA_UDRE	5
#define	UCSRA_FE	4
#define	UCSRA_DOR	3
#define	UCSRA_PE	2
#define	UCSRA_U2X	1

#define UCSRB_REG	*((volatile uint8*)0x2A)

#define UCSRB_RXEN	4
#define UCSRB_TXEN	3
#define UCSRB_UCSZ2	2

#define UBRRL_REG	*((volatile uint8*)0x29)
#define UBRRH_REG	*((volatile uint8*)0x40)
#define UBRRH_URSEL		7  /*select between UCSRC/UBRRH*/
#define UBRRH_UBRR11	3
#define UBRRH_UBRR10	2
#define UBRRH_UBRR9		1
#define UBRRH_UBRR8		0

#define UCSRC_REG	*((volatile uint8*)0x40)            // its the same reg of UBRRH
#define UCSRC_URSEL	7   /*select between UCSRC/UBRRH*/
#define UCSRC_UMSEL	6
#define UCSRC_UPM1	5
#define UCSRC_UPM0	4
#define UCSRC_USBS	3  //stop bit
#define UCSRC_UCSZ1	2
#define UCSRC_UCSZ0	1
#define	UCSRC_UCPOL	0

/*			modes		*/

#define no_party	0
#define	even_party	1
#define odd_party	2

#define	one_bit_stop	0
#define	two_bit_stop	1

#define UART_SYN		0
#define UART_ASYN		1

#endif /* UART_PRIVATE_H_ */