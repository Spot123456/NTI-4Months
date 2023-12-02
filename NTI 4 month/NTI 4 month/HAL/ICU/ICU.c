/*
 * ICU.c
 *
 * Created: 9/16/2023 11:34:28 AM
 *  Author: Ahmed Nour
 */ 

#include "../../utilities/datatypes.h"
#include "../../utilities/math.h"
#include "../../MCAL/TIMERS/Timer_Interface.h"
#include "ICU_Private.h"
#include "ICU_Interface.h"
#include "ICU_config.h"


/*
static void (*pf)(void)=NULL;
void ICU_init()
{
	#if mode == rising
	set_bit(TCCR1B_REG,TCCR1B_ICES1);
	#elif	mode == falling
	clr_bit(TCCR1B_REG,TCCR1B_ICES1);
	#endif
	
		// select no prescaler
		set_bit(TCCR1B_REG,1);
		
		//TCNT1_REG=0;
	// enable icu interrupt
	set_bit(TIMSK1_REG,5);
}

void ICU_change_sence(uint8 sence)
{
	switch (sence)
	{
		case falling:	clr_bit(TCCR1B_REG,TCCR1B_ICES1); break;
		case rising:	set_bit(TCCR1B_REG,TCCR1B_ICES1);	break;
		
	}
}

uint16 ICU_get_inputCap()
{
	uint16 result;
	//result=ICR1_REG;
	result=TCNT1_REG;
	return result;
}

void ICU_clear_timer()
{
	//ICR1_REG=0;
	TCNT1_REG=0;
}


void set_CallBackFun_ICU(void(*func)(void))
{
	if(func!=NULL)
	{
		pf=func;
	}
	
}

void __vector_6(void) __attribute__((signal));\
void __vector_6(void)
{
	if(pf!=NULL)
	{
		
		pf();
	//	set_bit(TIFR1_REG,5);
		
	}
}
*/


/*
 * ICU.c
 *
 * Created: 5/12/2023 8:31:54 PM
 *  Author: yahia
 */ 

#include "../../utilities/datatypes.h"
#include "../../utilities/math.h"

#include "ICU_Interface.h"
#include "ICU_config.h"
#include "ICU_Private.h"

static void (*pf)(void)=NULL;

void ICU_init()
{
	// select no prescaler
	set_bit(TCCR1B_REG,1); 
	// enable the interrupt
	set_bit(TIMSK1_REG,5);
	//select the raising first 
	set_bit(TCCR1B_REG,6);
}

void ICU_set_EdgeType(uint8 Edge_Type)
{
	switch(Edge_Type)
	{
		case raising : set_bit(TCCR1B_REG,6); break;
		case falling : clr_bit(TCCR1B_REG,6); break;
	}
	
}

uint16 ICU_get_inputCap()
{
	uint16 result;
	//result=ICR1_REG;
	result=TCNT1_REG;
	return result;
}

void ICU_clear_timer()
{
	//ICR1_REG=0;
	TCNT1_REG=0;
}


void set_CallBackFun_ICU(void(*func)(void))
{
	if(func!=NULL)
	{
		pf=func;
	}
	
}
/*
ISR(TIMER1_CAPT_vect)
{
	if(pf!=NULL)
	{
		pf();
		set_bit(TIFR1_REG,5);
	}
}
*/

void __vector_6(void) __attribute__((signal));\
void __vector_6(void)
{
	if(pf!=NULL)
	{
		
		pf();
		//	set_bit(TIFR1_REG,5);
		
	}
}
