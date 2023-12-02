/*
 * RTC.c
 *
 * Created: 9/26/2023 12:19:34 AM
 *  Author: Ahmed Nour
 */ 

#include "../../utilities/datatypes.h"
#include "../../utilities/math.h"
#include "../../COMM/I2C/I2C_Interface.h"
#include "RTC_Config.h"
#include "RTC_Private.h"
#include "RTC_Interface.h"
#include <util/delay.h>
void RTC_init()
{
	
	TWI_SendStartCondition();
	TWI_SendSlaveAddressWithWrite(RTC_Address);
	TWI_MasterWriteDataByte(0x07);
	TWI_SendSlaveAddressWithRead(0x00);
	TWI_SendStopCondition();
}

void RTC_write(date*x)
{
	//TWI_voidInitMaster(0);
	//enable start condition
	TWI_SendStartCondition();
	// send address of Rtc with write
	TWI_SendSlaveAddressWithWrite(RTC_Address);
	// this is first add location for Rtc (Note that the address inc  automatically)
	TWI_SendSlaveAddressWithWrite(0x00); 
	// send data (sec , minuet , hour) 
	TWI_MasterWriteDataByte(x->sec);
	TWI_MasterWriteDataByte(x->min);
	TWI_MasterWriteDataByte(x->hour);
	TWI_SendStopCondition();
}


void RTC_read(date*x)
{
		 uint8 s;
	//TWI_voidInitMaster(0);
	TWI_SendStartCondition();
	TWI_SendSlaveAddressWithWrite(RTC_Address);
	
	TWI_MasterWriteDataByte(0x00); // Set the address register to 0x00
	TWI_SendRepeatedStart();
	TWI_SendSlaveAddressWithRead(RTC_Address);
	TWI_MasterReadDataByte(&x->sec);
	TWI_MasterReadDataByte(&x->min);
	//TWI_MasterReadDataByte(x->hour);
	 I2C_readByteWithNACK(&x->hour);

	 I2C_readByteWithNACK(s);
	_delay_ms(1);
	TWI_SendStopCondition();
	
	//TWI_SendStopCondition();
}

void RTC_read1(uint8*x,uint8*y,uint8*z)
{
	uint8 s;
	//TWI_voidInitMaster(0);
	TWI_SendStartCondition();
	TWI_SendSlaveAddressWithWrite(RTC_Address);
	
	TWI_MasterWriteDataByte(0x00); // Set the address register to 0x00
	TWI_SendRepeatedStart();
	TWI_SendSlaveAddressWithRead(RTC_Address);
	TWI_MasterReadDataByte(x);

	TWI_MasterReadDataByte(y);
	
	TWI_MasterReadDataByte(z);
	I2C_readByteWithNACK(s);
	_delay_ms(1);
	TWI_SendStopCondition();
	
	//TWI_SendStopCondition();
}


/*
date RTC_read(date*x)
{
	TWI_voidInitMaster(0);
	TWI_SendStartCondition();
	TWI_SendSlaveAddressWithWrite(RTC_Address);
	TWI_SendRepeatedStart();
	TWI_SendSlaveAddressWithRead(0x00);
	TWI_MasterReadDataByte(x->sec);
	TWI_MasterReadDataByte(x->min);
	TWI_MasterReadDataByte(x->hour);
	TWI_SendStopCondition();
}*/
