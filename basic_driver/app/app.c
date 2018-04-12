#include"led\led.h"
#include"app\app.h"
#include"sys\sys.h"
#include"generic\generic.h"
#include"btn\btn.h"
#include"systick\systick.h"
#include"uart\uart.h"
#include"ds\ds.h"
#define DELAY 1000000u
unsigned char name[120] = "";

int main(void)
{
	uint16_t length;
	sys_init();
	led_init(RED);
	led_init(BLUE);
	led_init(GREEN);
	btn_init(BTN1,NO_INT_MODE,NO_INT);
	btn_init(BTN2,INT_MODE,RISING);
	SystemCoreClockUpdate();
	systick_init(DELAY,PIOSC_DIV_4);
	//uart_tx_data(USART5,name,100);
	while(1)
	{
		length =  strlen(name);
		if(uart_array[USART5]->rx_data.state == READY)
		{
			uart_rx_data(USART5,name,120,rx_callback);
		}
		//led_on(RED);
		//led_on(BLUE);
		//led_on(GREEN);
		//gen_delay(DELAY);
		//led_off(RED);
		//led_off(BLUE);
		//led_off(GREEN);
		gen_delay(DELAY);
		if(btn_get_status(BTN1) == PRESS )
		{
			//uart_rx_data(USART5,name,10);
			//uart_tx_data(USART5,name1,10);
			led_on(BLUE);
		}
		else
		{
			led_off(BLUE);
		}
		if(btn_get_status(BTN2) == PRESS )
		{
			if(led_get_status(GREEN) == LED_ON)
			{
				//led_off(GREEN);
			}
			else
			{
				//led_on(GREEN);
			}		
	}
	
	
	}
	return 0;
}
void rx_callback(void)
{
	uart_tx_data(USART5,name,10);
}