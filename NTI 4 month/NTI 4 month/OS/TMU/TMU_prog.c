/*
 * TMU_prog.c
 *
 *  Created on: Oct 7, 2023
 *      Author: Ahmed El-Gaafrawy
 */
#include "../../utilities/datatypes.h"
#include "../../utilities/math.h"

#include "TMU_config.h"
#include "TMU_priv.h"

static uint16 LOC_u16OvfCounts = 0 ;
static uint16 LOC_u16ISRCounts = 0 ;
static uint8 LOC_u8Preload = 0 ;


static TCB_t LOC_astrTasksTCB [ TMU_MAX_NUM_TASKS ] = {0};
static uint32 LOC_u32OsTicks = 0 ;


void TMU_vidInit(void)
{
    #if TMU_TIMER_CHANNEL == TIMER0
        // Ovf , 1024 , dis OC0
        TCCR0 = 0x05;

        uint32 Local_u32TicksCounts = ((uint32)TMU_OS_TICK * TMU_CPU_FREQ) / 1024UL;
        LOC_u16OvfCounts = (Local_u32TicksCounts + 255) / 256UL; 
        LOC_u16ISRCounts = LOC_u16OvfCounts;
        LOC_u8Preload = 256UL - (Local_u32TicksCounts % 256UL);
        TCNT0 = LOC_u8Preload;

        TIMSK |= (1<<0);

    #elif TMU_TIMER_CHANNEL == TIMER1

    #elif TMU_TIMER_CHANNEL == TIMER2

    #else
        #error Timer channel selection in TMU is Invalid
    #endif
}


void TMU_vidCreateTask(void(*Copy_pfunAppFun)(void), uint16 Copy_u16Periodicity , uint8 Copy_u8Priority)

{
    if (Copy_u8Priority < TMU_MAX_NUM_TASKS)
    {
        LOC_astrTasksTCB[ Copy_u8Priority ].schedTask = Copy_pfunAppFun;
        LOC_astrTasksTCB[ Copy_u8Priority ].u16Periodicty = Copy_u16Periodicity;
    }
}


void TMU_vidStartScheduler(void)
{
    uint32 Local_u32TempTick =0;
    asm("SEI");
    while(1)
    {
        if (LOC_u32OsTicks > Local_u32TempTick)
        {
            Local_u32TempTick = LOC_u32OsTicks;    
            // for (u8 u8Priority = 0 ; u8Priority <TMU_MAX_NUM_TASKS ; u8Priority++)//0 highest , Max-1 lowest
            for (int8 s8Priority = TMU_MAX_NUM_TASKS -1 ;  s8Priority >=0  ; s8Priority--)//max-1 highest , 0 lowest
            {   
                if ((LOC_astrTasksTCB[s8Priority].schedTask != NULL) &&
                    ((LOC_u32OsTicks % LOC_astrTasksTCB[s8Priority].u16Periodicty) == 0))
                {
                    LOC_astrTasksTCB[s8Priority].schedTask ();   
                }
            }
        }
    }
}


void __vector_11 (void)__attribute__((signal));
void __vector_11 (void)
{
    LOC_u16ISRCounts --;
    if (! LOC_u16ISRCounts)
    {
        TCNT0 = LOC_u8Preload;
       
        LOC_u32OsTicks++;

        LOC_u16ISRCounts = LOC_u16OvfCounts;
    }
}