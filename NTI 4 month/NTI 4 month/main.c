/*
 * NTI 4 month.c
 *
 * Created: 9/4/2023 3:11:36 PM
 * Author : Ahmed Nour
 * version: 1.0.0
 */ 

//#include <avr/io.h>

#include "MCAL/DIO/DIO_INTERFACE.h"
#include "utilities/datatypes.h"
#include "utilities/math.h"
#include "util/delay.h"
#include "HAL/KEYPAD/Keypad_Interface.h"
#include "HAL/SSG/SSG_Interface.h"
#include "HAL/LCD/LCD.h"
#include "MCAL/TIMERS/Timer_Interface.h"
#include "HAL/ICU/ICU_Interface.h"
#include "COMM/UART/UART_Interface.h"
#include "MCAL/EXTI/EXTI_Interface.h"
#include "MCAL/WDT/WDT_Interface.h"
#include "COMM/SPI/SPI_Interface.h"
#include "COMM/I2C/I2C_Interface.h"
#include "HAL/EEPROM/EEPROM_Interface.h"
#include "HAL/RTC/RTC_Interface.h"
#define F_CPU	16000000

void mathfun()
{
	int x ,y,z=0;
	char op,k ;
	x=keypad_getval();
	while(x==99)
	{
		x=keypad_getval();
		
	}
	LCD_voidWriteNumber(x-'0');
	
	op=keypad_getval();
	while(op==99)
	{
		op=keypad_getval();
	}
	LCD_Send_Data(op);
	
	y=keypad_getval();
	while(y==99)
	{
		y=keypad_getval();
	}
	
	LCD_voidWriteNumber(y-'0');
	switch (op)
	{
		case '+':	z=(x-'0')+(y-'0'); break;
		case '-':	z=(x-'0')-(y-'0'); break;
		case '/':	z=(x-'0')/(y-'0'); break;
		case '*':	z=(x-'0')*(y-'0'); break;
		
	}
	k=keypad_getval();
	while(k==99)
	{
		k=keypad_getval();
		if(k=='=')
		{
			 LCD_Send_Data(k);
			 LCD_voidWriteNumber(z);
		}
		
	}
	if(k=='r')
	{
		LCD_Clear();
	}	
}

/*		ADV Math		*/

void ADV_math()
{
	uint8 arr[10];
	uint8 i;
	char op ;
	char x;
	uint64 result, num1=0,num2=0;
	for(i=0;i<2;i++)
	{
		arr[i]=keypad_getval();
		while(arr[i]==99)
		{
			arr[i]=keypad_getval();
		}
			if ((arr[i]!='+')&&(arr[i]!='-')&&(arr[i]!='*')&&(arr[i]!='/')&&(arr[i]!='='))
			{
				
				LCD_voidWriteNumber(arr[i]-'0');
				arr[i]=arr[i]-'0';
				num1=num1*10+arr[i];
				
			}
			else
			{
				break;
			}
	}
	
		op=keypad_getval();
		while(op==99)
		{
			op=keypad_getval();
		}
			if (op=='+')
			{
				op='+';
				
			}
			else if (op=='-')
			{
				op='-';
				
			}
			else if (op=='*')
			{
				op='*';
			
			}
			else if (op=='/')
			{
				op='/';
			}
			LCD_Send_Data(op);
	
	for(i=0;i<9;i++)
	{
		arr[i]='\0';
	}

	for(i=0;i<2;i++)
	{
			arr[i]=keypad_getval();
				while(arr[i]==99)
				{
					arr[i]=keypad_getval();
				}
		
			if ((arr[i]!='+')&&(arr[i]!='-')&&(arr[i]!='*')&&(arr[i]!='/')&&(arr[i]!='='))
			{
			
				//arr[i]-='0';
				LCD_voidWriteNumber(arr[i]-'0');
				arr[i] = arr[i] - '0';
				num2=num2*10+arr[i];
				
			}
			else if ((arr[i]=='+')||(arr[i]=='-')||(arr[i]=='*')||(arr[i]=='/')||(arr[i]=='='))
			{
				break;
			}
	}
		x= keypad_getval();
		while(x==99)
		{
			x= keypad_getval();
		}
		if(x=='=')
		{
			if(op=='+')
			{
				result = num1+num2;
			}
			else if(op=='-')
			{
				result = num1-num2;
			
			}
			else if(op=='*')
			{
				result = num1*num2;
			}
			else if(op=='/')
			{
				result = num1/num2;
				
			}
			LCD_Send_Data(x);
			LCD_voidWriteNumber(result);
			
		}
	
	
}
/*
void ADV_math()
{
	uint8 arr[10], i;
	char op;
	uint64 result, num1 = 0, num2 = 0;

	for (i = 0; i < 2; i++) {
		while (1) {
			arr[i] = keypad_getval();
			while (arr[i]==99)
			{
				arr[i] = keypad_getval();
			}
			if ((arr[i] >= '0' && arr[i] <= '9') || arr[i] != '+' || arr[i] != '-' || arr[i] != '*' || arr[i] != '/') {
				break;
			}
		}
		LCD_voidWriteNumber(arr[i] - '0');
		arr[i] = arr[i] - '0';
		num1 = num1 * 10 + arr[i];
	}

	op = keypad_getval();
	while (op == 99) {
		op = keypad_getval();
	}

	if (op == '+' || op == '-' || op == '*' || op == '/') {
		LCD_Send_Data(op);
		} else {
		return;
	}

	for (i = 0; i < 2; i++) {
		while (1) {
			arr[i] = keypad_getval();
			while (arr[i]==99)
			{
				arr[i] = keypad_getval();
			}
			if ((arr[i] >= '0' && arr[i] <= '9') || arr[i] == '+' || arr[i] == '-' || arr[i] == '*' || arr[i] == '/') {
				break;
			}
		}
		LCD_voidWriteNumber(arr[i] - '0');
		arr[i] = arr[i] - '0';
		num2 = num2 * 10 + arr[i];

		if (arr[i] == '=') {
			break;
		}
	}

	if (op == '+') {
		result = num2 + num1;
		} else if (op == '-') {
		result = num2 - num1;
		} else if (op == '*') {
		result = num2 * num1;
		} else if (op == '/') {
		result = num2 / num1;
	}

	LCD_Send_Data('=');
	LCD_voidWriteNumber(result);
}
*/
/*
uint16 static local_timer=0;
void count_over(void)
{
	uint16 static local_counter=0;
	local_counter++;
	local_timer+=(local_counter*256);
}

void led_void()
{
	uint16 static local_counter = 0 ;
	uint8 static z=0;
	local_counter++;
	if(local_counter==2000)
	{
		z^=1;
		DIO_set_pin_val(PORT_C,PIN0,z);
		local_counter=0;
	}
	
	
}*/
/*
uint8 volatile flag=0;
uint16  volatile temp=0;
uint16	volatile temp2=0;
uint16  volatile temp3=0;
uint16	 t_cycle=0;
uint16   ton=0;
void icu_HW()
{
	
	
	if( flag == 0)
	{
		//LCD_voidWriteNumber(50);
		// clear timer
		ICU_clear_timer();
		temp=ICU_get_inputCap();
		ICU_change_sence(0);
		flag = 1;
		
		//lcd_write_char('c');
	}
	else if(flag == 1)
	{
		temp2=ICU_get_inputCap();
		 t_cycle=temp2-temp;
		
		ICU_change_sence(1);
		flag=2;
	}
	else if(flag == 2)
	{
		temp3 = ICU_get_inputCap();
		ton=temp3-temp2;
		ICU_change_sence(0);
		flag = 3;
		
	}
	else{}
}

int main(void)
{
	Timer1_init();
	//DIO_set_pin_dir(PORT_B,PIN3,OUTPUT);
	uint8 i=0 ;
	DIO_set_pin_dir(PORT_D,PIN5,OUTPUT);
	DIO_set_pin_dir(PORT_D,PIN4,OUTPUT);
		 Timer1_voidSetChannelACompValue(1000);
		 Timer1_voidSetChannelBCompValue(10);
	ICU_init();
	Timer0_Init();
	Timer0_pwm(127);
	Enable_Globla_INT();
	set_CallBackFun_ICU(& icu_HW);
	LCD_INIT_DIR();
	LCD_INIT();
	DIO_set_pin_dir(PORT_B,PIN3,OUTPUT);
	DIO_set_pin_dir(PORT_D,PIN6,INPUT);
	
	uint16 duty= (ton*100)/(t_cycle);
	LCD_ChangePOS_XY(0,0);
	LCD_voidWriteNumber(duty);

	while(1)
	{
	
	}
}*/

// void main ()
// {
// 	DIO_set_pin_dir(PORT_D,PIN1,OUTPUT);
// 	DIO_set_pin_dir(PORT_D,PIN0,INPUT);
// 	LCD_INIT_DIR();
// 	LCD_INIT();
// 	UART_init();
// 	//UART_voidSendStringBlocking('ahmed');
// 	uint8 received[6] = {0};
// 	//keypad_init2();
// 	uint8 i ,press;
// // 	for(i=0;i<6;i++)
// // 	{
// // 		received[i]=UART_ReceivedData();
// // 		LCD_Send_Data(received[i]);
// // 	}
// 
// DIO_set_pin_dir(PORT_D,PIN7,INPUT);
// DIO_set_pin_dir(PORT_D,PIN6,INPUT);
// DIO_set_pin_dir(PORT_D,PIN5,INPUT);
// DIO_set_pin_dir(PORT_D,PIN3,INPUT);
// uint8 val , val2,val3,val4;
// DIO_set_pin_dir(PORT_A,PIN6,OUTPUT);
// 	while(1)
// 	{
// 	/*	press= keypad_scan();
// 		while(press==0x99)
// 		{
// 			press= keypad_scan();
// 		}
// 		UART_SendData(press);*/
// 	DIO_get_pin_val(PORT_D,PIN7,&val);
// 	
// 	if(val==0)
// 	{
// 		DIO_set_pin_val(PORT_A,PIN6,HIGH);
// 
// 		UART_SendData('r');
// 				LCD_Send_Data('1');
// 		DIO_get_pin_val(PORT_D,PIN7,&val);
// 	//	while(val==0);
// 	}
// 	DIO_get_pin_val(PORT_D,PIN6,&val2);
// 	if(val2==0)
// 	{
// 		UART_SendData('b');
// 				LCD_Send_Data('b');
// 		DIO_get_pin_val(PORT_D,PIN6,&val2);
// 	//	while(val2==0);
// 		
// 	}
// 	
// 	DIO_get_pin_val(PORT_D,PIN5,&val3);
// 	if(val3==0)
// 	{
// 		UART_SendData('g');
// 				LCD_Send_Data('4');
// 		DIO_get_pin_val(PORT_D,PIN6,&val3);
// 	//	while(val3==1);
// 		
// 	}
// 	DIO_get_pin_val(PORT_D,PIN3,&val);
// 	if(val4==0)
// 	{
// 		UART_SendData('y');
// 		LCD_Send_Data('4');
// 		DIO_get_pin_val(PORT_D,PIN6,&val4);
// 		//while(val4==0);
// 		
// 	}
// 		
// 	}
// 
// }
/**********************************************/


/*uint32 volatile temp1;
uint32 volatile temp2;
uint32 volatile temp3;
uint64 volatile ovr=0;
uint8 static flag =0;
uint32 volatile t_on=0;
uint32 volatile t_off=0;
uint32 volatile duty=0;
#include "MCAL/EXTI/EXTI_Config.h"
void icu_ssw()
{
	if(flag==0)
	{
		//Timer_stop();
		TIMER0_void_setTCNT0(0);
		flag=1;
		EXTI_sense(0,falling_edge);
		
	}
	else if (flag==1)
	{
		temp2= (timer0_getTCNT_val()+(ovr*255)) ;
		TIMER0_void_setTCNT0(0);
		ovr=0;
		flag=2;
		EXTI_sense(0,Rising_edge);
		
	}
	else if (flag==2)
	{
		temp3= (timer0_getTCNT_val()+(ovr*255)) ; // t off
		ovr=0;
		flag=1;
		EXTI_sense(0,falling_edge);
	
	
		flag=1;
	}
	else
	{}
}
void TOVF_APP (void)
{
	ovr++;
}
/*
void main ()
{
	DIO_set_pin_dir(PORT_D,PIN5,OUTPUT);
	DIO_set_pin_dir(PORT_D,PIN2,INPUT);
	
	LCD_INIT_DIR();
	LCD_INIT();
	LCD_Clear();
	
	Timer0_Init();
	Timer1_init();
	//Timer1_voidSetChannelACompValue(1000);
	
	EXTI_Inti();
	Enable_Globla_INT();
	
	Timer0_OV_setcallback(TOVF_APP);
	EXTI_Set_call_back(icu_ssw,0);
	
	
	uint32 freq=0,f;
	while(1)
	{
			duty = ((temp2*100)/(temp2+temp3));
			f= 1 / (temp2+temp3);
			freq=(int)f;
			LCD_ChangePOS_XY(0,0);
			LCD_sendString("duty=");
			LCD_ChangePOS_XY(7,0);
			LCD_Send_Data(( duty / 10 ) + 48);
			LCD_Send_Data(( freq % 10) + 48);
			LCD_ChangePOS_XY(0,1);
			LCD_sendString("t_on=");
			LCD_ChangePOS_XY(7,1);
			LCD_voidWriteNumber(temp2);
			_delay_ms(3000);
			LCD_Clear();
			LCD_ChangePOS_XY(1,1);
			LCD_sendString("t_cycle=");
			LCD_ChangePOS_XY(7,1);
			LCD_voidWriteNumber(temp2+temp3);
			_delay_ms(3000);
			LCD_Clear();
	}
}

*/
/************************************************/
 // ADC_ trigger
/*
uint16  ldr=0, pot =0;
uint16  data1=0,data2=0;
void adc_trigger()
{

}

void main ()
{
	
	LCD_INIT_DIR();
	LCD_INIT();
	
	EXTI_Inti();
	Enable_Globla_INT();
	
	ADC_init();
	

	DIO_set_pin_dir(PORT_A,PIN0,INPUT);
	DIO_set_pin_dir(PORT_A,PIN1,INPUT);
		 
		
	
//	EXTI_Set_call_back(adc_trigger,0);
	
	while(1)
	{
		data1 =(uint32)((uint32) pot*(uint32)500)/(uint32)(1023);
		data2 =(uint32) ((uint32)ldr*(uint32)500)/(uint32)(1023);
		LCD_Clear();
		LCD_ChangePOS_XY(0,0);
		LCD_sendString("pot=");
		//LCD_ChangePOS_XY(5,0);
		LCD_voidWriteNumber(data1);
		LCD_ChangePOS_XY(0,1);
		LCD_sendString("ldr=");
		LCD_ChangePOS_XY(5,1);
		LCD_voidWriteNumber(data2);
		pot=ADC_Start_Conversion(0);
		ldr=ADC_Start_Conversion(1);
		
	}
}


*/

/***********************************************/
// WDT  main code
/*
void main ()
{
	DIO_set_pin_dir(PORT_A,PIN1,OUTPUT);
	while(1)
	{
		WDT_Init();
		WDT_Enable();
		DIO_set_pin_val(PORT_A,PIN1,HIGH);
		_delay_ms(10);
		WDT_refresh();
		DIO_set_pin_val(PORT_B,PIN1,HIGH);
		_delay_ms(18);
		DIO_set_pin_val(PORT_B,PIN2,HIGH);
	}
}*/
/***********************************************/

// spi stack 
/*
uint8 data[200]={'a','b'};
uint8 static i=0;
void spi_receive_void()
{
	spi_stack_pop(data[i]);
	i++;
}

void spi_send_void()
{
	spi_stack_push(data[i]);
	i++;
}


void main ()
{
	DIO_set_pin_dir(PORT_B,PIN4,OUTPUT);
	DIO_set_pin_dir(PORT_B,PIN5,OUTPUT);
	DIO_set_pin_dir(PORT_B,PIN6,INPUT);
	DIO_set_pin_dir(PORT_B,PIN7,OUTPUT);
	Spi_init();
	spi_TxRx('a');
	 uint8 state,state2;
	
	while(1)
	{
		/*state=spi_stack_pop(&data); //received
		if (state==0) // empty 
		{
			// return empty 	
		}	
		else
		{
			spi_call_back(spi_receive_void);
		}
		
		state2=spi_stack_push(data[0]);
		if(state==1)
		{
			// return full
		}
		else
		{
			spi_call_back(spi_send_void);
		}
		
		
	}
}
*/
		
/************************************************/

// i2c debugger
/*
void main ()
{
	DIO_set_pin_dir(PORT_C,PIN0,OUTPUT);
	DIO_set_pin_dir(PORT_C,PIN1,OUTPUT);
	TWI_voidInitMaster(10);
	TWI_SendStartCondition();
	TWI_SendSlaveAddressWithWrite((0b1010000));
	TWI_MasterWriteDataByte(15);
	//TWI_SendStopCondition();
	TWI_SendRepeatedStart();
	TWI_SendSlaveAddressWithWrite((0b1010000));
	TWI_MasterWriteDataByte(10);
	TWI_SendStopCondition();
	while(1)
	{
		
	}	
}
		
*/

/****************************************************************/

/*
// EEPROM TEST

void main()
{
	DIO_set_pin_dir(PORT_A,PIN6,OUTPUT);
		_delay_ms(100);
	LCD_INIT_DIR();
	LCD_INIT();
	
	TWI_voidInitMaster(0);
	
	EEPROM_Write(114,28);
	//	LCD_voidWriteNumber(EEPROM_Read(104));
	EEPROM_Write(116,30);
	
	EEPROM_Write(107,60);
	
	LCD_voidWriteNumber(EEPROM_Read(116));
	LCD_voidWriteNumber(EEPROM_Read(114));

	LCD_voidWriteNumber(EEPROM_Read(107));
	_delay_ms(500);

// 	LCD_voidWriteNumber(EEPROM_Read(104));
// 		uint8 data =0;
// 		uint8 data1=0;
// 		uint8 data2=0;	
// 		/*data= EEPROM_Read(105);
// 		LCD_Send_Data('B');
// 		_delay_ms(1000);
// 			LCD_Send_Data('C');
// 		data2= EEPROM_Read(105);
// 		LCD_Send_Data('G');*/
// 	while(1)
// 	{
// //LCD_voidWriteNumber(EEPROM_Read(105));
// 	
// 		/*LCD_ChangePOS_XY(0,0);
// 		
// 		LCD_voidWriteNumber(data);
// 		_delay_ms(1000);
// 		
// 			LCD_ChangePOS_XY(8,0);
// 			LCD_Send_Data('F');
// 			LCD_voidWriteNumber(data1);
// 			_delay_ms(1000);*/
// 		
// 		DIO_set_pin_val(PORT_A,PIN6,HIGH);
// 	
// 		
// 	}
// }	
// */


/**************************************************/

/*RTC*/

// void main ()
// {
// 	LCD_INIT_DIR();
// 	LCD_INIT();
// 	
// 	date x;
// 	date y;
// 	TWI_voidInitMaster(0);
// 	RTC_init();
// 	x.sec= 0b00000100; // 33 sec 
// 	x.min= 0b00100010 ;// 22 min
// 	x.hour = 0b00010010; // 24 hour mode the time =12
// 	RTC_write(&x);
// 	
// 	while(1)
// 	{
// 		RTC_read(&y);
// 		LCD_ChangePOS_XY(0,0);
// 		LCD_voidWriteNumber(y.sec);
// 		LCD_ChangePOS_XY(0,4);
// 		LCD_voidWriteNumber(y.min);
// 		LCD_ChangePOS_XY(0,8);
// 		LCD_voidWriteNumber(y.hour);
// 	}
// }
/****************************************************/
// rtc

	date x={0};
	date y={0};
		uint8 a,b,c;
void main ()
{
	LCD_INIT_DIR();
	LCD_INIT();

	//WDT_Init();
	//WDT_Enable();
	TWI_voidInitMaster(0);
	RTC_init();
	//_delay_ms(3000);
	x.sec= 0b00110011; // 33 sec
	x.min= 0b00100010 ;// 22 min
	x.hour = 0b00010101; // 24 hour mode the time =15
	RTC_write(&x);
	_delay_ms(1000);
	//RTC_read(&y);
	
	while(1)
	{
 		RTC_read(&y);
		
		//RTC_read1(&a,&b,&c);
		
		
		LCD_ChangePOS_XY(0,0);
		LCD_VoidIntgerToString(y.sec);
		//LCD_voidWriteNumber(a);
		LCD_ChangePOS_XY(4,0);
		LCD_VoidIntgerToString(y.min);
		//LCD_voidWriteNumber(b);
		
		LCD_ChangePOS_XY(8,0);
		//LCD_VoidIntgerToString(c);
		LCD_voidWriteNumber(y.hour);
		_delay_ms(500);
		LCD_Clear();
		// Write the current time to the RTC
		//RTC_write(&y);
	}
}


/******************************************************/

// traffic light
/*

uint8 min_count = 15;
uint8 max_count = 100;
uint8 count=15;
void inc(void)
{
	count ++ ; 
	if( count >max_count)
	{
		count=max_count;
	}
	else
	{
		// do nothing
	}
	
}

void dec(void)
{
	count -- ;
	if( count <min_count)
	{
		count=min_count;
	}
	else
	{
		// do nothing
	}
}

void fun (void)
{

	static uint16 local_counter=0;
	local_counter++;
	static uint16 counter_sec= 0 ;
	if(counter_sec<count)
	{
			DIO_set_pin_val(PORT_C,PIN0,HIGH);
	}
	if(local_counter==3906 )
	{
		
		counter_sec ++ ;
		SSG_Display(counter_sec);
		 local_counter=0;
		if (counter_sec == count)
		{
			DIO_set_pin_val(PORT_C,PIN0,LOW);	// green
			DIO_set_pin_val(PORT_C,PIN2,HIGH); // red
			
		}
		else if ( counter_sec == count*2)
		{
			DIO_set_pin_val(PORT_C,PIN2,LOW); //red
			local_counter=0;
			counter_sec=0;
		}
		if ( (counter_sec== count-3 && counter_sec<count) ||( counter_sec== 2*count-3 && counter_sec<2*count ))
		{
			for( uint8 i =0 ; i<=12 ; i++ )
			{
				DIO_set_pin_val(PORT_C,PIN1,HIGH);
				_delay_ms(125*8);
				DIO_set_pin_val(PORT_C,PIN1,LOW);
				_delay_ms(125*8);
				
			}
			
		}
		
		
	}

}
void main ()
{
//	uint8 i = 0 , j =0;uint8 counter;
	// init button
	DIO_set_pin_dir(PORT_A,PIN0,INPUT);
	DIO_set_pin_dir(PORT_A,PIN1,INPUT);
	// init leds
	DIO_set_pin_dir(PORT_C,PIN0,OUTPUT);
	DIO_set_pin_dir(PORT_C,PIN1,OUTPUT);
	DIO_set_pin_dir(PORT_C,PIN2,OUTPUT);
	// set up ssg
	SSG_init();
	SSG_enable(0);
	// open exti 0 
	EXTI_Inti();
	EXTI_sense(0,Rising_edge);
	EXTI_Set_call_back(&inc,0);
	// open exti 1
	
	EXTI_Inti();
	EXTI_sense(1,Rising_edge);
	EXTI_Set_call_back(&dec,1);
	// set global int 
	Enable_Globla_INT();
	// init timer
	Timer0_Init();
	Timer0_OV_setcallback(&fun);

	while(1)
	{
		
/*	for (j=0;j<=count*2;j++)
	{
			for(j=0;j<=count;i++)
			{
				DIO_set_pin_val(PORT_C,PIN0,HIGH); // led
				Timer_delay(1000*count); // HW Timer
				if(j<=3)
				{
					DIO_set_pin_val(PORT_C,PIN1,HIGH);
					_delay_ms(125);
					DIO_set_pin_val(PORT_C,PIN1,LOW);
					_delay_ms(125);
				}
				DIO_set_pin_val(PORT_C,PIN0,LOW);
			}
		if((j==count) && (j<=2* count))
		{
				for(i=0;i<=count;i++)
				{
					DIO_set_pin_val(PORT_C,PIN3,HIGH); // led
					Timer_delay(1000*count); // HW Timer
					if(i<=3)
					{
						for( uint8 k =0 ; k < 12 ; k ++)
						{
							DIO_set_pin_val(PORT_C,PIN1,HIGH);
							_delay_ms(125);
							DIO_set_pin_val(PORT_C,PIN1,LOW);
							_delay_ms(125);
						}
						
					}
					DIO_set_pin_val(PORT_C,PIN3,LOW);
				}
		}
	}	//

	
	
	}
}

*/


/****************************************************/
//#include "OS/TMU/TMU_int.h"

/*void main ()
{
	
	while(1)
	{
		
	}
}*/

/*
void t0 (void)
{
	DIO_set_pin_val(PORT_C,PIN0,HIGH);
	_delay_ms(10);
	DIO_set_pin_val(PORT_C,PIN0,LOW);
	_delay_ms(10);
}
void t1 (void)
{
	DIO_set_pin_val(PORT_C,PIN1,HIGH);
	_delay_ms(10);
	DIO_set_pin_val(PORT_C,PIN1,LOW);
	_delay_ms(10);
	
	//DIO_enuTogglePinValue(DIO_GROUP_C , DIO_PIN_5);
}
void t2 (void)
{
	DIO_set_pin_val(PORT_C,PIN2,HIGH);
	_delay_ms(10);
	DIO_set_pin_val(PORT_C,PIN2,LOW);
	_delay_ms(10);
	//DIO_enuTogglePinValue(DIO_GROUP_C , DIO_PIN_7);
}
*/
/*uint8 min_count = 15;
uint8 max_count = 100;
uint8 count=15;
void Yellow_on (void)
{
	
}
void red_on (void)
{
	uint8 local_counter= 0;
	local_counter++;
	if(local_counter<=count)
	{
		DIO_set_pin_val(PORT_C,PIN2,LOW);
	}
	else if (local_counter<count*2)
	{
		DIO_set_pin_val(PORT_C,PIN2,HIGH);
		local_counter=0;
	}
}
void green_on (void)
{
	uint8 local_counter= 0;
	local_counter++;
	if(local_counter<=count)
	{
			DIO_set_pin_val(PORT_C,PIN0,HIGH);
	}
	else if (local_counter<count*2)
	{
		DIO_set_pin_val(PORT_C,PIN0,LOW);
		local_counter=0;
	}

	
}

int main(void)
{
	DIO_set_pin_dir(PORT_C,PIN0,OUTPUT);
	DIO_set_pin_dir(PORT_C,PIN1,OUTPUT);
	DIO_set_pin_dir(PORT_C,PIN2,OUTPUT);
	//DIO_enuSetPinDirection(DIO_GROUP_C , DIO_PIN_2, DIO_OUTPUT);
	//DIO_enuSetPinDirection(DIO_GROUP_C , DIO_PIN_5, DIO_OUTPUT);
	//DIO_enuSetPinDirection(DIO_GROUP_C , DIO_PIN_7, DIO_OUTPUT);
	TMU_vidInit();

	TMU_vidCreateTask(green_on , 100 , 2);
	TMU_vidCreateTask(red_on ,100  , 1);
	TMU_vidCreateTask(yellow_on ,100  , 0);

	TMU_vidStartScheduler();
}
*/


/*
#include "RTOS_OS/FreeRTOS.h"
#include "RTOS_OS/task.h"
uint8 flag=0,flag1=0;
void Task1(void)
{
	while(1)
	{
		if(flag==0)
		{
			DIO_set_pin_val(PORTA,PIN4, HIGH);
			flag=1;
			vTaskDelay(750);
		}
		else
		{
				DIO_set_pin_val(PORTA,PIN4, LOW);
				flag=0;
				vTaskDelay(750);
		}
		
	}
	
}
void Task2(void)
{
	while(1)
	{
		if(flag1==0)
		{
			DIO_set_pin_val(PORTA,PIN5, HIGH);
			flag=1;
			vTaskDelay(1250);
		}
		else
		{
			DIO_set_pin_val(PORTA,PIN5, LOW);
			flag1=0;
			vTaskDelay(1250);
		}
		
	}
	
}
void main ()
{
	DIO_set_pin_dir(PORT_A,PIN5,OUTPUT);
	DIO_set_pin_dir(PORT_A,PIN4,OUTPUT);
	xTaskCreate(Task1,NULL,100,NULL,1,NULL);
	xTaskCreate(Task2,NULL,100,NULL,2,NULL);
	vTaskStartScheduler();
	while(1)
	{
		
	}
}

*/