/*
 * Timer_Config.h
 *
 * Created: 9/15/2023 9:56:31 AM
 *  Author: Ahmed Nour
 */ 


#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

#define normal_mode	1
#define CTC_mode	2
#define PWM_mode	3
#define PWM_Phase_mode	4

#define Timer_0_mode	normal_mode	//PWM_mode


#define CTC_no_out	0
#define CTC_toggle	1
#define CTC_clear	2
#define CTC_set		3

#define output_mode	CTC_no_out	


#define OCR0_val 250
#define	time_preload_val  0
#define timer0_prescaler_mask 0b11111000
#define timer_8prescaler 2
#define Timer_EXT_count		7
#define timer_1024 5

#define off		0
#define on		1
#define Timer_count	off

#endif /* TIMER_CONFIG_H_ */