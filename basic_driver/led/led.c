#include"led\led.h"
/*1.	Enable clock
	2.	Set direction
	3.	Alternate Function select
	4.  Enable open drain
	5. 	Digital enable
	6. 	Set output strength
*/
void led_init(led_color color)
{
	gen_set_gpio(PORTF,(pin_num )color,OUT);	
}
void led_on(led_color color)
{
	GPIOF_AHB->DATA |= SET << color; 
}

void led_off(led_color color)
{
	GPIOF_AHB->DATA &= ~(SET << color);
}

led_status led_get_status(led_color color)
{
	return((GPIOF_AHB->DATA &(SET << color) ? LED_ON : LED_OFF));
}

void led_toggle(led_color color)
{
	if(led_get_status(color) == LED_ON)
	{
		led_off(color);
	}
	else
	{
		led_on(color);
	}
}
