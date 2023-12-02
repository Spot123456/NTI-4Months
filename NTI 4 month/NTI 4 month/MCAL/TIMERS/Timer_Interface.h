/*
 * Timer_Interface.h
 *
 * Created: 9/15/2023 9:57:18 AM
 *  Author: Ahmed Nour
 */ 


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

void Timer_delay(float msecend);


void TIMER0_void_setTCNT0(uint8 value_cpy);

void Timer0_Init();
void Timer0_start_Preload(uint8 val);
void Timer0_ocr(uint8 ocr_val);
void Timer_stop();
uint8 Timer0_OV_setcallback(void(*notification)(void));
uint8 Timer0_CTC_setcallback(void(*notification)(void));
uint8 timer0_getTCNT_val();
void Timer0_pwm(uint8 Copy_PWM);

void Timer1_init();
void Timer1_voidSetChannelACompValue(uint16 copy_u16Value);
void Timer1_voidSetChannelBCompValue(uint16 copy_u16Value);
#endif /* TIMER_INTERFACE_H_ */