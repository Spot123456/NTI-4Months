/*
 * EXTI_Config.h
 *
 * Created: 9/14/2023 10:45:43 PM
 *  Author: Ahmed Nour
 */ 


#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

// to enable any of interrupt write 1 
// for disable any interrupt write 0 

#define EXTI_0	1
#define EXTI_1	1
#define EXTI_2	0



// select pre_sense for interrupt in init
#define Select_sense_0	Rising_edge
#define Select_sense_1	Rising_edge
#define Select_sense_2	Rising_edge
// this use for change sense in run time
#define EXTI0	0
#define EXTI1	1
#define EXTI2	2

#endif /* EXTI_CONFIG_H_ */