/*
 * DIO.c
 *
 * Created: 9/9/2023 10:20:18 AM
 *  Author: Ahmed Nour
 */ 
#include "../../utilities/datatypes.h"
#include "../../utilities/math.h"
#include "../../utilities/Erorr_Type.h"
#include "DIO_PRIVATE.h"
#include "DIO_CONFIG.h"
#include "DIO_INTERFACE.h"

uint8 DIO_set_port_dir(EN_Port_ID PORT_ID,EN_DIO_DIR DIR)
{
	uint8 error = ok;
	if(PORT_ID>PORT_D)
	{
		error= nok;
	}
	else
	{
		if(DIR==OUTPUT)
		{
			switch(PORT_ID)
			{
				case PORT_A: DDRA_Reg=0xff; break;
				case PORT_B: DDRB_Reg=0xff; break;
				case PORT_C: DDRC_Reg=0xff; break;
				case PORT_D: DDRD_Reg=0xff; break;
			}
		}
		else if (DIR==INPUT)
		{
			switch(PORT_ID)
			{
				case PORT_A: DDRA_Reg=0x00; break;
				case PORT_B: DDRB_Reg=0x00; break;
				case PORT_C: DDRC_Reg=0x00; break;
				case PORT_D: DDRD_Reg=0x00; break;
			}
		}
		
	}
	return error;
}

uint8 DIO_set_port_char(EN_Port_ID PORT_ID,uint8 data)
{
	uint8 error = ok;
	if(PORT_ID>PORT_D)
	{
		error= nok;
	}
	else
	{
		
			switch(PORT_ID)
			{
				case PORT_A: PORTA_Reg=data; break;
				case PORT_B: PORTB_Reg=data; break;
				case PORT_C: PORTC_Reg=data; break;
				case PORT_D: PORTD_Reg=data; break;
			}
	}

	return error;
	
}

uint8 DIO_set_port_val(EN_Port_ID PORT_ID,EN_DIO_Val VAL)
{
	uint8 error = ok;
	if(PORT_ID>PORT_D)
	{
		error= nok;
	}
	else
	{
		if(VAL==HIGH)
		{
			switch(PORT_ID)
			{
				case PORT_A: PORTA_Reg=0xff; break;
				case PORT_B: PORTB_Reg=0xff; break;
				case PORT_C: PORTC_Reg=0xff; break;
				case PORT_D: PORTD_Reg=0xff; break;
			}
		}
		else if (VAL==LOW)
		{
			switch(PORT_ID)
			{
				case PORT_A: PORTA_Reg=0x00; break;
				case PORT_B: PORTB_Reg=0x00; break;
				case PORT_C: PORTC_Reg=0x00; break;
				case PORT_D: PORTD_Reg=0x00; break;
			}
		}
		
	}
	return error;
}

uint8 DIO_set_pin_dir(EN_Port_ID PORT_ID,EN_PIN_ID PIN_ID,EN_DIO_DIR DIR) 
{
	uint8 error = ok;
	if(PORT_ID<=PORT_D && PIN_ID<=PIN7)
	{
		if(DIR==OUTPUT)
		{
			switch(PORT_ID)
			{
				case PORT_A: set_bit(DDRA_Reg,PIN_ID); break;
				case PORT_B: set_bit(DDRB_Reg,PIN_ID); break;
				case PORT_C: set_bit(DDRC_Reg,PIN_ID); break;
				case PORT_D: set_bit(DDRD_Reg,PIN_ID); break;
			}
		}
		else if (DIR == INPUT)
		{
			switch(PORT_ID)
			{
				case PORT_A: clr_bit(DDRA_Reg,PIN_ID); break;
				case PORT_B: clr_bit(DDRB_Reg,PIN_ID); break;
				case PORT_C: clr_bit(DDRC_Reg,PIN_ID); break;
				case PORT_D: clr_bit(DDRD_Reg,PIN_ID); break;
			}
		}
	}
	else
	{
		error = nok;
	}
	return error;
}
uint8	DIO_set_pin_val(EN_Port_ID PORT_ID,EN_PIN_ID PIN_ID,EN_DIO_Val VAL) 
{
		uint8 error = ok;
		if(PORT_ID<=PORT_D && PIN_ID<=PIN7)
		{
			if(VAL==HIGH)
			{
				switch(PORT_ID)
				{
					case PORT_A: set_bit(PORTA_Reg,PIN_ID); break;
					case PORT_B: set_bit(PORTB_Reg,PIN_ID); break;
					case PORT_C: set_bit(PORTC_Reg,PIN_ID); break;
					case PORT_D: set_bit(PORTD_Reg,PIN_ID); break;
				}
			}
			else if (VAL == LOW)
			{
				switch(PORT_ID)
				{
					case PORT_A: clr_bit(PORTA_Reg,PIN_ID); break;
					case PORT_B: clr_bit(PORTB_Reg,PIN_ID); break;
					case PORT_C: clr_bit(PORTC_Reg,PIN_ID); break;
					case PORT_D: clr_bit(PORTD_Reg,PIN_ID); break;
					
				}
			}
		}
		else
		{
			error = nok;
		}
		return error;
} 
uint8	DIO_get_pin_val(EN_Port_ID PORT_ID,EN_PIN_ID PIN_ID,uint8 * val) 
{
		uint8 error = ok;
		if(PORT_ID<=PORT_D && PIN_ID<=PIN7)
		{
			
			switch(PORT_ID)
			{
				case PORT_A: *val=get_bit(PINA_Reg,PIN_ID); break;
				case PORT_B: *val=get_bit(PINB_Reg,PIN_ID); break;
				case PORT_C: *val=get_bit(PINC_Reg,PIN_ID); break;
				case PORT_D: *val=get_bit(PIND_Reg,PIN_ID); break;
			}
			
			
		}
		else
		{
			error = nok;
		}
		return error;
}