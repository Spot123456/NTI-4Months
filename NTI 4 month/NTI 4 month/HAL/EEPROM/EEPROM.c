/*
 * EEPROM.c
 *
 * Created: 9/24/2023 1:04:59 PM
 *  Author: Ahmed Nour
 */ 

#include "../../utilities/datatypes.h"
#include "../../utilities/math.h"
#include "../../COMM/I2C/I2C_Interface.h"
#include "EEPROM_Config.h"
#include "EEPROM_Private.h"
#include "EEPROM_Interface.h"
#include <util\delay.h>
void EEPROM_Write(uint16 location_Address,uint8 Copy_Data)
{
	// data is 10 bit bec EEPROM 8 K
	// 1010 000 --> 1010 A2 B10 B9
	uint8 location_Address_Packet=EEPROM_FIXED_ADDRESS | (A2_Connection<<2) |(uint8)(location_Address>>8); // from location add we need the first 3 bit for add location
	//send start condition
	TWI_SendStartCondition();
	//send the addressPacket
	TWI_SendSlaveAddressWithWrite(location_Address_Packet);
	// send the rest 8bit of the location address
	TWI_MasterWriteDataByte((uint8)location_Address);
	// send the data
	TWI_MasterWriteDataByte(Copy_Data);
	//stop the condition of TWI
	TWI_SendStopCondition();
	//delay for 10 ms to write in the memory
	_delay_ms(10);
}


uint8 EEPROM_Read(uint16 location_Address)
{
	uint8 static data ;
	uint8 local_AddressPacket=EEPROM_FIXED_ADDRESS | (A2_Connection<<2) |(uint8)(location_Address>>8);
	TWI_SendStartCondition();
	// 7 bit slave with write to can be able to send the rest 8 bit of location address
	TWI_SendSlaveAddressWithWrite(local_AddressPacket);
	// send the rest of 8 bits
	TWI_MasterWriteDataByte((uint8)location_Address);
	// send repeated start
	TWI_SendRepeatedStart();
	// send slave add with read
	TWI_SendSlaveAddressWithRead(local_AddressPacket);
	// read the send data
	TWI_MasterReadDataByte(&data);
	//send stop condition
	TWI_SendStopCondition();
	
	
	return data;

}
