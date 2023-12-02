/*
 * ICU_Interface.h
 *
 * Created: 9/16/2023 11:33:18 AM
 *  Author: yahia
 */ 


#ifndef ICU_INTERFACE_H_
#define ICU_INTERFACE_H_

void ICU_init();

void ICU_change_sence(uint8 sence);
void ICU_set_EdgeType(uint8 Edge_Type);

uint16 ICU_get_inputCap();

void ICU_clear_timer();

void set_CallBackFun_ICU(void(*func)(void));




#endif /* ICU_INTERFACE_H_ */