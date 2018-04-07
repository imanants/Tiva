#ifndef __SYS__H
#define __SYS__H
#include "TM4C123.h"                    // Device header
#include"generic.h"

extern void sys_init(void);
extern void sys_bus_init(void);
extern void sys_clock_init(void);
extern void sys_port_init(port_num port_num);

#endif
