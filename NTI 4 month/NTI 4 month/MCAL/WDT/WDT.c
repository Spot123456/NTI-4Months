/*
 * WDT.c
 *
 * Created: 9/22/2023 10:18:02 AM
 *  Author: Ahmed Nour
 */ 

#include "../../utilities/datatypes.h"
#include "../../utilities/math.h"
#include "WDT_Config.h"
#include "WDT_Interface.h"
#include "WDT_Private.h"
void WDT_Init()
{
	/*select prescale*/
	WDTCR_REG&=WDT_mask;
	WDTCR_REG|=WDT_pre2s;
}

void WDT_Enable()
{
	set_bit(WDTCR_REG,WDE);
}

void WDT_Disable()
{
	WDT_refresh();
	WDTCR_REG |= (1<<WDTOE) | (1<<WDE);
	/* Turn off WDT */
	WDTCR_REG = 0x00;
}
void WDT_refresh()
{
	asm("wdr");
}

