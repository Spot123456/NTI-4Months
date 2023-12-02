/*
 * datatypes.h
 *
 * Created: 9/4/2023 3:22:58 PM
 *  Author: Ahmed Nour
 */ 


#ifndef DATATYPES_H_
#define DATATYPES_H_

#define NULL	(void*)0
typedef unsigned char		uint8;
typedef unsigned short int	uint16;
typedef unsigned long		uint32;
typedef unsigned  int	uint64;


typedef  char		int8;
typedef short int	int16;
typedef  long		int32;
typedef  int		int64;
typedef	 float		f32;

typedef enum
{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D
	
}EN_Port_ID;

#define PORT_A	0
#define PORT_B	1
#define PORT_C	2
#define PORT_D	3
typedef enum
{
	INPUT,
	OUTPUT
	
}EN_DIO_DIR;
typedef enum
{
	LOW,
	HIGH
	
}EN_DIO_Val;

typedef enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}EN_PIN_ID;


#endif /* DATATYPES_H_ */