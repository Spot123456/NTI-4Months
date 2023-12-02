
/*
 * Erorr_Type.h
 *
 * Created: 9/9/2023 9:07:28 AM
 *  Author:Ahmed Nour
 */ 


#ifndef ERORR_TYPE_H_
#define ERORR_TYPE_H_

typedef enum
{
	nok,
	ok
} EN_Erorr_types;

#define empty  0
#define busy   1
#define OK     2
#define NOK	   3
#define ADC_TimeOut 10000    //for example 10k
#define NULL_POINTER	4    // from imt
#define TIMEOUT_STATE	5	// from imt
#define BUSY_STATE		6	// from imt

#endif /* ERORR_TYPE_H_ */