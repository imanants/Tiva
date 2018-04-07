#include"systick.h"
#include"generic.h"
#define MAX_DELAY 14000u
#define SYS_TICK_FRQ_DiV_1000 4000ul
void systick_init(uint32_t ms,CLK_SRC soure)
{
	if(ms > MAX_DELAY )
	{
		ms = MAX_DELAY; 
	}
	else
	{
		// do nothing
	}
	SysTick->VAL = 0x00;
	SysTick->LOAD = ( SYS_TICK_FRQ_DiV_1000 * ms - 1u);
	SysTick->CTRL = ( SET << BIT0 | SET << BIT1 );
}
