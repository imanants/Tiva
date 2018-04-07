#ifndef __LED__H
#define __LED__H
#include "TM4C123.h"                    // Device header
#include "generic\generic.h"
#define GPIOF_CLOCK_EN 0x20


typedef enum 
{
	RESERVE,
	RED, 				/*PF1*/
	BLUE,				/*PF2*/
	GREEN				/*PF3*/
}led_color;

typedef enum
{
	LED_OFF,
	LED_ON
}led_status;


extern void led_init(led_color color);
extern void led_on(led_color color);
extern void led_off(led_color color);
extern led_status led_get_status(led_color color);
extern void led_toggle(led_color color);

#endif
