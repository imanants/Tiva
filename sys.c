#include"sys.h"
#include"generic.h"
#include"interrupt.h"
#include"uart.h"

void sys_init(void)
{
	/*set mcu clock frq*/
	sys_clock_init();
	/*set the bus to access the port*/
	sys_bus_init();
	
	uart_fill_uart_details();
	/*initialize interrupt*/
	interrupt_init();
	uart_init(USART5,9600);
}

void sys_bus_init(void)
{
	/*AHB bus is enabled for PORTF*/
	SYSCTL->GPIOHBCTL |= SET << PORTF;
}

void sys_clock_init()
{
}

//void sys_port_init(port_num port_num)
//{
//	SYSCTL->RCGCGPIO |= SET << port_num;
//}
