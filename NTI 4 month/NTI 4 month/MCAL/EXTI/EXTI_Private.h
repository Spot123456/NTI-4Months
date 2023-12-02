/*
 * EXTI_Private.h
 *
 * Created: 9/14/2023 10:46:08 PM
 *  Author: Ahmed Nour
 */ 


#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

/************************************************************************/
/*                                 EXT interrupt                                     */
/************************************************************************/


#define EXTI_INT_0  __vector_1
#define EXTI_INI_1  __vector_2
#define EXTI_INI_2  __vector_3

#define ISR(INT_VECT)void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)



#define GICR_REG	*((volatile uint8*) 0x5B)
#define GICR_INT1	7
#define GICR_INT0	6
#define GICR_INT2	5

#define GIFR_REG	*((volatile uint8*) 0x5A)
#define GIFR_INT1	7
#define GIFR_INT0	6
#define GIFR_INT2	5
#define MCUCR_REG	*((volatile uint8*) 0x55)

#define MCUCR_ISC11 3
#define MCUCR_ISC10 2		//select sensing of Ext interrupt
#define MCUCR_ISC01 1
#define MCUCR_ISC00 0



#define MCUCSR_REG	*((volatile uint8*) 0x54)
#define MCUSCR_ISC2		6
#define SREG_REG    *((volatile uint8*) 0x5F)


#endif /* EXTI_PRIVATE_H_ */