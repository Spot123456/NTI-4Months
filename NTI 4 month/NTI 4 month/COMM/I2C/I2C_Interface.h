/*
 * I2C_Interface.h
 *
 * Created: 9/23/2023 10:50:44 AM
 *  Author: yahia
 */ 


#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_
#include "I2C_Private.h"

void TWI_voidInitMaster(uint8 Copy_Address);

void TWI_voidInitSlave(uint8 Copy_address);

TWI_ErrStatus TWI_SendStartCondition();

TWI_ErrStatus TWI_SendRepeatedStart();

TWI_ErrStatus TWI_SendSlaveAddressWithWrite(uint8 copy_Slaveaddress);

TWI_ErrStatus TWI_SendSlaveAddressWithRead(uint8 copy_Slaveaddress);

TWI_ErrStatus TWI_MasterWriteDataByte(uint8 copy_DataByte);

TWI_ErrStatus TWI_MasterReadDataByte(uint8 *copy_DataByte);

void TWI_SendStopCondition(void);

TWI_ErrStatus TWI_SendSlaveAddressWithRead(uint8 copy_Slaveaddress);

void I2C_slave_transmit(uint8 ch);
uint8 I2C_readByteWithNACK(uint8* var);


#endif /* I2C_INTERFACE_H_ */