/*
 * SPI_Interface.h
 *
 * Created: 9/22/2023 12:03:22 PM
 *  Author: yahia
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void Spi_init();

uint8 spi_TxRx(uint8  data);

uint8 Spi_Transceive_word(uint8 *copy_Data);
uint8 spi_stack_push(uint8  data);
uint8 spi_stack_pop(uint8 * data);
void spi_call_back(void(*notification)(void));
#endif /* SPI_INTERFACE_H_ */