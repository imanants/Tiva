#ifndef __systick__H
#define __systick__H
#include "TM4C123.h"                    // Device header

typedef enum
{
	PIOSC_DIV_4,
	SYS_CLK,
}CLK_SRC;
extern void systick_init(uint32_t ms,CLK_SRC soure);
extern void systick_load_counter(uint32_t count);
extern uint32_t systick_get_counter(void);
extern uint32_t systick_get_set_ctrl_sts(uint32_t ctrl_Sts);
#endif
