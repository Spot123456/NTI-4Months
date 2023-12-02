/*
 * Keypad.c
 *
 * Created: 9/9/2023 11:03:42 PM
 *  Author: Ahmed Nour
 */ 
#include "../../utilities/datatypes.h"
#include "../../utilities/math.h"
#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "Keypad_privaite.h"
#include "Keypad_config.h"
#include "Keypad_Interface.h"

void keypad_init()
{
	#if keypad_port==PORT_A
	
	//row as output
	DDRA_Reg|=(1<<0) | (1<<1)|(1<<2)|(1<<3);
	//set the col input
	DDRA_Reg&=~((1<<4) | (1<<5) | (1 << 6) | (1<<7));
	//set col init high : pull up res
	PORTA_Reg|=((1<<4) | (1<<5) | (1 << 6) | (1<<7));
	
	#elif	keypad_port ==PORT_B
	
	//row as output
	DDRB_Reg|=(1<<0) | (1<<1)|(1<<2)|(1<<3);
	//set the col input
	DDRB_Reg&=~((1<<4) | (1<<5) | (1 << 6) | (1<<7));
	//set col init high : pull up res
	PORTB_Reg|=((1<<4) | (1<<5) | (1 << 6) | (1<<7));
	
	#elif	keypad_port ==PORT_C
	
	//row as output
	DDRC_Reg|=(1<<0) | (1<<1)|(1<<2)|(1<<3);
	//set the col input
	DDRC_Reg&=~((1<<4) | (1<<5) | (1 << 6) | (1<<7));
	//set col init high : pull up res
	PORTC_Reg|=((1<<4) | (1<<5) | (1 << 6) | (1<<7));
	
	#elif	keypad_port == PORT_D
	
	//row as output
	DDRD_Reg|=(1<<0) | (1<<1)|(1<<2)|(1<<3);
	//set the col input
	DDRD_Reg&=~((1<<4) | (1<<5) | (1 << 6) | (1<<7));
	//set col init high : pull up res
	PORTD_Reg|=((1<<4) | (1<<5) | (1 << 6) | (1<<7));
	
	#endif
}

uint8 keypad_getval()
{
	uint8 i,j;
	for(i=0 ; i< rows ; i++)
	{
		#if keypad_port== PORT_A
		//activate the row
		PORTA_Reg&=~(1<<i);
		for(j=0;j<cols;j++)
		{
			if((PINA_Reg&(1<<colpins[j]))==0)
			{
				while((PINA_Reg&(1<<colpins[j]))==0);
				return keypad_map[i][j];
				
			}
		}
		//deactivate the current row
		PORTA_Reg|=(1<<i);
	}

		#elif keypad_port==PORT_B
		//activate the row
		PORTB_Reg&=~(1<<i);
		for(j=0;j<cols;j++)
		{
			if((PIND_Reg&(1<<colpins[j]))==0)
			{
				while((PIND_Reg&(1<<colpins[j]))==0);
				return keypad_map[i][j];
				
			}
		}
		//deactivate the current row
		PORTD_Reg|=(1<<i);
	}
	
		#elif keypad_port== PORT_C
		
		//activate the row
		PORTC_Reg&=~(1<<i);
		for(j=0;j<cols;j++)
		{
			if((PIND_Reg&(1<<colpins[j]))==0)
			{
				while((PIND_Reg&(1<<colpins[j]))==0);
				return keypad_map[i][j];
				
			}
		}
		//deactivate the current row
		PORTD_Reg|=(1<<i);
	}

		#elif keypad_port== PORT_D
		//activate the row
		PORTD_Reg&=~(1<<i);
		for(j=0;j<cols;j++)
		{
			if((PIND_Reg&(1<<colpins[j]))==0)
			{
				while((PIND_Reg&(1<<colpins[j]))==0);
				return keypad_map[i][j];
				
			}
		}
		//deactivate the current row
		PORTD_Reg|=(1<<i);
	}
	
		#endif
		return 99;
}

/*******************************************************************/
// new method

void keypad_init2()
{
	// set row out
	DIO_set_pin_dir(keypad_port_row,r0,OUTPUT);
	DIO_set_pin_dir(keypad_port_row,r1,OUTPUT);
	DIO_set_pin_dir(keypad_port_row,r2,OUTPUT);
	DIO_set_pin_dir(keypad_port_row,r3,OUTPUT);
	
	// set col input
	DIO_set_pin_dir(keypad_port_col,c0,OUTPUT);
	DIO_set_pin_dir(keypad_port_col,c1,OUTPUT);
	DIO_set_pin_dir(keypad_port_col,c2,OUTPUT);
	DIO_set_pin_dir(keypad_port_col,c3,OUTPUT);
	
	// enable pullup in cols
	DIO_set_pin_val(keypad_port_col,c0,HIGH);
	DIO_set_pin_val(keypad_port_col,c1,HIGH);
	DIO_set_pin_val(keypad_port_col,c2,HIGH);
	DIO_set_pin_val(keypad_port_col,c3,HIGH);
}

uint8 keypad_scan()
{
	uint8 i , j,val=99 ;
	//local_rows[]={r0,r1,r2,r3};
	//local_cols[]={c0,c1,c2,c3};
	for(i=0;i<rows;i++)
	{
		DIO_set_pin_val(keypad_port_col,arr_cols[i],LOW);
		for(j=0;j<cols;j++)
		{
			DIO_get_pin_val(keypad_port_row,arr_rows[i],&val);
			if(val!=99)
			{
				
				return val;
			}
		}
		DIO_get_pin_val(keypad_port_row,rows+i,&val);
	}
	return val;
}