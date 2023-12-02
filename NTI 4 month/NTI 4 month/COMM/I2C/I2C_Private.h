/*
 * I2C_Private.h
 *
 * Created: 9/23/2023 10:51:10 AM
 *  Author: Ahmed Nour
 */ 


#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

typedef enum
{
	NoError,
	StartconditionERR,
	RepeatedStartError,
	SlaveAddressWithWriteErr,
	SlaveAddresswithReadErr,
	MasterWriteByteErr,
	MasterReadByteErr,
}TWI_ErrStatus;
/************************************************************************/
/*                        TWI REG                                       */
/************************************************************************/
#define TWCR_REG	*((volatile uint8*)0x56) /*TWI Control Register*/

#define TWCR_TWINT	7		/*Interrupt Flag*/
#define TWCR_TWEA	6		/*Enable Acknoledge*/
#define TWCR_TWSTA	5		/*Start Condition*/
#define TWCR_TWSTO	4		/*Stop condition*/
#define TWCR_TWWC	3		/*write collision*/
#define TWCR_TWEN	2		/*enable*/
#define TWCR_TWIE	0		/*interrupt Enable*/

#define TWDR_REG	*((volatile uint8*)0x23)	/*TWI Data Register*/

#define TWAR_REG	*((volatile uint8*)0x22)	/*TWI Address Register*/
#define TWAR_TWGCE	0							/*General Call recognition Enable*/

#define TWSR_REG	*((volatile uint8*)0x21)	/*TWI Status Register*/
#define TWSR_TWPS0	0							/*Prescaler Bit0*/
#define TWSR_TWPS1	1							/*Prescaler Bit1*/

#define TWBR_REG	*((volatile uint8*)0x20)	/*TWI Bit Rate Register*/

/****************************************************************/
/*					error state i2c								*/
/****************************************************************/


#define START_ACK				0x08 /* start has been sent*/
#define REP_START_ACK			0x10 /* repeated start*/
#define Slave_ADD_AND_WR_ACK	0x18 /* master transmit ( slave address + Write request ) Ack */
#define Slave_ADD_AND_RD_ACK	0x40 /* master transmit ( slave address + read request ) Ack */
#define MSTR_WR_BYTE_ACK		0x28 /* master transmit data ACK*/
#define MSTR_RRD_BYTE_WITH_ACK	0x50 /* master receive data with ACK*/
#define MSTR_RRD_BYTE_WITH_NACK	0x58 /* master receive data with not ACK*/
#define SLAVE_ADD_RCVD_RD_REQ	0xA8 /* means that slave address is received with read request*/
#define SLAVE_ADD_RCVE_RW_REQ	0x60 /* means that slave address is received with write request*/
#define SLAVE_DATA_RECEIVED		0x80 /* means that a byte is received*/
#define SLAVE_BYTE_TRANSIMITTED	0xB8 /* means that the written byte is transmitted*/



#define status_Reg_mask	0b11111000 // 0xf8

#endif /* I2C_PRIVATE_H_ */