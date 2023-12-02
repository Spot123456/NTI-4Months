/*
 * EXTI_Interface.h
 *
 * Created: 9/14/2023 10:45:24 PM
 *  Author: yahia
 */ 


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define on_change		1
#define Rising_edge		2
#define falling_edge	3
#define low_level		4


void Enable_Globla_INT();
void Disable_global_int();
void EXTI_Inti();

uint8 EXTI_sense(uint8 EXTI,uint8 sense);

uint8 EXTI_Set_call_back(void(*notification)(void), uint8 NO_of_interrupt);




#endif /* EXTI_INTERFACE_H_ */