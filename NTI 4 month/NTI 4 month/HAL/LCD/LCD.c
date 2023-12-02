/*
 * LCD.c
 *
 * Created: 9/10/2023 2:40:11 PM
 *  Author: Ahmed nour
 */ 
/*
 * lcd.c
 *
 * Created: 2/22/2023 2:24:03 AM
 *  Author: Ahmed Nour
 */ 
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"
#include "LCD_CONFIG.h"
#include "../../utilities/math.h"
//#include "../../MCAL/TIMER/timer.h"
#define F_CPU	8000000

void LCD_Send_Command(uint8 command)
{
	#if LCD_Mode==Mode_8bit
	
	/*1- Set RS to LOW : for command */
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_RS_PIN,LOW);
	
	/*2- Set RW to LOW : for Write */
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_RW_PIN,LOW);
	
	/*3- Send command */
	DIO_set_port_char(LCD_DATA_PORT,command);
	
	/*4- send the enable pulse :enable pin high */
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_E_PIN,HIGH);
	_delay_ms(2);//Timer_delay(2); // delay 2 ms
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_E_PIN,LOW);
	
	#elif LCD_Mode==Mode_4bit
	
	/*1- Set RS to LOW : for command */
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_RS_PIN,LOW);
	
	/*2- Set RW to LOW : for Write */
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_RW_PIN,LOW);
	
	/*3- Send command */
	
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data0,get_bit(command,4));
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data1,get_bit(command,5));
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data2,get_bit(command,6));
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data3,get_bit(command,7));
	
	/*4- send the enable pulse :enable pin high */
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_E_PIN,HIGH);
	_delay_ms(2);//Timer_delay(2); // delay 2 ms
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_E_PIN,LOW);
	_delay_ms(1);
	
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data0,get_bit(command,0));
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data1,get_bit(command,1));	
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data2,get_bit(command,2));
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data3,get_bit(command,3));
	
	//4- send the enable pulse :enable pin high 
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_E_PIN,HIGH);
	_delay_ms(2);//Timer_delay(2); // delay 2 ms
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_E_PIN,LOW);
	_delay_ms(1);
	#endif
	
	
}
void LCD_Send_Data(uint8 Data)
{
	#if LCD_Mode == Mode_8bit
	/*1- Set RS to high */ 
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_RS_PIN,HIGH);
	
	/*2- set RW to LOW : Write*/
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_RW_PIN,LOW);
	
	/*3- send data*/
	DIO_set_port_char(LCD_DATA_PORT,Data);
	
	/*4- Send enable Pulse */ 
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_E_PIN,HIGH);
	_delay_ms(2);//Timer_delay(2); // 2 ms
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_E_PIN,LOW);
	
	#elif LCD_Mode==Mode_4bit
	/*1- Set RS to LOW : for command */
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_RS_PIN,HIGH);
	
	/*2- Set RW to LOW : for Write */
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_RW_PIN,LOW);
	
	/*3- Send command */

	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data0,get_bit(Data,4));
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data1,get_bit(Data,5));
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data2,get_bit(Data,6));
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data3,get_bit(Data,7));
	
	/*4- send the enable pulse :enable pin high */
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_E_PIN,HIGH);
	_delay_ms(2);//Timer_delay(2); // delay 2 ms
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_E_PIN,LOW);
	_delay_ms(1);
	
	
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data0,get_bit(Data,0));
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data1,get_bit(Data,1));
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data2,get_bit(Data,2));
	DIO_set_pin_val(LCD_DATA_PORT,PIN_Data3,get_bit(Data,3));
		
	/*4- send the enable pulse :enable pin high */
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_E_PIN,HIGH);
	_delay_ms(2);//Timer_delay(2); // delay 2 ms
	DIO_set_pin_val(LCD_CTRL_PORT,LCD_E_PIN,LOW);
	_delay_ms(1);
	#endif
}

void LCD_INIT()
{
	#if LCD_Mode==Mode_8bit
	/*1- wait more than 30ms*/
	_delay_ms(40);//Timer_delay(40); //br7ty
	/*2- function set command : 2 line , font size */
	LCD_Send_Command(0b00111000);
	
	/*display on / of : display enable ,cursor off , blink cursor off */ 
	LCD_Send_Command(0b00001100);
	/*display clear */
	LCD_Send_Command(1);
	_delay_ms(1);
	
	#elif LCD_Mode==Mode_4bit
	
	_delay_ms(40);
	
		LCD_Send_Command(RETURN_HOME );

		/* Configure as 4-bit data mode*/
		LCD_Send_Command(FUNCTION_SET_4BIT_2LINES_5X7_DOTS);
		_delay_ms(2);

		/*Display ON OFF Control */
		LCD_Send_Command(DISPLAY_ON_CURSOR_OFF);
		_delay_ms(2);

		/* Clear Display */
		LCD_Send_Command(DISPLAY_CLEAR);
		_delay_ms(2);
		
	#endif
}

void LCD_sendString(const char* string)
{
	uint8 local_count=0;
	while(string[local_count]!='\0')
	{
		
		LCD_Send_Data(string[local_count]);
		local_count++;
	}
	
}

void LCD_ChangePOS_XY(uint8 POSX,uint8 POSY)
{
	uint8 POS_DDRAM=0;
	if(POSY==0)
	{
		POS_DDRAM= POSY*0x40+POSX;  // Now we have Address of DDRAM (3wd yasta)
	}
	if(POSY==1)
	{
		POS_DDRAM=POSY*0x40+POSX;	 // Now we have Address of DDRAM 
	}
	/*we need to go to address first then go write data on it*/
	/*we add 128 bec we send data and the last bit (D7) =1 look in data sheet so we can add 128 OR set_bit 7 =1 */
	LCD_Send_Command(POS_DDRAM+128);
}

void LCD_sendSpecial_char(uint8* pattern_Data_Array,uint8 pattern_no,uint8 XPOS,uint8 YPOS)
{
	uint8 CGRAM_Address,local_counter;
	/* 1- calculate CGRAM Address*/
	CGRAM_Address=pattern_no*8;
	/*2- send setCGRAM address command with 6 bit*/
	LCD_Send_Command(CGRAM_Address+64);
	/* 3- send(write) the pattern in CGRAM */ 
	for(local_counter=0;local_counter<8;local_counter++)
	{
		LCD_Send_Data(pattern_Data_Array[local_counter]);
	} 
	/*4- to display the figure position back to DDRAM  (ht3rdha feen yasta)*/
	LCD_ChangePOS_XY(XPOS,YPOS);
	/*5- to display data that store in CGRAM : send the pattern Number */
	LCD_Send_Data(pattern_no);
}

void LCD_INIT_DIR()
{
	#if LCD_Mode==Mode_8bit
	DIO_set_pin_dir(LCD_DATA_PORT,PIN0,OUTPUT);
	DIO_set_pin_dir(LCD_DATA_PORT,PIN1,OUTPUT);
	DIO_set_pin_dir(LCD_DATA_PORT,PIN2,OUTPUT);
	DIO_set_pin_dir(LCD_DATA_PORT,PIN3,OUTPUT);
	
	DIO_set_pin_dir(LCD_DATA_PORT,PIN4,OUTPUT);
	DIO_set_pin_dir(LCD_DATA_PORT,PIN5,OUTPUT);
	DIO_set_pin_dir(LCD_DATA_PORT,PIN6,OUTPUT);
	DIO_set_pin_dir(LCD_DATA_PORT,PIN7,OUTPUT);
	
	DIO_set_pin_dir(LCD_CTRL_PORT,LCD_E_PIN,OUTPUT);
	DIO_set_pin_dir(LCD_CTRL_PORT,LCD_RW_PIN,OUTPUT);
	DIO_set_pin_dir(LCD_CTRL_PORT,LCD_RS_PIN,OUTPUT);
	
	#elif LCD_Mode==Mode_4bit
	
	DIO_set_pin_dir(LCD_DATA_PORT,PIN_Data0,OUTPUT);
	DIO_set_pin_dir(LCD_DATA_PORT,PIN_Data1,OUTPUT);
	DIO_set_pin_dir(LCD_DATA_PORT,PIN_Data2,OUTPUT);
	DIO_set_pin_dir(LCD_DATA_PORT,PIN_Data3,OUTPUT);
	
	DIO_set_pin_dir(LCD_CTRL_PORT,LCD_E_PIN,OUTPUT);
	DIO_set_pin_dir(LCD_CTRL_PORT,LCD_RW_PIN,OUTPUT);
	DIO_set_pin_dir(LCD_CTRL_PORT,LCD_RS_PIN,OUTPUT);
	#endif
	
	
	
}



void LCD_Clear()
{
	LCD_Send_Command(1);
}


void LCD_VoidIntgerToString (uint16 num)
{
	uint8 buff[16];
	itoa(num, buff, 10);
	LCD_sendString(buff);
}



static uint16 Private_u16GetPower(uint8 Copy_u8Number1, uint8 Copy_u8Number2)
{
	uint16 Local_u16Result = 1;
	uint8 Local_u8Counter = 0;

	for(Local_u8Counter = 0; Local_u8Counter < Copy_u8Number2; Local_u8Counter++)
	{
		Local_u16Result *= Copy_u8Number1;
	}
	return Local_u16Result;
}


void LCD_voidWriteNumber(uint16 Copy_u16Number)
{
	uint8 Local_u8Counter = 0, Local_u8Digits = 0, Local_u8Current;
	uint16 Local_u16CopyNumber = Copy_u16Number;

	if(0 == Copy_u16Number)
	{
		LCD_Send_Data('0');
	}
	else
	{
		while(Local_u16CopyNumber)
		{
			Local_u16CopyNumber /= 10;
			Local_u8Digits++;
		}
		Local_u16CopyNumber = Copy_u16Number;

		for(Local_u8Counter = 0; Local_u8Counter < Local_u8Digits; Local_u8Counter++)
		{
			Local_u8Current = Local_u16CopyNumber / (Private_u16GetPower(10, Local_u8Digits - 1 - Local_u8Counter));
			LCD_Send_Data(Local_u8Current + '0');
			Local_u16CopyNumber %= (Private_u16GetPower(10, Local_u8Digits - 1 - Local_u8Counter));
		}
	}
}



/////////////////////////////////////////////


void LCD_4bit_init()
{
	_delay_ms(40);
	
	/*LCD_Send_Command(0b00100000);
	LCD_Send_Command(0b00100000);
	LCD_Send_Command(0b10000000);
	
	// wait 37 us
	_delay_ms(2);
	LCD_Send_Command(0b00000000);
	LCD_Send_Command(0b11000000);
	_delay_ms(2);
	LCD_Send_Command(0b00000000);
	LCD_Send_Command(0b00010000);
	//LCD_Send_Command(0x01);
	_delay_ms(2);
	*/	
} 

void lcd_write_s_char(int no_pattern,int * arr_pattern ,int posx,int posy) 
{
	int CGRAM_ADD, local_count;
	CGRAM_ADD=8* no_pattern;
	LCD_Send_Command(CGRAM_ADD+64);
	for(local_count=0;local_count<8;local_count++)
	{
		LCD_Send_Data(arr_pattern[local_count]); // 3malna save
	}
	LCD_ChangePOS_XY(posx,posy);
	LCD_Send_Data(no_pattern); // data show to screen 
}

