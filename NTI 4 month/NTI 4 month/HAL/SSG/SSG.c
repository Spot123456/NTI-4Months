/*
 * SSG.c
 *
 * Created: 9/10/2023 10:18:27 AM
 *  Author: Ahmed Nour
 */ 

#include "../../utilities/datatypes.h"
#include "../../utilities/math.h"
#include "SSG_Config.h"
#include "SSG_Interface.h"
#include "SSG_Private.h"
#include "../../MCAL/DIO/DIO_INTERFACE.h"
void SSG_init()
{
	DIO_set_pin_dir(SSG_Port,SSG_Pin0,OUTPUT);
	DIO_set_pin_dir(SSG_Port,SSG_Pin1,OUTPUT);
	DIO_set_pin_dir(SSG_Port,SSG_Pin2,OUTPUT);
	DIO_set_pin_dir(SSG_Port,SSG_Pin3,OUTPUT);
	
	// enable first one
	DIO_set_pin_dir(SSG_Port,SSG_EN1,OUTPUT);
	
}
void SSG_enable(uint8 number)
{
	switch(number)
	{
		// enable first SSG
		case 1: DIO_set_pin_dir(SSG_Port,SSG_EN1,OUTPUT); break;
		// enable second SSG
		case 2: DIO_set_pin_dir(SSG_Port,SSG_EN2,OUTPUT); break;
		// enable third SSG
		case 3: DIO_set_pin_dir(SSG_Port,SSG_EN3,OUTPUT); break;
		// enable forth SSG
		case 4: DIO_set_pin_dir(SSG_Port,SSG_EN4,OUTPUT); break;
	}
	
	
}

void SSG_Display(uint8 number)
{
	//3 ---> 0000 0011
	//			  dcba
	if(number<10)
	{

	DIO_set_pin_val(SSG_Port,SSG_Pin0,get_bit(number,0)); // a
	DIO_set_pin_val(SSG_Port,SSG_Pin1,get_bit(number,1)); // b
	DIO_set_pin_val(SSG_Port,SSG_Pin2,get_bit(number,2)); // c
	DIO_set_pin_val(SSG_Port,SSG_Pin3,get_bit(number,3)); // d
	
	}
}