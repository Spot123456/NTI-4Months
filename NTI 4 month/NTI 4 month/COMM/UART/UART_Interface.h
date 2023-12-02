/*
 * UART_Interface.h
 *
 * Created: 9/18/2023 11:18:54 AM
 *  Author: Ahmed Nour
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_init();
void UART_SendData(uint8 data);
uint8 UART_ReceivedData();
uint8	UART_Receivedstring(uint8 * arr);
void UART_voidSendStringBlocking(char *Copy_u8Data);
void UART_voidWriteDecimalNumber(uint32 Copy_u32Number);

#endif /* UART_INTERFACE_H_ */