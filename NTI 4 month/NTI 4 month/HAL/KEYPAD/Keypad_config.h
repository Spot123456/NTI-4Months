/*
 * Keypad_config.h
 *
 * Created: 9/10/2023 9:08:00 AM
 *  Author: Ahmed Nour
 */ 


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_
#include "../../utilities/datatypes.h"
#define rows	4
#define cols	4
# define KEY_PORT_D  3
#define keypad_port	  PORT_D

/************************************/
/*			new method				*/
/************************************/

#define keypad_port_row	  PORT_B
#define keypad_port_col	  PORT_C
// define for rows
#define r0	PIN5
#define r1	PIN4
#define r2	PIN3
#define r3	PIN2
// define for cols
#define c0	PIN7
#define c1	PIN6
#define c2	PIN5
#define c3	PIN3

uint8 arr_rows[]={r0,r1,r2,r3};
uint8 arr_cols[]={c0,c1,c2,c3};




#endif /* KEYPAD_CONFIG_H_ */