/*
 * LCD_CONFIG.h
 *
 * Created: 2/22/2023 2:25:14 AM
 *  Author: Ahmed Nour
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#include "../../utilities/datatypes.h"

#define LCD_CTRL_PORT      PORT_A
#define LCD_DATA_PORT      PORT_B


#define LCD_E_PIN          PIN2
#define LCD_RW_PIN		   PIN1
#define LCD_RS_PIN		   PIN3

#define	Mode_8bit		0
#define Mode_4bit		1

#define PIN_Data0		PIN0
#define PIN_Data1		PIN1
#define PIN_Data2		PIN2
#define PIN_Data3		PIN4


#define LCD_Mode		Mode_4bit


// 4bit
#define  ENTRY_MODE               0x06
#define  FUNCTION_SET_8BIT		  0x38
#define  DISPLAY_ON_OFF           0x0E
#define  CURSOR_OFF               0x0C
#define  CURSOR_ON                0x0E

#define FUNCTION_SET_8BIT_2LINES_5X7_DOTS  0x38
#define FUNCTION_SET_4BIT_2LINES_5X7_DOTS  0x28

#define DISPLAY_ON_CURSOR_ON_BLink_OFF     0x0E
#define DISPLAY_ON_CURSOR_OFF              0x0C

#define DISPLAY_CLEAR                      0x01
#define ENTRY_MODE_SET                     0x06
#define  RETURN_HOME                       0x02


#endif /* LCD_CONFIG_H_ */