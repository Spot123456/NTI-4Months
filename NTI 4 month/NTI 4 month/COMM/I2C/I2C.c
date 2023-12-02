/*
 * I2C.c
 *
 * Created: 9/23/2023 1:52:37 PM
 *  Author: yahia
 */ 

#include "../../utilities/datatypes.h"
#include "../../utilities/math.h"
#include "I2C_Private.h"
#include "I2C_Interface.h"
#include "I2C_Config.h"
void TWI_voidInitMaster(uint8 Copy_Address)
{
	/*Enable ACKnowledge bit */ 
	set_bit(TWCR_REG,TWCR_TWEA);
	TWSR_REG=0x00;
	/* assume the speed = 400 ,8MHZ freq */
	/* by sub in the equation : the TWBR=2,TWPS=0  */
	/*we made this to generate clk by master*/
	TWBR_REG= 32;  //32 ;//2;
	
	/* Prescaler bits: 2bit in TWPS*/
	clr_bit(TWSR_REG,TWSR_TWPS0);
	clr_bit(TWSR_REG,TWSR_TWPS1);
	
	/*to make any change or make any step we need to clear flag*/
	clr_bit(TWCR_REG,TWCR_TWINT);
	
	/*we need to check if the master has address or not*/
	if(Copy_Address!=0)
	{
		/*Set the Master address*/
		TWAR_REG=Copy_Address<<1;
	}
	else
	{
		//do nothing
	}
	/*Enable TWI*/
	set_bit(TWCR_REG,TWCR_TWEN);
}

void TWI_voidInitSlave(uint8 Copy_address)
{
	/*Set the slave address*/
	TWAR_REG=Copy_address<<1;
	
	/*Enable ACKnowledge bit */
	set_bit(TWCR_REG,TWCR_TWEA);
	
	
	/*Enable TWI*/
	set_bit(TWCR_REG,TWCR_TWEN);
}

TWI_ErrStatus TWI_SendStartCondition()
{
	TWI_ErrStatus Local_Error=NoError;
	
	/*Send start condition*/
	set_bit(TWCR_REG,TWCR_TWSTA);
	
	/*to make any change or make any step we need to clear flag*/
	/*Clear the interrupt flag to start the previous operation*/
	set_bit(TWCR_REG,TWCR_TWINT);
	
	/*wait until the operation finishes and the flag is raised*/
	while((get_bit(TWCR_REG,TWCR_TWINT))==0);
	
	/*Check the operation status*/
	// we need to clear the last 3 bit (3 LSB bits) so we use 0xF8
	if((TWSR_REG & 0xF8)!=START_ACK)
	{
		Local_Error=StartconditionERR;
// 		LCD_ChangePOS_XY(5,1);
// 		LCD_voidWriteNumber(5);
	}
	else
	{
		//do nothing
	}
	
	return Local_Error;

}

TWI_ErrStatus TWI_SendRepeatedStart()
{
	TWI_ErrStatus Local_Error = NoError;
	
	/* enable start condition*/
	set_bit(TWCR_REG,TWCR_TWSTA);
	
	/*clear the interrupt flag*/
	set_bit(TWCR_REG,TWCR_TWINT);
	
	while((get_bit(TWCR_REG,TWCR_TWINT))==0);
	
	/*Check the operation status*/
	// we need to clear the last 3 bit (3 LSB bits) so we use 0xF8
	if((TWSR_REG & 0xF8)!= REP_START_ACK)
	{
		Local_Error=RepeatedStartError;
	}
	else
	{
		// do nothing
	}
	return Local_Error;
}

TWI_ErrStatus TWI_SendSlaveAddressWithWrite(uint8 copy_Slaveaddress)
{
	TWI_ErrStatus Local_Error=NoError;
	
	/*set the address slave */
	TWDR_REG=copy_Slaveaddress<<1;
	
	/* Enable the write bit*/
	clr_bit(TWDR_REG,0);
	
	/*we must clear start condition by software after send the start condition */
	clr_bit(TWCR_REG,TWCR_TWSTA);
	
	/*clear the interrupt flag*/
	set_bit(TWCR_REG,TWCR_TWINT);
	
	/*wait until the flag rising up*/
	while((get_bit(TWCR_REG,TWCR_TWINT))==0);
	
	/* check the condition */
	if((TWSR_REG & 0xF8)!=Slave_ADD_AND_WR_ACK)
	{
		Local_Error=SlaveAddressWithWriteErr;
// 		LCD_ChangePOS_XY(4,1);
// 		LCD_voidWriteNumber(4);
	}
	else
	{
		//do nothing 
	}
	return Local_Error;
}

TWI_ErrStatus TWI_SendSlaveAddressWithRead(uint8 copy_Slaveaddress)
{
	TWI_ErrStatus Local_Error=NoError;
	
		
	TWDR_REG=0x00;
	/*send the 7bit slave address to the bus*/
	TWDR_REG=copy_Slaveaddress<<1;

	/*set the read request in the LSB in the data register*/
	set_bit(TWDR_REG,0);
	
	/*we must clear start condition by software after send the start condition */
	//clr_bit(TWCR_REG,TWCR_TWSTA);
	
	/*to make any change or make any step we need to clear flag*/
	set_bit(TWCR_REG,TWCR_TWINT);
	
	/*wait until the operation finishes and the flag is raised*/
	while((get_bit(TWCR_REG,TWCR_TWINT))==0);
	
	if((TWSR_REG & 0xF8)!=Slave_ADD_AND_RD_ACK)
	{
		Local_Error= SlaveAddresswithReadErr;
// 		LCD_ChangePOS_XY(3,1);
// 		LCD_voidWriteNumber(3);

	}
	else
	{
		//do nothing
	}
	return Local_Error;
}

TWI_ErrStatus TWI_MasterWriteDataByte(uint8 copy_DataByte)
{
	TWI_ErrStatus Local_Error = NoError;
	
	/*send the data to the bus */ 
	TWDR_REG = copy_DataByte ;
	
	/* clear the interrupt flag*/
	set_bit(TWCR_REG,TWCR_TWINT);
	
	/*wait until the operation finishes and the flag is raised*/
	while((get_bit(TWCR_REG,TWCR_TWINT))==0);

	/*Check the operation status*/
	if((TWSR_REG & 0xF8) !=MSTR_WR_BYTE_ACK  )
	{
		Local_Error = MasterWriteByteErr ;
// 		LCD_ChangePOS_XY(0,1);
// 		LCD_voidWriteNumber(1);
	}
	else
	{
		/*Do nothing*/
	}
	return Local_Error;
}

TWI_ErrStatus TWI_MasterReadDataByte(uint8 *copy_DataByte)
{
	TWI_ErrStatus Local_Error = NoError;
	
	/*we need to imagine the send scenario the master send start 
	 * then address with read and ack then the flag will rise so 
	 * to the address send the data we need to clear the flag first 
	 * to get the CLK work again and the slave can send the data */
	set_bit(TWCR_REG,TWCR_TWINT);
	set_bit(TWCR_REG,TWCR_TWEN); //
	set_bit(TWCR_REG,TWCR_TWEA); //
	/*wait until the operation finishes and the flag is raised*/
	while((get_bit(TWCR_REG,TWCR_TWINT))==0);
	
	/*Check the operation status*/
// 	if((TWSR_REG & 0xF8)!=MSTR_RRD_BYTE_WITH_ACK)
// 		{
// 			Local_Error=MasterReadByteErr;
// 			LCD_ChangePOS_XY(1,1);
// 			LCD_voidWriteNumber(2);
// 		}
// 		else
// 		{
// 			*copy_DataByte = TWDR_REG;
// 		}

	*copy_DataByte = TWDR_REG;
	return Local_Error;
}

void TWI_SendStopCondition(void)
{
	
	/*Enable the stop condition*/
	set_bit(TWCR_REG,TWCR_TWSTO);
	
	/*Clear the interrupt flag to start the previous operation*/
	set_bit(TWCR_REG,TWCR_TWINT);
	//while(TWCR_REG&(1<<TWCR_TWINT));

}


uint8 I2C_readByteWithNACK(uint8* var)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR_REG = (1 << TWCR_TWINT) | (1 <<TWCR_TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(get_bit(TWCR_REG,TWCR_TWINT));
    /* Read Data */
	*var = TWDR_REG;
    return var;
}

void I2C_slave_transmit(uint8 ch){
	TWDR_REG=ch;
	TWCR_REG|=(1<<TWCR_TWEN)|(1<<TWCR_TWINT);
	while(get_bit(TWCR_REG,TWCR_TWINT)==0);
}