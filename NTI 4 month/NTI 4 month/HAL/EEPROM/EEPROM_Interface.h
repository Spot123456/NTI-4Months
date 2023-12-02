/*
 * EEPROM_Interface.h
 *
 * Created: 9/24/2023 1:06:16 PM
 *  Author: Ahmed Nour
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_Write(uint16 location_Address,uint8 Copy_Data);
uint8 EEPROM_Read(uint16 location_Address);


#endif /* EEPROM_INTERFACE_H_ */