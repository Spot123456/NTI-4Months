/*
 * RTC_Interface.h
 *
 * Created: 9/26/2023 12:19:54 AM
 *  Author: Ahmed Nour
 */ 


#ifndef RTC_INTERFACE_H_
#define RTC_INTERFACE_H_

typedef struct
{
	uint8	sec;
	uint8	min;
	uint8	hour;
}date;

void RTC_init();
void RTC_write(date*x);
void RTC_read1(uint8*x,uint8*y,uint8*z);
void RTC_read(date*x);

#endif /* RTC_INTERFACE_H_ */