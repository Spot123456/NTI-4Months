/*
 * SPI.c
 *
 * Created: 9/22/2023 12:03:06 PM
 *  Author: Ahmed Nour
 */ 

#include "../../utilities/datatypes.h"
#include "../../utilities/math.h"
#include "SPI_Config.h"
#include "SPI_Interface.h"
#include "SPI_Private.h"

static void (* SPI_set_call)(void)=NULL;

void Spi_init()
{
		/*select the spi as master */
		set_bit(SPCR_REG,SPCR_MSTR);
	/*enable interrupt*/
	set_bit(SPCR_REG,SPCR_SPIE);
	/*select the CLK rate : (f/8) */
	set_bit(SPCR_REG,SPCR_SPR0);
	clr_bit(SPCR_REG,SPCR_SPR1);
	set_bit(SPSR_REG,SPSR_SPI2X);
	/*enable SPI*/
	set_bit(SPCR_REG,SPCR_SPE);
}



uint8 spi_TxRx(uint8 data)
{
	SPDR_REG=data;
	while(get_bit(SPSR_REG,SPSR_SPIF)==0);
	return SPDR_REG;
}


uint8 Spi_Transceive_word(uint8 *copy_Data)
{
	uint8 i =0;
	while(copy_Data[i]!='\0')
	{
		
		SPDR_REG= *copy_Data; // if we need received the send data is garbage value
		/*wait until the received complete*/
		while((get_bit(SPSR_REG,SPSR_SPIF)==0)); // the same problem with same solution
		//copy_Data=SPDR_REG;
		return SPDR_REG;
		i++;
	}
	spi_TxRx('#');
	return 0;
	
}


/*uint8 static stack_spi[255]={0};
uint8 static stack_ptr=0;
uint8 spi_stack_push(uint8  data)
{
	
	if(stack_ptr==255)
	{
		return stack_full;
	}
	stack_spi[stack_ptr++]=data;
	return stack_fine;
}
uint8 spi_stack_pop(uint8 * data)
{
	
	if(stack_ptr==0)
	{
		return stack_empty;
	}
	stack_ptr--;
	*data =stack_spi[stack_ptr];
	return stack_fine;
}

void spi_call_back(void(*notification)(void))
{
	if(notification!=NULL)
	{
		SPI_set_call=notification;
	}
}
void __vector_12 (void) __attribute__((signal));
void __vector_12 (void)
{
	if(SPI_set_call!=NULL)
	{
		SPI_set_call();
	}
	
};*/
