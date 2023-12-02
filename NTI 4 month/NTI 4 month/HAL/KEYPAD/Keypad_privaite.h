/*
 * Keypad_privaite.h
 *
 * Created: 9/10/2023 9:19:08 AM
 *  Author:	Ahmed Nour
 */ 


#ifndef KEYPAD_PRIVAITE_H_
#define KEYPAD_PRIVAITE_H_
#include "Keypad_config.h"

uint8 rowpins[rows]={0,1,2,3};
uint8 colpins[cols]={4,5,6,7};
//uint8 keypad_map[rows][cols]= {{1,2,3,'+'},{4,5,6,'-'},{7,8,9,'*'},{'/',0,'=','%'}};
uint8 keypad_map[rows][cols]= {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'r','0','=','+'}};


#endif /* KEYPAD_PRIVAITE_H_ */