/*
 * math.h
 *
 * Created: 9/4/2023 3:12:52 PM
 *  Author: ahmed nour
 */ 


#ifndef MATH_H_
#define MATH_H_

#define set_bit(PortID, Pos)		PortID|=(1<<Pos)
#define clr_bit(PortID, Pos)		PortID&=~(1<<Pos)
#define toggle_bit(PortID, Pos)		PortID^=(1<<Pos)
#define get_bit(PortID, Pos)		 (((PortID)>>(Pos)) & 0x01)



#endif /* MATH_H_ */