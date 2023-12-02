/*
 * EXTI.c
 *
 * Created: 9/14/2023 10:45:02 PM
 *  Author: AHmed Nour
 */ 

#include "../../utilities/datatypes.h"
#include "../../utilities/math.h"
#include "../../utilities/Erorr_Type.h"
#include "EXTI_Interface.h"
#include "EXTI_Config.h"
#include "EXTI_Private.h"

static	void (*EXTI_pvINTCallBackFunc[3])(void)= {NULL};

void Enable_Globla_INT();
void EXTI_Inti()
{
	
	
	#if EXTI_0
	// this is for first sense we can able change on run time with fun EXTI_sense
	// for low level of interrupt is generates
		#if		Select_sense_0 == low_level
		clr_bit(MCUCR_REG,MCUCR_ISC00);
		clr_bit(MCUCR_REG,MCUCR_ISC01);
		
		// for on change of interrupt is generates
		#elif	Select_sense_0 == on_change
		set_bit(MCUCR_REG,MCUCR_ISC00);
		clr_bit(MCUCR_REG,MCUCR_ISC01);
		
		// for falling edge of interrupt is generates
		#elif	Select_sense_0 == falling_edge
		clr_bit(MCUCR_REG,MCUCR_ISC00);
		set_bit(MCUCR_REG,MCUCR_ISC01);
		
		// for rising edge of interrupt is generates
		#elif	Select_sense_0 == Rising_edge
		set_bit(MCUCR_REG,MCUCR_ISC00);
		set_bit(MCUCR_REG,MCUCR_ISC01);
		
		#endif
		// enable EXTI
	set_bit(GICR_REG,GICR_INT0);
	
	#endif
	
	#if EXTI_1
		// this is for first sense we can able change on run time with fun EXTI_sense
		// for low level of interrupt is generates
		#if		Select_sense_1 == low_level
		clr_bit(MCUCR_REG,MCUCR_ISC10);
		clr_bit(MCUCR_REG,MCUCR_ISC11);
		
		// for on change of interrupt is generates
		#elif	Select_sense_1 == on_change
		set_bit(MCUCR_REG,MCUCR_ISC10);
		clr_bit(MCUCR_REG,MCUCR_ISC11);
		
		// for falling edge of interrupt is generates
		#elif	Select_sense_1 == falling_edge
		clr_bit(MCUCR_REG,MCUCR_ISC10);
		set_bit(MCUCR_REG,MCUCR_ISC11);
		
		// for rising edge of interrupt is generates
		#elif	Select_sense_1 == Rising_edge
		set_bit(MCUCR_REG,MCUCR_ISC10);
		set_bit(MCUCR_REG,MCUCR_ISC11);
		
		#endif
		// enable EXTI_1 
	set_bit(GICR_REG,GICR_INT1);
	#endif

	#if EXTI_2
		// this is for first sense we can able change on run time with fun EXTI_sense
		// for low level of interrupt is generates
		
		// for falling edge of interrupt is generates
		#if	Select_sense_0 == falling_edge
		clr_bit(MCUCSR_REG,MCUSCR_ISC2);
		
		// for rising edge of interrupt is generates
		#elif	Select_sense_0 == Rising_edge
		clr_bit(MCUCSR_REG,MCUSCR_ISC2);

		#endif
		// enable EXTI_2
	set_bit(GICR_REG,GICR_INT2);
#endif
	
}

void Enable_Globla_INT()
{
	SREG_REG|=(1<<7); // for global interrupt
	//asm("sei");
	 
}
void Disable_global_int()
{
	asm("cli"); 
}

uint8 EXTI_sense(uint8 EXTI,uint8 sense)
{
	uint8 type_error=ok; // this is type error decade that fun work correctly or not
	switch(EXTI)
	{
		case EXTI0 :
		switch (sense)
		{
			case low_level:		clr_bit(MCUCR_REG,MCUCR_ISC00); clr_bit(MCUCR_REG,MCUCR_ISC01); break;
			case on_change:		set_bit(MCUCR_REG,MCUCR_ISC00); clr_bit(MCUCR_REG,MCUCR_ISC01); break;
			case falling_edge:	clr_bit(MCUCR_REG,MCUCR_ISC00); set_bit(MCUCR_REG,MCUCR_ISC01); break;
			case Rising_edge:	set_bit(MCUCR_REG,MCUCR_ISC00); set_bit(MCUCR_REG,MCUCR_ISC01); break;
			default: type_error=nok; // if pass any wrong type
		}
		case EXTI1 :
		switch (sense)
		{
			// for low level of interrupt is generates
			case low_level:	clr_bit(MCUCR_REG,MCUCR_ISC10);clr_bit(MCUCR_REG,MCUCR_ISC11); break;
		
			// for on change of interrupt is generates
			case on_change:	set_bit(MCUCR_REG,MCUCR_ISC10);clr_bit(MCUCR_REG,MCUCR_ISC11);break;
			
			// for falling edge of interrupt is generates
			case falling_edge:	clr_bit(MCUCR_REG,MCUCR_ISC10);set_bit(MCUCR_REG,MCUCR_ISC11);break;
			
			// for rising edge of interrupt is generates
			case Rising_edge:	set_bit(MCUCR_REG,MCUCR_ISC10);set_bit(MCUCR_REG,MCUCR_ISC11);break;
			
			default:  type_error=nok;
		}
		case EXTI2 :
		switch (sense)
		{
			// for falling edge of interrupt is generates
			case falling_edge:	clr_bit(MCUCSR_REG,MCUSCR_ISC2); break;
			
			// for rising edge of interrupt is generates
			case Rising_edge :	clr_bit(MCUCSR_REG,MCUSCR_ISC2); break;
			default:  type_error=nok;
		}
		
		default: type_error=nok; 
		
	}
	return type_error;
	
}


uint8 EXTI_Set_call_back(void(*notification)(void),uint8 NO_of_interrupt)
{
	uint8 local_error = ok;
	if(notification!=NULL)
	{
		EXTI_pvINTCallBackFunc[NO_of_interrupt]=notification;
	}
	
	else
	{
		local_error=nok;
		
	}
	return local_error;
}

ISR(EXTI_INT_0)
{
	if(EXTI_pvINTCallBackFunc[EXTI0]!=NULL)
	{
			EXTI_pvINTCallBackFunc[EXTI0]();
	}
	else
	{
		// do nothing
	}
}

ISR(EXTI_INI_1)
{
	if(EXTI_pvINTCallBackFunc[EXTI1]!=NULL)
	{
		EXTI_pvINTCallBackFunc[EXTI1]();
		
	}
	else
	{
		// do nothing
	}
}

ISR(EXTI_INI_2)
{
	if(EXTI_pvINTCallBackFunc[EXTI2]!=NULL)
	{
		EXTI_pvINTCallBackFunc[EXTI2]();
	}
	else
	{
		// do nothing
	}
}