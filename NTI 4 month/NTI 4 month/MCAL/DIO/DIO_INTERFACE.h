/*
 * DIO_INTERFACE.h
 *
 * Created: 9/9/2023 10:18:31 AM
 *  Author: yahia
 */ 

#include "../../utilities/datatypes.h"
#include "DIO_PRIVATE.h"
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_



uint8	DIO_set_port_dir(EN_Port_ID PORT_ID,EN_DIO_DIR DIR); // use to set port direction
uint8	DIO_set_port_val(EN_Port_ID PORT_ID,EN_DIO_Val VAL);	// use to set port val
uint8	DIO_set_pin_dir(EN_Port_ID PORT_ID,EN_PIN_ID PIN_ID,EN_DIO_DIR DIR) ; //use to set pin direction 
uint8	DIO_set_pin_val(EN_Port_ID PORT_ID,EN_PIN_ID PIN_ID,EN_DIO_Val VAL) ; //use to set pin value
uint8	DIO_get_pin_val(EN_Port_ID PORT_ID,EN_PIN_ID PIN_ID,uint8 * val) ; //use to get pin value

uint8 DIO_set_port_char(EN_Port_ID PORT_ID,uint8 data); // use for send data to port as it is



#endif /* DIO_INTERFACE_H_ */