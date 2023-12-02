/*
 * UART.c
 *
 * Created: 3/21/2023 3:27:53 PM
 *  Author: Ahmed Nour
 */ 

#include "../../utilities/datatypes.h"
#include "../../utilities/math.h"
#include "UART_Interface.h"
#include "UART_Private.h"
#include "UART_Config.h"


void UART_init()
{
	/*local variable to hold the required value of UCSRC register */
	uint8 local_UCSRCVsl= 0;
	/*choose the UCSRC REG */ 
	set_bit(local_UCSRCVsl,UCSRC_URSEL);
	/*ASY- no party - 1 stop */
	
	#if		party_mode	==	no_party
	clr_bit(local_UCSRCVsl,UCSRC_UPM1);
	clr_bit(local_UCSRCVsl,UCSRC_UPM0);
	#elif	party_mode	==	even_party
	set_bit(local_UCSRCVsl,UCSRC_UPM1);
	clr_bit(local_UCSRCVsl,UCSRC_UPM0);
	#elif	party_mode	==	odd_party
	set_bit(local_UCSRCVsl,UCSRC_UPM1);
	set_bit(local_UCSRCVsl,UCSRC_UPM0);
#endif

	#if		STOP_bit_mode	==	one_bit_stop
	clr_bit(local_UCSRCVsl,UCSRC_USBS);
	#elif	STOP_bit_mode	==	two_bit_stop
	set_bit(local_UCSRCVsl,UCSRC_USBS);
	
#endif

	#if		SYN_mode	==	UART_ASYN
	clr_bit(local_UCSRCVsl,UCSRC_UMSEL);	
	#elif	SYN_mode	==	UART_SYN
	set_bit(local_UCSRCVsl,UCSRC_UMSEL);
	
#endif
	
	/*choose the character size : 8 bit size*/
	set_bit(local_UCSRCVsl,UCSRC_UCSZ0);
	set_bit(local_UCSRCVsl,UCSRC_UCSZ1);
	clr_bit(UCSRB_REG,UCSRB_UCSZ2);
	
	/*we need to set boud rate: for sys 8 MHz & boud rate 9600 we set boud =51 */
	//UBRRL_REG = 51;
	/*we need to set boud rate: for sys 16 MHz & boud rate 9600 we set boud =103 */
	UBRRL_REG = 103;
	// this the equation for cal the boudrate register --> (fosc / 16 Boud)-1 
	// the two reg in diff location so make var , save the value , mack casting for first  , and shift for sec 
	// note draw the frame if u didn't understand ( 0-->7 , 8 --> 15 ).
/*	uint16 val=0;
	val= (f_os_UART/(16*boudrate))-1;
	UBRRL_REG=(uint8)val;
	UBRRH_REG=(val>>8);*/
	
	/*enable TX*/
	set_bit(UCSRB_REG,UCSRB_TXEN);
	/*enable RX*/
	set_bit(UCSRB_REG,UCSRB_RXEN);
}

void UART_SendData(uint8 data)
{
	while((get_bit(UCSRA_REG,UCSRA_UDRE)==0));
	/*send the data*/
	UDR_REG= data;  //buffer
}

uint8 UART_ReceivedData()
{
	/*wait until receive complete event happens*/
	while((get_bit(UCSRA_REG,UCSRA_RXC))==0);
	
	/*return the data*/
	return UDR_REG; //buffer
}
// uint8	UART_Receivedstring(uint8 * arr)
// {
// 	uint8 res= 0 ;
// 	while(arr!='\0')
// 	{
// 		res=UART_ReceivedData();
// 		return res;
// 	}
// 	return 0;
// 	
// 	
// }
uint8 UART_Receivedstring(uint8 * arr)
{
	if (arr == NULL || arr[0] == '\0') {
		return 0;
	}

	uint8 res = 0;
	while (arr != '\0') {
		res = UART_ReceivedData();
		arr++;
	}

	return res;
}

void UART_voidSendStringBlocking(char *Copy_u8Data){

	while(*Copy_u8Data != NULL){

		UART_SendData(*Copy_u8Data);
		*Copy_u8Data++;
	}
}



void UART_voidWriteDecimalNumber(uint32 Copy_u32Number){

	uint32 Local_u8Reversed = 1;

	if(0 == Copy_u32Number){
		UART_SendData('0');
	}
	while(0 != Copy_u32Number){

		Local_u8Reversed = ((Local_u8Reversed * 10) + (Copy_u32Number % 10));
		Copy_u32Number /= 10;
	}
	while(1 != Local_u8Reversed){

		UART_SendData((Local_u8Reversed % 10 ) + 48);
		Local_u8Reversed /= 10;
	}

}