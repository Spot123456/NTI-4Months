/*
 * Timer.c
 *
 * Created: 9/15/2023 9:56:04 AM
 *  Author: Ahmed Nour
 */ 
#include "../../utilities/math.h"
#include "../../utilities/datatypes.h"
#include "../../utilities/Erorr_Type.h"
#include "Timer_Config.h"
#include "Timer_Interface.h"
#include "Timer_Private.h"

// pointer to fun to set call back overflow
static void (*TIMER0_OV_setcall)(void)=NULL;
// pointer to fun to set call back CTC
static void (*TIMER0_CTC_setcall)(void)=NULL;



void TIMER0_void_setTCNT0(uint8 value_cpy){
	TCNT0_REG = value_cpy;
}

void Timer0_Init()
{
	#if Timer_0_mode == normal_mode
	clr_bit(TCCR0_REG,TCCR0_WGM00);
	clr_bit(TCCR0_REG,TCCR0_WGM01);
	/*set the required preload */
	TCNT0_REG=time_preload_val ;
	/*timer0 overflow interrupt enable*/
	set_bit(TIMSK_REG,TIMSK_TOIE0);
	// select Prescaler
	TCCR0_REG &=  timer0_prescaler_mask;
		#if		Timer_count	== off
		TCCR0_REG|=timer_8prescaler;
		#elif	Timer_count	==	on
		TCCR0_REG|=Timer_EXT_count;
		#endif
	#elif Timer_0_mode == CTC_mode
	clr_bit(TCCR0_REG,TCCR0_WGM00);
	set_bit(TCCR0_REG,TCCR0_WGM01);
	/*set the OCR value*/
	OCR0_REG= OCR0_val;
	
		#if output_mode == CTC_no_out
		clr_bit(TCCR0_REG,TCCR0_COM00);
		clr_bit(TCCR0_REG,TCCR0_COM01);
		#elif	output_mode== CTC_toggle
		set_bit(TCCR0_REG,TCCR0_COM00);
		clr_bit(TCCR0_REG,TCCR0_COM01);
		#elif	output_mode== CTC_clear
		clr_bit(TCCR0_REG,TCCR0_COM00);
		set_bit(TCCR0_REG,TCCR0_COM01);
		#elif	output_mode== CTC_set
		set_bit(TCCR0_REG,TCCR0_COM00);
		set_bit(TCCR0_REG,TCCR0_COM01);
		#endif
	/*timer0 ctc interrupt enable*/
	set_bit(TIMSK_REG,TIMSK_OCIE0);
	// select pre
	TCCR0_REG &=  timer0_prescaler_mask;
	TCCR0_REG|=timer_8prescaler;
	
	#elif	Timer_0_mode== PWM_mode
	set_bit(TCCR0_REG,TCCR0_WGM00);
	set_bit(TCCR0_REG,TCCR0_WGM01);
	/*set on top clear on compare*/
	clr_bit(TCCR0_REG,TCCR0_COM00);
	set_bit(TCCR0_REG,TCCR0_COM01);
	// select pre
	TCCR0_REG &=  timer0_prescaler_mask;
	TCCR0_REG|=timer_8prescaler;
#endif
}

void timer0_start_Preload(uint8 val)
{
	TCNT0_REG=val; //start from (value) to overflow
}

void Timer_stop()
{
	TCCR0_REG =0x00;
}

uint8 Timer0_OV_setcallback(void(*notification)(void))
{
	uint8 local_error = ok;
	if(notification!=NULL)
	{
			
		TIMER0_OV_setcall=notification;
	}
	else
	{
		local_error= nok;
	}
}
uint8 Timer0_CTC_setcallback(void(*notification)(void))
{
		uint8 local_error = ok;
		if(notification!=NULL)
		{
			TIMER0_CTC_setcall=notification;
		}
		else
		{
			local_error= nok;
		}
}

uint8 timer0_getTCNT_val()
{
	return TCNT0_REG;
}

void Timer0_pwm(uint8 Copy_PWM)
{
	OCR0_REG = Copy_PWM;
}

/*over flow ISR back */
/*void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{

	if(TIMER0_OV_setcall!=NULL)
	{
		set_bit(TIFR0_REG,0); // clr flag
		TIMER0_OV_setcall();
		
	}
	else
	{
		// do nothing
	}
}*/

// ISR OV
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	
	if(TIMER0_CTC_setcall!=NULL)
	{
		set_bit(TIFR0_REG,1); // clr flag
		TIMER0_CTC_setcall();
	}
	else
	{
		// do nothing
	}
}



void Timer1_init()
{
	/*compare match output mode : set on top clear on compare (non inverted)*/
	set_bit(TCCR1A_REG,TCCR1A_COM1A1);
	clr_bit(TCCR1A_REG,TCCR1A_COM1A0);
	
	//set_bit(TCCR1A_REG,5);
	//clr_bit(TCCR1A_REG,4);
	
	/*waveForm generation mode: Fast PWM With ICR1 as  top value*/
	clr_bit(TCCR1A_REG,TCCR1A_WGM10);
	set_bit(TCCR1A_REG,TCCR1A_WGM11);
	set_bit(TCCR1B_REG,TCCR1B_WGM12);  // 5ly balk tccr1b
	set_bit(TCCR1B_REG,TCCR1B_WGM13);
	
	/*set top value */
	
	ICR1_REG= 3000;  // time over flow
	
	/* compare match value : range between 750 to 2500*/
		/* compare match value : range between 1000 to 2000*/
	OCR1A_REG=1000;
	
	/*set Prescaler : divide by 8*/
	clr_bit(TCCR1B_REG,TCCR1B_CS12);
	set_bit(TCCR1B_REG,TCCR1B_CS11);
	clr_bit(TCCR1B_REG,TCCR1B_CS10);
}
void Timer1_voidSetChannelACompValue(uint16 copy_u16Value)
{
	OCR1A_REG= copy_u16Value;
}
void Timer1_voidSetChannelBCompValue(uint16 copy_u16Value)
{
	OCR1B_REG= copy_u16Value;
}


void Timer_delay(float msecend)
{
	unsigned int overflow_counter=0;
	//Timer0_init(pre64);
	//	float timer_clk=64*.000001;
	//	float time_overflow=256*timer_clk;
	//	msecend=msecend*.001;
	int num_over_flow=(int)(msecend*61);
	while (overflow_counter<num_over_flow)
	{
		//wait for flag occurs
		while((TIFR0_REG &(1<<0))==0);
		//clear flag
		TIFR0_REG |=(1<<0);
		overflow_counter++;
	}
	overflow_counter=0;
	//set time to 0
	TCCR0_REG=0x00;
}
